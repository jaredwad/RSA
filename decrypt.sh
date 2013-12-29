#!/bin/bash
#decrypts a message in a given file

if [ -f "$1" ]
then
    rsaZZ $(< $1)

else

echo "This scrypt will decrypt a message in a given file"
echo "Possible files include:"
echo
ls *.txt
echo
printf "Please enter file name: "
read src

if [ -f "$dir"]
then
    rsaZZ $(< $src)
fi

fi