@echo off

IF [%2]==[] (
rem echo Generating %1.bat from %1.pp
cl.exe /c /I"%build_shell_path%" /I"..\..\..\include\BuildQOR\Cmd" /I"..\..\..\include\CompilerQOR\Compilers\MSVC" /I"..\..\..\include" %build_env_params% /W0 /nologo /X /P /EP %1.pp
echo rem BuildQOR generated script file from %1.pp > %1.bat
FINDSTR /r "." %1.i >> %1.bat
del %1.i
call %1.bat
del %1.bat
) else (
rem echo Generating %1.bat from %2\%1.pp
copy %2\%1.pp %1.pp >nul
cl.exe /c /I"%build_shell_path%" /I"..\..\..\include\BuildQOR\Cmd" /I"..\..\..\include\CompilerQOR\Compilers\MSVC" /I"..\..\..\include" %build_env_params% /W0 /nologo /X /P /EP %1.pp
echo rem BuildQOR generated script file from %2\%1.pp > %1.bat
FINDSTR /r "." %1.i >> %1.bat
del %1.i
call %1.bat
del %1.bat
del %1.pp
)



