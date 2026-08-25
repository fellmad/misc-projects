// https://research.swtch.com/vgo1
// https://github.com/rsc/hello/blob/v1.0.0/hello.go
// https://lets-go.alexedwards.net/
// https://lets-go-further.alexedwards.net/sample/00.00-front-matter.html

// Hello greets the world.
package main

import (
	"fmt"

	"rsc.io/quote/v4"
)

func main() {
	fmt.Println(quote.Hello())
	fmt.Println(quote.Glass())
	fmt.Println(quote.Go())
	fmt.Println(quote.Opt())
}
