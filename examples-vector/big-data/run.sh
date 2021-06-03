#!/bin/bash

apps=$(ls *.elf | sort -d)
PS3='Please Choose an Example: '
select app in $apps
do
    break
done
echo "Selected Example: $app"

riscvOVPsimPlus.exe --variant RV64GCV --program ${app} --override riscvOVPsim/cpu/vector_version=0.8