//HighLevelAssembler.h

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
// Copyright (c) Querysoft Limited 2012
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

#ifndef ARCHQOR_HIGHLEVELASSEMBLER_H_2
#define ARCHQOR_HIGHLEVELASSEMBLER_H_2

#include "CompilerQOR.h"
#include "ArchQOR/Common/Assembler/CodeGenerator.h"
#include "ArchQOR/Common/HLAssembler/FunctionDefinition.h"

//------------------------------------------------------------------------------
namespace nsArch
{	
	//------------------------------------------------------------------------------
	// High Level Assembler - high level code generation.
	//
	// This class is used to store instruction stream and allows to modify
	// it on the fly. It uses different concept than Assembler class
	// and in fact Assembler is only used as a backend. Compiler never
	// emits machine code and each instruction you use is stored to instruction
	// array instead. This allows to modify instruction stream later and for
	// example to reorder instructions to make better performance.
	//
	// Using @c AsmJit::Compiler moves code generation to higher level. Higher
	// level constructs allows to write more abstract and extensible code that
	// is not possible with pure @c AsmJit::Assembler class. Because
	// @c AsmJit::Compiler needs to create many objects and lifetime of these
	// objects is small (same as @c AsmJit::Compiler lifetime itself) it uses
	// very fast memory management model. This model allows to create object
	// instances in nearly zero time (compared to @c malloc() or @c new()
	// operators) so overhead by creating machine code by @c AsmJit::Compiler
	// is minimized.
	//
	// @section AsmJit_Compiler_TheStory The Story
	//
	// Before telling you how Compiler works I'd like to write a story. I'd like
	// to cover reasons why this class was created and why I'm recommending to use 
	// it. When I released the first version of AsmJit (0.1) it was a toy. The
	// first function I wrote was function which is still available as testjit and
	// which simply returns 1024. The reason why function works for both 32-bit/
	// 64-bit mode and for Windows/Unix specific calling conventions is luck, no
	// arguments usage and no registers usage except returning value in EAX/RAX.
	//
	// Then I started a project called BlitJit which was targetted to generating
	// JIT code for computer graphics. After writing some lines I decided that I
	// can't join pieces of code together without abstraction, should be
	// pixels source pointer in ESI/RSI or EDI/RDI or it's completelly 
	// irrellevant? What about destination pointer and SSE2 register for reading
	// input pixels? The simple answer might be "just pick some one and use it".
	//
	// Another reason for abstraction is function calling-conventions. It's really
	// not easy to write assembler code for 32-bit and 64-bit platform supporting
	// three calling conventions (32-bit is similar between Windows and Unix, but
	// 64-bit calling conventions are different).
	//
	// At this time I realized that I can't write code which uses named registers,
	// I need to abstract it. In most cases you don't need specific register, you
	// need to emit instruction that does something with 'virtual' register(s),
	// memory, immediate or label.
	//
	// The first version of AsmJit with Compiler was 0.5 (or 0.6?, can't remember).
	// There was support for 32-bit and 64-bit mode, function calling conventions,
	// but when emitting instructions the developer needed to decide which 
	// registers are changed, which are only read or completely overwritten. This
	// model helped a lot when generating code, especially when joining more
	// code-sections together, but there was also small possibility for mistakes.
	// Simply the first version of Compiler was great improvement over low-level 
	// Assembler class, but the API design wasn't perfect.
	//
	// The second version of Compiler, completelly rewritten and based on 
	// different goals, is part of AsmJit starting at version 1.0. This version
	// was designed after the first one and it contains serious improvements over
	// the old one. The first improvement is that you just use instructions with 
	// virtual registers - called variables. When using compiler there is no way
	// to use native registers, there are variables instead. AsmJit is smarter 
	// than before and it knows which register is needed only for read (r), 
	// read/write (w) or overwrite (x). Supported are also instructions which 
	// are using some registers in implicit way (these registers are not part of
	// instruction definition in string form). For example to use CPUID instruction 
	// you must give it four variables which will be automatically allocated to
	// input/output registers (EAX, EBX, ECX, EDX).
	// 
	// Another improvement is algorithm used by a register allocator. In first
	// version the registers were allocated when creating instruction stream. In
	// new version registers are allocated after calling @c Compiler::make(). This
	// means that register allocator has information about scope of all variables
	// and their usage statistics. The algorithm to allocate registers is very
	// simple and it's always called as a 'linear scan register allocator'. When
	// you get out of registers the all possible variables are scored and the worst
	// is spilled. Of course algorithm ignores the variables used for current
	// instruction.
	//
	// In addition, because registers are allocated after the code stream is
	// generated, the state switches between jumps are handled by Compiler too.
	// You don't need to worry about jumps, compiler always do this dirty work 
	// for you.
	//
	// The nearly last thing I'd like to present is calling other functions from 
	// the generated code. ArchQOR uses a CFunctionPrototype class to hold
	// the function parameters, their position in stack (or register index) and
	// function return value. This class is used internally, but it can be
	// used to create your own function calling-convention. All standard function
	// calling conventions are implemented.
	//
	// Please enjoy the new version of Compiler, it was created for writing a
	// low-level code using high-level API, leaving developer to concentrate to
	// real problems and not to solving a register puzzle.
	//
	// @section AsmJit_Compiler_CodeGeneration Code Generation
	//
	// First that is needed to know about compiler is that compiler never emits
	// machine code. It's used as a middleware between @c AsmJit::Assembler and
	// your code. There is also convenience method @c make() that allows to
	// generate machine code directly without creating @c AsmJit::Assembler
	// instance.
	//
	// Comparison of generating machine code through @c Assembler and directly
	// by @c Compiler:
	//
	// @code
	// // Assembler instance is low level code generation class that emits
	// // machine code.
	// Assembler a;
	//
	// // Compiler instance is high level code generation class that stores all
	// // instructions in internal representation.
	// Compiler c;
	//
	// // ... put your code here ...
	//
	// // Final step - generate code. AsmJit::Compiler::serialize() will serialize
	// // all instructions into Assembler and this ensures generating real machine
	// // code.
	// c.serialize(a);
	//
	// // Your function
	// void* fn = a.make();
	// @endcode
	//
	// Example how to generate machine code using only @c Compiler (preferred):
	//
	// @code
	// // Compiler instance is enough.
	// Compiler c;
	//
	// // ... put your code here ...
	//
	// // Your function
	// void* fn = c.make();
	// @endcode
	//
	// You can see that there is @c AsmJit::Compiler::serialize() function that
	// emits instructions into @c AsmJit::Assembler(). This layered architecture
	// means that each class is used for something different and there is no code
	// duplication. For convenience there is also @c AsmJit::Compiler::make()
	// method that can create your function using @c AsmJit::Assembler, but
	// internally (this is preffered bahavior when using @c AsmJit::Compiler).
	//
	// The @c make() method allocates memory using @c CodeGenerator instance passed
	// into the @c Compiler constructor. If code generator is used to create JIT
	// function then virtual memory allocated by @c MemoryManager is used. To get
	// global memory manager use @c MemoryManager::getGlobal().
	//
	// @code
	// // Compiler instance is enough.
	// Compiler c;
	//
	// // ... put your code using Compiler instance ...
	//
	// // Your function
	// void* fn = c.make();
	//
	// // Free it if you don't want it anymore
	// // (using global memory manager instance)
	// MemoryManager::getGlobal()->free(fn);
	// @endcode
	//
	// @section AsmJit_Compiler_Functions Functions
	//
	// To build functions with @c Compiler, see @c AsmJit::Compiler::newFunction()
	// method.
	//
	// @section AsmJit_Compiler_Variables Variables
	//
	// Compiler is able to manage variables and function arguments. Internally
	// there is no difference between function argument and variable declared
	// inside. To get function argument you use @c argGP() method and to declare
	// variable use @c newGP(), @c newMM() and @c newXMM() methods. The @c newXXX()
	// methods accept also parameter describing the variable type. For example
	// the @c newGP() method always creates variable which size matches the target
	// architecture size (for 32-bit target the 32-bit variable is created, for
	// 64-bit target the variable size is 64-bit). To override this behavior the
	// variable type must be specified.
	//
	// @code
	// // Compiler and function declaration - void f(int*);
	// Compiler c;
	// c.newFunction(CALL_CONV_DEFAULT, BuildFunction1<int*>());
	//
	// // Get argument variable (it's pointer).
	// GPVar a1(c.argGP(0));
	//
	// // Create your variables.
	// GPVar x1(c.newGP(VARIABLE_TYPE_GPD));
	// GPVar x2(c.newGP(VARIABLE_TYPE_GPD));
	//
	// // Init your variables.
	// c.mov(x1, 1);
	// c.mov(x2, 2);
	//
	// // ... your code ...
	// c.add(x1, x2);
	// // ... your code ...
	//
	// // Store result to a given pointer in first argument
	// c.mov(dword_ptr(a1), x1);
	//
	// // End of function body.
	// c.endFunction();
	//
	// // Make the function.
	// typedef void (*MyFn)(int*);
	// MyFn fn = function_cast<MyFn>(c.make());
	// @endcode
	//
	// This code snipped needs to be explained. You can see that there are more 
	// variable types that can be used by @c Compiler. Most useful variables can
	// be allocated using general purpose registers (@c GPVar), MMX registers 
	// (@c MMVar) or SSE registers (@c XMMVar).
	//
	// X86/X64 variable types:
	// 
	// - @c VARIABLE_TYPE_GPD - 32-bit general purpose register (EAX, EBX, ...).
	// - @c VARIABLE_TYPE_GPQ - 64-bit general purpose register (RAX, RBX, ...).
	// - @c VARIABLE_TYPE_GPN - 32-bit or 64-bit general purpose register, depends
	//   to target architecture. Mapped to @c VARIABLE_TYPE_GPD or @c VARIABLE_TYPE_GPQ.
	//
	// - @c VARIABLE_TYPE_X87 - 80-bit floating point stack register st(0 to 7).
	// - @c VARIABLE_TYPE_X87_1F - 32-bit floating point stack register st(0 to 7).
	// - @c VARIABLE_TYPE_X87_1D - 64-bit floating point stack register st(0 to 7).
	//
	// - @c VARIALBE_TYPE_MM - 64-bit MMX register.
	//
	// - @c VARIABLE_TYPE_XMM - 128-bit SSE register.
	// - @c VARIABLE_TYPE_XMM_1F - 128-bit SSE register which contains 
	//   scalar 32-bit single precision floating point.
	// - @c VARIABLE_TYPE_XMM_1D - 128-bit SSE register which contains
	//   scalar 64-bit double precision floating point.
	// - @c VARIABLE_TYPE_XMM_4F - 128-bit SSE register which contains
	//   4 packed 32-bit single precision floating points.
	// - @c VARIABLE_TYPE_XMM_2D - 128-bit SSE register which contains
	//   2 packed 64-bit double precision floating points.
	//
	// Unified variable types:
	//
	// - @c VARIABLE_TYPE_INT32 - 32-bit general purpose register.
	// - @c VARIABLE_TYPE_INT64 - 64-bit general purpose register.
	// - @c VARIABLE_TYPE_INTPTR - 32-bit or 64-bit general purpose register / pointer.
	//
	// - @c VARIABLE_TYPE_FLOAT - 32-bit single precision floating point.
	// - @c VARIABLE_TYPE_DOUBLE - 64-bit double precision floating point.
	//
	// Variable states:
	//
	// - @c VARIABLE_STATE_UNUSED - State that is assigned to newly created
	//   variables or to not used variables (dereferenced to zero).
	// - @c VARIABLE_STATE_REGISTER - State that means that variable is currently
	//   allocated in register.
	// - @c VARIABLE_STATE_MEMORY - State that means that variable is currently
	//   only in memory location.
	//
	// When you create new variable, initial state is always @c VARIABLE_STATE_UNUSED,
	// allocating it to register or spilling to memory changes this state to
	// @c VARIABLE_STATE_REGISTER or @c VARIABLE_STATE_MEMORY, respectively.
	// During variable lifetime it's usual that its state is changed multiple
	// times. To generate better code, you can control allocating and spilling
	// by using up to four types of methods that allows it (see next list).
	//
	// Explicit variable allocating / spilling methods:
	//
	// - @c Compiler::alloc() - Explicit method to alloc variable into
	//      register. You can use this before loops or code blocks.
	//
	// - @c Compiler::spill() - Explicit method to spill variable. If variable
	//      is in register and you call this method, it's moved to its home memory
	//      location. If variable is not in register no operation is performed.
	//
	// - @c Compiler::unuse() - Unuse variable (you can use this to end the
	//      variable scope or sub-scope).
	//
	// Please see AsmJit tutorials (testcompiler.cpp and testvariables.cpp) for
	// more complete examples.
	//
	// @section AsmJit_Compiler_MemoryManagement Memory Management
	//
	// @c Compiler Memory management follows these rules:
	// - Everything created by @c Compiler is always freed by @c Compiler.
	// - To get decent performance, compiler always uses larger memory buffer
	//   for objects to allocate and when compiler instance is destroyed, this
	//   buffer is freed. Destructors of active objects are called when
	//   destroying compiler instance. Destructors of abadonded compiler
	//   objects are called immediately after abadonding them.
	// - This type of memory management is called 'zone memory management'.
	//
	// This means that you can't use any @c Compiler object after destructing it,
	// it also means that each object like @c Label, @c Var and others are created
	// and managed by @c Compiler itself. These objects contain ID which is used
	// internally by Compiler to store additional information about these objects.
	//
	// @section AsmJit_Compiler_StateManagement Control-Flow and State Management.
	//
	// The @c Compiler automatically manages state of the variables when using
	// control flow instructions like jumps, conditional jumps and calls. There
	// is minimal heuristics for choosing the method how state is saved or restored.
	//
	// Generally the state can be changed only when using jump or conditional jump
	// instruction. When using non-conditional jump then state change is embedded
	// into the instruction stream before the jump. When using conditional jump
	// the @c Compiler decides whether to restore state before the jump or whether
	// to use another block where state is restored. The last case is that no-code
	// have to be emitted and there is no state change (this is of course ideal).
	//
	// Choosing whether to embed 'restore-state' section before conditional jump
	// is quite simple. If jump is likely to be 'taken' then code is embedded, if
	// jump is unlikely to be taken then the small code section for state-switch
	// will be generated instead.
	//
	// Next example is the situation where the extended code block is used to
	// do state-change:
	//
	// @code
	// Compiler c;
	//
	// c.newFunction(CALL_CONV_DEFAULT, FunctionBuilder0<Void>());
	// c.getFunction()->setHint(FUNCTION_HINT_NAKED, true);
	//
	// // Labels.
	// Label L0 = c.newLabel();
	//
	// // Variables.
	// GPVar var0 = c.newGP();
	// GPVar var1 = c.newGP();
	//
	// // Cleanup. After these two lines, the var0 and var1 will be always stored
	// // in registers. Our example is very small, but in larger code the var0 can
	// // be spilled by xor(var1, var1).
	// c.xor_(var0, var0);
	// c.xor_(var1, var1);
	// c.cmp(var0, var1);
	// // State:
	// //   var0 - register.
	// //   var1 - register.
	//
	// // We manually spill these variables.
	// c.spill(var0);
	// c.spill(var1);
	// // State:
	// //   var0 - memory.
	// //   var1 - memory.
	//
	// // Conditional jump to L0. It will be always taken, but compiler thinks that
	// // it is unlikely taken so it will embed state change code somewhere.
	// c.je(L0);
	//
	// // Do something. The variables var0 and var1 will be allocated again.
	// c.add(var0, 1);
	// c.add(var1, 2);
	// // State:
	// //   var0 - register.
	// //   var1 - register.
	//
	// // Bind label here, the state is not changed.
	// c.bind(L0);
	// // State:
	// //   var0 - register.
	// //   var1 - register.
	//
	// // We need to use var0 and var1, because if compiler detects that variables
	// // are out of scope then it optimizes the state-change.
	// c.sub(var0, var1);
	// // State:
	// //   var0 - register.
	// //   var1 - register.
	//
	// c.endFunction();
	// @endcode
	//
	// The output:
	//
	// @verbatim
	// xor eax, eax                    ; xor var_0, var_0
	// xor ecx, ecx                    ; xor var_1, var_1
	// cmp eax, ecx                    ; cmp var_0, var_1
	// mov [esp - 24], eax             ; spill var_0
	// mov [esp - 28], ecx             ; spill var_1
	// je L0_Switch
	// mov eax, [esp - 24]             ; alloc var_0
	// add eax, 1                      ; add var_0, 1
	// mov ecx, [esp - 28]             ; alloc var_1
	// add ecx, 2                      ; add var_1, 2
	// L0:
	// sub eax, ecx                    ; sub var_0, var_1
	// ret
	//
	// ; state-switch begin
	// L0_Switch0:
	// mov eax, [esp - 24]             ; alloc var_0
	// mov ecx, [esp - 28]             ; alloc var_1
	// jmp short L0
	// ; state-switch end
	// @endverbatim
	//
	// You can see that the state-switch section was generated (see L0_Switch0).
	// The compiler is unable to restore state immediately when emitting the
	// forward jump (the code is generated from first to last instruction and
	// the target state is simply not known at this time).
	//
	// To tell @c Compiler that you want to embed state-switch code before jump
	// it's needed to create backward jump (where also processor expects that it
	// will be taken). To demonstrate the possibility to embed state-switch before
	// jump we use slightly modified code:
	//
	// @code
	// Compiler c;
	// 
	// c.newFunction(CALL_CONV_DEFAULT, FunctionBuilder0<Void>());
	// c.getFunction()->setHint(FUNCTION_HINT_NAKED, true);
	// 
	// // Labels.
	// Label L0 = c.newLabel();
	// 
	// // Variables.
	// GPVar var0 = c.newGP();
	// GPVar var1 = c.newGP();
	// 
	// // Cleanup. After these two lines, the var0 and var1 will be always stored
	// // in registers. Our example is very small, but in larger code the var0 can
	// // be spilled by xor(var1, var1).
	// c.xor_(var0, var0);
	// c.xor_(var1, var1);
	// // State:
	// //   var0 - register.
	// //   var1 - register.
	// 
	// // We manually spill these variables.
	// c.spill(var0);
	// c.spill(var1);
	// // State:
	// //   var0 - memory.
	// //   var1 - memory.
	// 
	// // Bind our label here.
	// c.bind(L0);
	// 
	// // Do something, the variables will be allocated again.
	// c.add(var0, 1);
	// c.add(var1, 2);
	// // State:
	// //   var0 - register.
	// //   var1 - register.
	// 
	// // Backward conditional jump to L0. The default behavior is that it is taken
	// // so state-change code will be embedded here.
	// c.je(L0);
	// 
	// c.endFunction();
	// @endcode
	//
	// The output:
	//
	// @verbatim
	// xor ecx, ecx                    ; xor var_0, var_0
	// xor edx, edx                    ; xor var_1, var_1
	// mov [esp - 24], ecx             ; spill var_0
	// mov [esp - 28], edx             ; spill var_1
	// L.2:
	// mov ecx, [esp - 24]             ; alloc var_0
	// add ecx, 1                      ; add var_0, 1
	// mov edx, [esp - 28]             ; alloc var_1
	// add edx, 2                      ; add var_1, 2
	//
	// ; state-switch begin
	// mov [esp - 24], ecx             ; spill var_0
	// mov [esp - 28], edx             ; spill var_1
	// ; state-switch end
	//
	// je short L.2
	// ret
	// @endverbatim
	//
	// Please notice where the state-switch section is located. The @c Compiler 
	// decided that jump is likely to be taken so the state change is embedded
	// before the conditional jump. To change this behavior into the previous
	// case it's needed to add a hint (@c HINT_TAKEN or @c HINT_NOT_TAKEN).
	//
	// Replacing the <code>c.je(L0)</code> by <code>c.je(L0, HINT_NOT_TAKEN)
	// will generate code like this:
	//
	// @verbatim
	// xor ecx, ecx                    ; xor var_0, var_0
	// xor edx, edx                    ; xor var_1, var_1
	// mov [esp - 24], ecx             ; spill var_0
	// mov [esp - 28], edx             ; spill var_1
	// L0:
	// mov ecx, [esp - 24]             ; alloc var_0
	// add ecx, 1                      ; add var_0, a
	// mov edx, [esp - 28]             ; alloc var_1
	// add edx, 2                      ; add var_1, 2
	// je L0_Switch, 2
	// ret
	//
	// ; state-switch begin
	// L0_Switch:
	// mov [esp - 24], ecx             ; spill var_0
	// mov [esp - 28], edx             ; spill var_1
	// jmp short L0
	// ; state-switch end
	// @endverbatim
	//
	// This section provided information about how state-change works. The 
	// behavior is deterministic and it can be overriden.
	//
	// @section AsmJit_Compiler_AdvancedCodeGeneration Advanced Code Generation
	//
	// This section describes advanced method of code generation available to
	// @c Compiler (but also to @c Assembler). When emitting code to instruction
	// stream the methods like @c mov(), @c add(), @c sub() can be called directly
	// (advantage is static-type control performed also by C++ compiler) or 
	// indirectly using @c emit() method. The @c emit() method needs only 
	// instruction code and operands.
	//
	// Example of code generating by standard type-safe API:
	//
	// @code
	// Compiler c;
	// GPVar var0 = c.newGP();
	// GPVar var1 = c.newGP();
	//
	// ...
	//
	// c.mov(var0, imm(0));
	// c.add(var0, var1);
	// c.sub(var0, var1);
	// @endcode
	//
	// The code above can be rewritten as:
	//
	// @code
	// Compiler c;
	// GPVar var0 = c.newGP();
	// GPVar var1 = c.newGP();
	//
	// ...
	//
	// c.emit(INST_MOV, var0, imm(0));
	// c.emit(INST_ADD, var0, var1);
	// c.emit(INST_SUB, var0, var1);
	// @endcode
	//
	// The advantage of first snippet is very friendly API and type-safe control
	// that is controlled by the C++ compiler. The advantage of second snippet is
	// availability to replace or generate instruction code in different places.
	// See the next example how the @c emit() method can be used to generate
	// abstract code.
	//
	// Use case:
	//
	// @code
	// bool emitArithmetic(Compiler& c, XMMVar& var0, XMMVar& var1, const char* op)
	// {
	//   uint code = INVALID_VALUE;
	//
	//   if (strcmp(op, "ADD") == 0)
	//     code = INST_ADDSS;
	//   else if (strcmp(op, "SUBTRACT") == 0)
	//     code = INST_SUBSS;
	//   else if (strcmp(op, "MULTIPLY") == 0)
	//     code = INST_MULSS;
	//   else if (strcmp(op, "DIVIDE") == 0)
	//     code = INST_DIVSS;
	//   else
	//     // Invalid parameter?
	//     return false;
	//
	//   c.emit(code, var0, var1);
	// }
	// @endcode
	//
	// Other use cases are waiting for you! Be sure that instruction you are 
	// emitting is correct and encodable, because if not, Assembler will set
	// error code to @c ERROR_UNKNOWN_INSTRUCTION.
	//
	// @section AsmJit_Compiler_CompilerDetails Compiler Details
	//
	// This section is here for people interested in the compiling process. There
	// are few steps that must be done for each compiled function (or your code).
	//
	// When your @c Compiler instance is ready, you can create function and add
	// emittables using intrinsics or higher level methods implemented by the
	// @c AsmJit::Compiler. When you are done (all instructions serialized) you
	// should call @c AsmJit::Compiler::make() method which will analyze your code,
	// allocate registers and memory for local variables and serialize all emittables
	// to @c AsmJit::Assembler instance. Next steps shows what's done internally
	// before code is serialized into @c AsmJit::Assembler
	//   (implemented in @c AsmJit::Compiler::serialize() method).
	//
	// 1. Compiler try to match function and end-function emittables (these
	//    emittables define the function-body or function block).
	//
	// 2. For all emittables inside the function-body the virtual functions
	//    are called in this order:
	//    - Emittable::prepare()
	//    - Emittable::translate()
	//    - Emittable::emit()
	//    - Emittable::post()
	//
	//    There is some extra work when emitting function prolog / epilog and
	//    register allocator.
	//
	// 3. Emit jump tables data.
	//
	// When everything here ends, AsmJit::Assembler contains binary stream
	// that needs only relocation to be callable by C/C++ code.
	//
	// @section AsmJit_Compiler_Differences Summary of Differences between @c Assembler and @c Compiler
	//
	// - Instructions are not translated to machine code immediately, they are
	//   stored as emmitables (see AsmJit::Emittable, AsmJit::EInstruction).
	// - Contains function builder and ability to call other functions.
	// - Contains register allocator and variable management.
	// - Contains a lot of helper methods to simplify the code generation not
	//   available/possible in Assembler.
	// - Ability to pre-process or post-process the code which is being generated.

}//nsArch

#endif//ARCHQOR_HIGHLEVELASSEMBLER_H_2
