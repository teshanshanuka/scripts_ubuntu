#!/bin/bash

if [ $# -ne 2 ]; then
    echo "usage ./${0##*/} <dir_on_robot> <mnt_dir>"
    exit
fi
if [ -d $2 ]; then
    rm -rf $2
fi
mkdir $2 
sshfs aziro@192.168.0.3:/home/aziro/$1 $2
