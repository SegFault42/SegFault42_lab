package main

import (
	"fmt"
	"os"
)

func unique(intSlice []string) []string {
	keys := make(map[string]bool)
	list := []string{}
	for _, entry := range intSlice {
		if _, value := keys[entry]; !value {
			keys[entry] = true
			list = append(list, entry)
		}
	}
	return list
}

func main() {

	fmt.Println("")
	lst := os.Args[1:]
	fmt.Println(lst)
	fmt.Println(len(lst))

	fmt.Println("")

	uniqueSlice := unique(lst)
	fmt.Println(uniqueSlice)

	fmt.Println(len(uniqueSlice))
}
