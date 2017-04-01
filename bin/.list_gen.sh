#!/bin/bash
dir_pres=$PWD
if [ -f $dir_pres/.files ] ; then
    rm $dir_pres/.files
    fi
cd $HOME
file0="*.cpp */*.cpp */*/*.cpp */*/*/*.cpp */*/*/*/*.cpp "
file1="*.txt */*.txt */*/*.txt */*/*/*.txt */*/*/*/*.txt"
file2="*.java */*.java */*/*.java */*/*/*.java */*/*/*/*.java"
for i in $file0 $file1 $file2; do [ -f "$i" ] && echo "$HOME/$i" >>$dir_pres/.files ; done | sort

if [ -f $dir_pres/.encrypted_list ] ; then
    rm $dir_pres/.encrypted_list
    fi
file3="*.serial_coders */*.serial_coders */*/*.serial_coders */*/*/*.serial_coders */*/*/*/*.serial_coders"
for i in $file3; do [ -f "$i" ] && echo "$HOME/$i" >>$dir_pres/.encrypted_list ; done | sort
