#!/bin/bash
cp ../cpmaker ./
let "i = 0";
while IFS= read -r test
do 
    ./cpmaker -i "$test" -o "$i";
    let "i++";
done < $1
