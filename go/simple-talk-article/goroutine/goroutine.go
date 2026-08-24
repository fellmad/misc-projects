package main

import "fmt"

// no gaurentee this will even run:
func someThing(parameterOne string, parameterTwo int) {
	fmt.Println("parameterOne: ", parameterOne, " parameterTwo: ", parameterTwo)
}

func main() {
	fmt.Println("calling someThing")
	go someThing("aaaa", 1980)
	fmt.Println("done calling someThing")
}
