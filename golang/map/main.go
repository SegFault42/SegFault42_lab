package main

import "fmt"

func main() {
	var personMobileNo = map[string]string{
		"John":  "+33-8273658526",
		"Steve": "+1-8579822345",
		"David": "+44-9462834443",
	}

	fmt.Println(personMobileNo["John"])
}
