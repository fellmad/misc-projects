package main

import (
	"log"
	"os"
	"path/filepath"
	"strings"
)

func main() {
	gopath := os.Getenv("gopath")
	if gopath == "" {
		log.Fatal("Your GOPATH has not been set!")
	}

	path := os.Getenv("path")
	gobin := filepath.Join(gopath, "bin")
	if !strings.Contains(path, gobin) {
		log.Fatalf("Your PATH does not contain %s", gobin)
	}

	log.Println("Success!")
	log.Println("gopath: " + gopath)
	log.Println("gobin: " + gobin)
}
