#!/bin/bash
a=( "SELECT * FROM numbers"
    "SELECT * FROM numerus"
    "SELECT * FROM числа"
    "SELECT * FROM goods"
    "SELECT * FROM storage"
    "SELECT area FROM storage where item = (SELECT item from goods goods where price < 5)" 
    );
for i in "${a[@]}"; do psql -d postgres -c "$i"; done;
