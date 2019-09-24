package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"path/filepath"
)

func main() {
	// Create new pdf document
	//pdf := gofpdf.New("P", "mm", "A4", "")

	files, err := ioutil.ReadDir("./")
	if err != nil {
		log.Fatal(err)
	}

	for _, f := range files {
		if filepath.Ext(f.Name()) == ".jpg" {
			fmt.Println(f.Name())
		}
	}

	pdf.AddPage()
	//pdf.Image("001.jpg", 5, 0, 200, 0, false, "", 0, "")
	//pdf.AddPage()
	//pdf.Image("002.jpg", 5, 0, 200, 0, false, "", 0, "")
	//fileStr := "Fpdf_Image.pdf"
	//pdf.OutputFileAndClose(fileStr)
}
