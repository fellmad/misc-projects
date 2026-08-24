package main

import (
	"fmt"
	"mymodule/mypackage"

	"github.com/spf13/cobra"
)

func main() {
	cmd := &cobra.Command{
		Run: func(cmd *cobra.Command, args []string) {
			fmt.Println("hello modules")
			mypackage.PrintHello()
		},
	}
	fmt.Println("calling cmd.Execute():")
	cmd.Execute()
}
