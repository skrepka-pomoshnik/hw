#!/bin/bash
a=( "SELECT * FROM numbers"
    "SELECT * FROM числа"
    "SELECT * FROM goods"
    "SELECT * FROM storage"
    "select goods.item,price,area from storage left join goods on goods.item = storage.item"
    "select goods.item,price,area from storage right join goods on goods.item = storage.item"
    "create view VVV as select goods.item,price,area from storage join goods on goods.item = storage.item"
    "select * from VVV"
    );
for i in "${a[@]}"; do psql -d postgres -c "$i"; done;
