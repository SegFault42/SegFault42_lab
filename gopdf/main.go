package main

import "github.com/jung-kurt/gofpdf"

func main() {
	pdf := gofpdf.New("P", "mm", "A4", "")
	pdf.AddPage()
	pdf.Image("001.jpg", 0, 0, 200, 0, false, "", 0, "")
	fileStr := "Fpdf_Image.pdf"
	pdf.OutputFileAndClose(fileStr)
}
