package main

import (
	"errors"
	"fmt"
	"io/ioutil"
	"strings"
)

const MAX = 10
const RESERVE = 2
const DMAX = MAX - RESERVE

type Table struct {
	sizex, sizey int
	Data         []string
}

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
			fmt.Printf("wrong size: %v", val)
			return errors.New("too lengthy")
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

func (T *Table) SortBy(n int, asc bool) error {
	if n > T.sizex {
		return errors.New("No such column")
	}
	if T.Data[MAX+n] == "int" {

	}

	return nil
}

//select something from table orderby
func Select(columns []string, T Table, regex string, asc int) (Table, error) {
	set := make(map[int]struct{})
	if len(columns) == T.sizex {
		return T, nil
	}

	if len(columns) > T.sizex {
		return T, errors.New("too much columns")
	}
	for inum, i := range T.Data[:T.sizex-1] {
		for _, j := range columns {
			//		fmt.Printf("%v==%v:%v", i, j, i == j)
			if i == j {
				set[inum] = struct{}{}
			}
		} //what if some fields are not found?
	}
	kk := 0 //deleted column
	for k := range set {
		T.RemoveColumn(k - kk)
		kk++
	}

	return T, nil
}

//func scanner() {
//	scanner := bufio.NewScanner(os.Stdin)
//	for scanner.Scan() {
//		if scanner.Text() == "\n" {
//			fmt.Print("?")
//		}
//		if scanner.Text() == "exit" {
//			return
//		}
//	}
//}

func main() {
	var goods, storage, numbers, numerus, числа Table
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

	goods, _ = Select([]string{"id", "price"}, goods, "", 0)
	fmt.Print(goods)
}
