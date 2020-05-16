package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
)

type Page struct {
	Title string
	Body  []byte
}

func loadPage(title string) (*Page, error) {
	if title == "/" {
		title = "It werks"
	}
	body, err := ioutil.ReadFile(title)
	if err != nil {
		return nil, err
	}
	return &Page{Title: title, Body: body}, nil

}

func Handler(w http.ResponseWriter, r *http.Request) {
	p, err := loadPage(r.URL.Path)
	if err != nil {
		http.Redirect(w, r, "/", http.StatusNotFound)
		return
	}
	fmt.Fprintf(w, "<h1>%s</h1><div style='white-space:pre-wrap'>%s</div>", p.Title, p.Body)
}

func main() {
	http.HandleFunc("/", Handler)
	log.Fatal(http.ListenAndServe(":8080", nil))
}
