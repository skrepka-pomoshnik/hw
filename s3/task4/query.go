package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/lib/pq"
)

type good struct {
	id    int
	item  string
	price int
}

func (p *good) Get(name string, connect string) error {
	db, err := sql.Open("postgres", connect)
	if err != nil {
		log.Fatal(err)
	}

	rows, err := db.Query("SELECT * FROM goods WHERE item='" + name + "'")
	if err != nil {
		log.Fatal(err)
	}
	rows.Next()
	err = rows.Scan(&p.id, &p.item, &p.price)
	if err != nil {
		log.Fatal(err)
	}
	defer rows.Close()

	return nil
}

func main() {
	connStr := "user=postgres dbname=postgres sslmode=disable"
	var Milk good
	Milk.Get("milk", connStr)
	fmt.Print(Milk)
}
