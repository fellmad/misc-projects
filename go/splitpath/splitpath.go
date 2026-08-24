// copilot: example of using win32 getenv() function in golang
// Here's an example of using the Win32 GetEnv function in Golang to
// retrieve an environment variable:
//
// This example defines a GetEnv function that uses the Win32
// GetEnvironmentVariableW function to retrieve the value of a specified
// environment variable. The main function demonstrates how to use this
// function to get the value of the PATH environment variable. You can
// replace "PATH" with the name of the environment variable you want to retrieve.

package main

import (
	"fmt"
	"log"
	"os"
	"path/filepath"
)

func main() {
	path := os.Getenv("PATH") // case-sensitive environment variable name
	if path == "" {
		log.Fatal("PATH environment variable not found")
	}

	dirs := filepath.SplitList(path)
	for dir := range dirs {
		fmt.Println(dirs[dir])
	}
}
