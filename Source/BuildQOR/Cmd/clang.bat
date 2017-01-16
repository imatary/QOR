@echo off
echo Generating Builds with LLVM clang
set build_env_params=
set ppexec=clangPPExec.bat
set drive=%~dp0
set build_shell_path=%drive%
if #%drive:~-1%# == #\# set build_shell_path=%drive:~0,-1%
echo %ppexec% Projects ..\..\..\Build
call %ppexec% Projects ..\..\..\Build
