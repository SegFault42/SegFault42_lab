package main

import (
	"encoding/json"
	"fmt"
)

type myStruct struct {
	Name     string `json:"name"`
	Lastname string `json:"lastname"`
	age      int    `json:"age"`
}

func main() {
	jsonString := `{
		"name":"Mickael",
		"lastname": "Dupont",
		"age": 19
	}`

	var reading myStruct
	err := json.Unmarshal([]byte(jsonString), &reading)
	if err != nil {
		panic(err)
	}

	fmt.Printf("%+v\n", reading)
}
