// Sample program to show how to show you how to briefly work
// with the sql package.
package main

import (
	"database/sql"

	_ "dbdriver/postgres"
)

// main is the entry point for the application.
func main() {
	db, err := sql.Open("postgres", "mydb")
	println((db))
	println(err)
}
