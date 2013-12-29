#!/bin/bash
#Encrypts a message

if [ "$1" = "" ]
then
    echo "This script will encrypt a message and write it to a file."
    printf "Please enter a message: "
    read message
    printf "Enter destination:"
    read dest
else
    for i in "$@"
    do
        if [ -f "$i" ]
        then
            dest="$i"
        else
            message=$message" $i"
        fi
    done
fi
    
./rsaZZ $message > $dest
