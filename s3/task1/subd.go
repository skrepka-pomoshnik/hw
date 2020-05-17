package main

import (
	"bufio"
	"errors"
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

const (
	MAX     = 10
	RESERVE = 2
	DMAX    = MAX - RESERVE
	HELLO   = "\n? "
	ERROR   = "Error: syntax error at or near: %v" + HELLO
)

type Table struct {
	sizex, sizey int
	Data         []string
}

var goods, storage, numbers, numerus, числа Table
var Tables = map[string]*Table{"goods": &goods, "storage": &storage, "numbers": &numbers, "numerus": &numerus, "числа": &числа}

func (T *Table) Init(n []string, t []string) error { //name and type
	if len(n) != len(t) || len(n) > MAX {
		fmt.Print(errors.New("wrong init"))
		return errors.New("wrong init")
	}
	//check types...
	T.Data = make([]string, MAX*MAX)
	copy(T.Data, n)
	copy(T.Data[MAX:], t)
	T.sizex = len(n)
	T.sizey = 0 //do not count first 2
	return nil
}

func (T Table) String() string {

	str := "\n"
	count := T.sizey + RESERVE
	for num, val := range T.Data {
		if num%MAX == T.sizex {
			str += ("\n")
			count--
			continue
		}
		if num%MAX > T.sizex { //do not print empty
			continue
		}
		if count == 0 {
			break
		}
		str += val + ","
	}
	return str
}

func (T *Table) Insert(str []string) error {
	if len(str) > (DMAX)*MAX {
		return errors.New("too much")
	}
	for i := 0; i < len(str); i += T.sizex {
		end := i + T.sizex
		if end > len(str) {
			end = len(str)
		}
		copy(T.Data[MAX*2+MAX*(T.sizey):], str[i:end]) //20 first two
		T.sizey++
	}
	return nil
}

func (T *Table) Export(File string) error {
	data, err := ioutil.ReadFile(File)
	if err != nil {
		fmt.Println("File reading error", err)
		return err
	}
	for num, val := range strings.Split(string(data), "\n") {
		if val == "" {
			continue
		}
		if len(strings.Split(val, ",")) != T.sizex {
			return fmt.Errorf("too lengthy %v", len(strings.Split(val, ",")))
		}
		if num > DMAX {
			break
		}
		T.Insert(strings.Split(val, ","))
	}
	return nil
}

func erase(a []string, n int) []string {
	return a[:n+copy(a[n:], a[n+1:])] //slice trick
}

func (T *Table) RemoveColumn(n int) error {
	if n > T.sizex {
		return errors.New("No such column")
	}

	for i := 0; i < MAX*(T.sizey+2); i += MAX {
		end := i + MAX
		a := erase(T.Data[i:end], n)

		copy(T.Data[i:], a)
	}
	T.sizex--
	return nil
}

//select something from table orderby
func Select(columns []string, T Table, asc int) (Table, error) {
	smap := make(map[string]int)
	for i, v := range T.Data[:T.sizex] {
		smap[v] = i
	}

	for _, v := range columns {
		if _, ok := smap[v]; ok {
			smap[v] = -1
		} else {
			return Table{}, fmt.Errorf("No such column %v"+HELLO, v)
		}
	}

	TT := T
	TT.Data = make([]string, len(T.Data))
	copy(TT.Data, T.Data)

	deleted := 0 //deleted column
	for _, i := range smap {
		if i != -1 {
			TT.RemoveColumn(i - deleted)
			deleted++
		}
	}

	return TT, nil
}

func printselection(input []string) error {
	var from int
	for i, v := range input {
		if strings.EqualFold(v, "from") {
			from = i
			break
		}
	}
	if from < 2 {
		return fmt.Errorf(ERROR, input[from])
	}
	T, ok := Tables[input[from+1]]
	if !ok {
		return fmt.Errorf(ERROR, input[from+1])
	}
	columns := strings.Split(input[from-1], ",")
	if len(columns) == 1 && columns[0] == "*" {
		columns = T.Data[:T.sizex]
	}
	Result, err := Select(columns, *T, 0)
	if err != nil {
		fmt.Print(err)
	}
	fmt.Print(Result)
	fmt.Print(HELLO)
	return nil
}

func scanner() {
	fmt.Print("Welcome! Press help to exit.\n? ")
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		switch {
		case scanner.Text() == "":
			fmt.Print("? ")
		case strings.EqualFold(strings.Fields(scanner.Text())[0], "select"):
			err := printselection(strings.Fields(scanner.Text()))
			if err != nil {
				fmt.Print(ERROR)
			}
		case scanner.Text() == "exit;":
			return
		case scanner.Text() == "help":
			return
		case scanner.Text() == "help;":
			return
		default:
			fmt.Printf(ERROR, scanner.Text())
		}
	}
}

func main() {
	goods.Init([]string{"id", "item", "price"}, []string{"int", "string", "string"})
	storage.Init([]string{"id", "area", "item"}, []string{"int", "string", "string"})
	numbers.Init([]string{"id", "name"}, []string{"int", "string"})
	numerus.Init([]string{"id", "name"}, []string{"int", "string"})
	числа.Init([]string{"id", "name"}, []string{"int", "string"})

	goods.Export("goods.csv")
	storage.Export("storage.csv")
	numbers.Export("numbers.csv")
	numerus.Export("numerus.csv")
	числа.Export("числа.csv")

	scanner()
}
