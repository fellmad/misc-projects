package main

// print a year's worth of dates formatted just the way we want them.
// use the output to pasted info a Word table.
//
// https://pkg.go.dev/time@go1.20.3
// https://pkg.go.dev/time@go1.20.3#pkg-constants

import (
	"fmt"
	"time"
)

func main() {
	now := time.Now()
	for count := 0; count < 365; count++ {
		s := now.Format("Mon Jan 2, 2006") // see date constants link above
		fmt.Println(s)
		now = now.AddDate(0, 0, 1)
	}
}
