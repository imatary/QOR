#!/bin/bash
echo Generating "$1".sh from "$2"/"$1".pp
cp $2/$1.pp $1.cpp
gcc -E -I"../../../include/BuildQOR/Bash" -I"../../../include/CompilerQOR/Compilers/GCC" -I"../../../include" $1.cpp -o $1.sh 
chmod +x $1.sh
#$($1.sh)
#rm $1.sh
rm $1.cpp
