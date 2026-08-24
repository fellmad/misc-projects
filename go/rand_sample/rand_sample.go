// http://127.0.0.1:3999/basics/1
// https://stackoverflow.com/questions/8288679/difficulty-with-go-rand-package

package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	rand.Seed(time.Now().UnixNano())
	fmt.Println("My favorite number is", rand.Intn(130))
}
