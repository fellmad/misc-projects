// http://www.golangpro.com/2015/02/simple-golang-example-sleep-function.html
// https://gobyexample.com/command-line-flags
// https://pkg.go.dev/time?tab=doc#ParseDuration

package main

import (
	"fmt"
	"log"
	"os"
	"time"
)

func printHelp() {
	msg := `Enter a duration.
A duration string is a possibly signed sequence of decimal numbers, each with 
optional fraction and a unit suffix, such as 300ms, -1.5h, or 2h45m. Valid 
time units are ns, us (or µs), ms, s, m, h.`
	fmt.Println(msg)
}

func main() {
	length := len(os.Args)
	if length <= 1 {
		printHelp()
		os.Exit(0)
	}

	firstParmString := os.Args[1]
	duration, err := time.ParseDuration(firstParmString)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("sleeping %.0f seconds:\n", duration.Seconds())

	for sec := duration.Seconds(); sec > 0; sec-- {
		fmt.Printf("\r%.0f ", sec)
		time.Sleep(time.Second)
	}
}
