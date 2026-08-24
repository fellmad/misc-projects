package main

// os.getwd() ?
// os.chdir() ?
// ishidden? avoid .vscode dir for example...

import (
	"fmt"
	"log"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
)

func getFolders(startFolder string) []string {
	var folders = make([]string, 0)
	myError := filepath.Walk(startFolder, func(path string, info os.FileInfo, err error) error {
		if err != nil {
			return err
		}
		if !info.IsDir() {
			return nil
		}
		folders = append(folders, path)
		return nil
	})

	if myError != nil {
		printHelp()
		log.Fatalf("walk failed: %v\n", myError)
	}
	return folders
}

func printHelp() {
	fmt.Fprintf(os.Stderr, "usage: recurse <starting folder> <command>\n\n")
	fmt.Fprintf(os.Stderr, "command will be executed in starting folder and all its subfolders\n")
}

func main() {

	if len(os.Args) < 3 {
		printHelp()
		os.Exit(1)
	}

	startFolder := os.Args[1]
	arg := strings.Join(os.Args[2:], " ")
	// fmt.Printf("arg: %v\n", arg)

	folders := getFolders(startFolder)
	for _, folder := range folders {
		// fmt.Printf("folder: %v\n", folder)
		cmd := exec.Command("cmd.exe", "/c", arg)
		cmd.Dir = folder
		// log.Printf("cmd: %v", cmd)
		cmdErr := cmd.Run()
		if nil != cmdErr {
			log.Printf("command error: %v", cmdErr)
		}
	}
}
