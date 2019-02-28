#!/bin/bash
make clean
make
    let r=0
for i in tests/*[1-9]
do 
    ./ladder $(< $i) > $i+res 
    if [ -z "$(diff $i+res $i+etalon)" ] 
    then
        r=$((++r))
        echo "$i passed"
    else
        cat $i+res
        echo "$i failed"
    fi
done
        echo "$r tests passed"
rm tests/*res
