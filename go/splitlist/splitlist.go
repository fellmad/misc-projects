package main

import (
	"log"
	"os"
	"path/filepath"
)

func main() {
	path := os.Getenv("PATH")
	log.Println("path:", path)
	dirs := filepath.SplitList(path)
	for dir := range dirs {
		log.Println(dirs[dir])
	}
}
