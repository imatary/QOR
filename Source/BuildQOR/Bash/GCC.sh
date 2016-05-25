#!/bin/bash
clear
echo Generating Build with GCC
echo "Hi, $USER."
echo "Home is $HOME"
echo "This is running on an $TERM terminal."
echo This script is $(readlink -f "$0")

#Now do something useful

build_env_params=
ppexec=./GCCPPExec.sh
/bin/bash $ppexec Projects ../../../Build
