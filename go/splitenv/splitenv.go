// see splitpath.go

package main

import (
	"fmt"
	"log"
	"os"
	"path/filepath"
)

func printHelp() {
	msg := `Enter then name of an environment variable, like "path".`
	fmt.Println(msg)
}

func GetEnv(key string) (string, error) {
	// Use os.LookupEnv for cross-platform environment lookup.
	if v, ok := os.LookupEnv(key); ok {
		return v, nil
	}
	return "", fmt.Errorf("environment variable %s not set", key)
}

func main() {
	length := len(os.Args)
	if length <= 1 {
		printHelp()
		os.Exit(0)
	}

	path := os.Args[1]
	value, err := GetEnv(path)
	if err != nil {
		log.Fatal("Error retrieving environment variable:", value, err)
	}

	paths := filepath.SplitList(value)
	//fmt.Println(paths)
	for _, currentPath := range paths {
		fmt.Println(currentPath)
	}
}
