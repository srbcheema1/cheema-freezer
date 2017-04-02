#!/bin/bash
dir_pres=$PWD
if [ -f $dir_pres/.files ] ; then
    rm $dir_pres/.files
    fi
cd $HOME
file0="*.cpp */*.cpp */*/*.cpp */*/*/*.cpp */*/*/*/*.cpp "
file1="*.txt */*.txt */*/*.txt */*/*/*.txt */*/*/*/*.txt"
file2="*.java */*.java */*/*.java */*/*/*.java */*/*/*/*.java"
file3="*.html */*.html */*/*.html */*/*/*.html */*/*/*/*.html"
file4="*.css */*.css */*/*.css */*/*/*.css */*/*/*/*.css"
file5="*.php */*.php */*/*.php */*/*/*.php */*/*/*/*.php"
file6="*.js */*.js */*/*.js */*/*/*.js */*/*/*/*.js"
file7="*.py */*.py */*/*.py */*/*/*.py */*/*/*/*.py"
file8="*.rb */*.rb */*/*.rb */*/*/*.rb */*/*/*/*.rb"
file9="*.sh */*.sh */*/*.sh */*/*/*.sh */*/*/*/*.sh"

for i in $file0 $file1 $file2 $file3 $file4 $file5 $file6 $file7 $file8 $file9; do 
    [ -f "$i" ] && echo "$HOME/$i" >>$dir_pres/.files ; done | sort


if [ -f $dir_pres/.encrypted_list ] ; then
    rm $dir_pres/.encrypted_list
    fi
file10="*.serial_coders */*.serial_coders */*/*.serial_coders */*/*/*.serial_coders */*/*/*/*.serial_coders"
for i in $file10; do 
    [ -f "$i" ] && echo "$HOME/$i" >>$dir_pres/.encrypted_list ; done | sort
