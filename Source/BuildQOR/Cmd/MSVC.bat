@echo off
echo Generating Builds with Microsoft Visual C++
set build_env_params=
set ppexec=MSVCPPExec.bat
set drive=%~dp0
set build_shell_path=%drive%
if #%drive:~-1%# == #\# set build_shell_path=%drive:~0,-1%
call %ppexec% Projects ..\..\..\Build


