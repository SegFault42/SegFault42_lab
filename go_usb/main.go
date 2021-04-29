package main

import (
	"log"

	"github.com/gotmc/libusb"
	"github.com/k0kubun/pp"
)

func main() {
	// ctx, _ := libusb.Init()
	ctx, _ := libusb.NewContext()
	defer ctx.Close()

	devices, _ := ctx.GetDeviceList()

	for _, device := range devices {
		usbDeviceDescriptor, err := device.GetDeviceDescriptor()
		if err != nil {
			pp.Println(err)
			continue
		}
		handle, _ := device.Open()
		defer handle.Close()
		snIndex := usbDeviceDescriptor.SerialNumberIndex
		serialNumber, _ := handle.GetStringDescriptorASCII(snIndex)
		log.Printf("Found S/N: %s", serialNumber)
	}
	pp.Println(len(devices))
}
