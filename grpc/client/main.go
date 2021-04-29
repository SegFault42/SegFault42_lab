package main

import (
	"context"
	"log"
	"strconv"
	"time"

	"grpc/pkg/proto/credit"

	"google.golang.org/grpc"

	binance "github.com/adshao/go-binance/v2"
	api "github.com/segfault42/binance-api"
)

var wsPairInfo binance.WsAggTradeEvent

func main() {
	log.Println("Client running ...")

	api.WsGetCoinPrice("BNBBUSD", &wsPairInfo)
	for {
		if wsPairInfo.Price != "" {
			break
		}
	}

	conn, err := grpc.Dial(":50051", grpc.WithInsecure(), grpc.WithBlock())
	if err != nil {
		log.Fatalln(err)
	}
	defer conn.Close()

	client := credit.NewCreditServiceClient(conn)
	oldPrice := 0.0

	for {

		price, _ := strconv.ParseFloat(wsPairInfo.Price, 64)
		if price == oldPrice {
			continue
		}
		oldPrice = price
		request := &credit.CreditRequest{Amount: float32(price)}

		ctx, cancel := context.WithTimeout(context.Background(), time.Second)
		defer cancel()

		response, err := client.Credit(ctx, request)
		if err != nil {
			log.Fatalln(err)
		}
		_ = response
	}
	// log.Println("Response:", response.GetConfirmation())
}
