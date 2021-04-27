#!/bin/bash
# Date：15:45 2021-03-31
# Author: Create by weiaoxin
# Description: This script function is connect gem5 when fs mode is running 
# Version： 2.0

if [ $# -gt 2 ]
then
    echo "valid input, please input a int num "
elif [ $# == 0 ]
then
    echo "/home/weiaoxin/hybrid-memory/gem5/util/term/ "
    echo "sudo ./m5term 127.0.0.1 3456"
    cd /home/weiaoxin/hybrid-memory/gem5/util/term/
    sudo ./m5term 127.0.0.1 3456
else
    echo "/home/weiaoxin/hybrid-memory/gem5/util/term/"
    echo "sudo ./m5term 127.0.0.1 $1"
    cd /home/weiaoxin/hybrid-memory/gem5/util/term/
    sudo ./m5term 127.0.0.1 $1
fi

