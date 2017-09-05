IF [%2]==[] (
echo Generating %1.bat from %1.pp
d:\tools\LLVM\bin\clang-cl.exe /c /I"%build_shell_path%" /I"..\..\..\include\BuildQOR\Cmd" /I"..\..\..\include\CompilerQOR\Compilers\clang" /I"..\..\..\include" %build_env_params% /W0 /nologo /X /P /EP /TP -Wno-invalid-token-paste %1.pp
echo rem BuildQOR generated script file from %1.pp > %1.bat
FINDSTR /r "." %1.i >> %1.bat
del %1.i
call %1.bat
del %1.bat
) else (
echo Generating %1.bat from %2\%1.pp
copy %2\%1.pp %1.pp
d:\tools\LLVM\bin\clang-cl.exe /c /I"%build_shell_path%" /I"..\..\..\include\BuildQOR\Cmd" /I"..\..\..\include\CompilerQOR\Compilers\clang" /I"..\..\..\include" %build_env_params% /W0 /nologo /X /P /EP /TP -Wno-invalid-token-paste %1.pp
echo rem BuildQOR generated script file from %2\%1.pp > %1.bat
FINDSTR /r "." %1.i >> %1.bat
rem del %1.i
call %1.bat
rem del %1.bat
rem del %1.pp
)
