package main

import (
	"log"
	"os"
	"path/filepath"
)

func getEnvPaths() []string {
	path := os.Getenv("path")
	dirs := filepath.SplitList(path)
	return dirs
}

func main() {
	dirs := getEnvPaths()
	for _, dir := range dirs {
		fileinfo, err := os.Stat(dir)
		if err != nil {
			log.Println(dir, err)
		} else {
			if !fileinfo.IsDir() {
				log.Println("not a folder:", dir, err)
			}
		}
	}
}
