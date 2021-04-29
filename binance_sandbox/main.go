package main

import (
	"fmt"
	"strconv"
	"time"

	api "github.com/SegFault42/binance-api"
	"github.com/adshao/go-binance/v2"
	"github.com/dariubs/percent"
	"github.com/yudai/pp"
)

func Velocity(ti, tf, vi, vf float64) float64 {

	// ti := 0.0
	// tf := 60.0
	// vi := 56519.32
	// vf := 56765.44
	// deltaV := vf - vi
	// deltaT := tf - ti

	// a := deltaV / deltaT

	return (vf - vi) / (tf - ti)
}

var pair string = "BTTBUSD"

func calculateVelocity(client api.ApiInfo) {

	for {
		now := time.Now()
		count := 60 * 24
		then := now.Add(time.Duration(-count) * time.Minute)

		last := then.Local().Unix() * 1000
		// now1 := time.Now().Unix() * 1000

		res, err := client.GetDepth(pair, "1m", last, 1)
		// res, err := client.GetAccountService()
		if err != nil {
			fmt.Println(err)
			return
		}
		// pp.Println(res)

		vi, _ := strconv.ParseFloat(res[0].Open, 64)
		res1, err := client.GetCurrentPrice(pair)

		// vf, _ := strconv.ParseFloat(res[0].Close, 64)
		vf, _ := strconv.ParseFloat(res1.Price, 64)

		// pp.Println(vi, vf)
		fmt.Printf("%.8f\n", Velocity(0.0, float64(count), vi, vf))
		fmt.Printf("%.2f%%\n\n", percent.ChangeFloat(vi, vf))

		time.Sleep(1 * time.Second)
	}
}

func lamboTrunk(client api.ApiInfo) {
	now := time.Now()
	count := (60 * 24) * 20
	then := now.Add(time.Duration(-count) * time.Minute)

	last := then.Local().Unix() * 1000
	// now1 := time.Now().Unix() * 1000

	res, err := client.GetDepth(pair, "1h", last, 1000)
	if err != nil {
		fmt.Println(err)
		return
	}

	wallet := 0.0
	oldHigh := 0.0
	status := ""

	for i, elem := range res {
		if i == 0 {
			oldHigh, _ = strconv.ParseFloat(elem.High, 64)
			wallet = oldHigh
			status = "bought"
			continue
		}

		curHigh, _ := strconv.ParseFloat(elem.High, 64)
		curOpen, _ := strconv.ParseFloat(elem.Open, 64)

		if status == "bought" && curHigh > oldHigh { // We hold
			wallet = curHigh
		} else if status == "bought" && curHigh < oldHigh { // We sold here cause the market goes down
			wallet, _ = strconv.ParseFloat(elem.Open, 64)
			status = "sold"
			fmt.Println("SOLD")
		} else if status == "sold" && curOpen > wallet { // We buy here cause the market goes up
			wallet = curOpen
			status = "bought"
			fmt.Println("BOUGHT")
		}

		// pp.Println(elem)
		pp.Println("Wallet: ", wallet)
		oldHigh = curHigh
	}

	// pp.Println(res)
}

func getAllHistory(client api.ApiInfo) {

	pair := "BTTBUSD"
	//client.Client.NewListOrdersService().StartTime(1615790306000).Limit(10).Symbol(pair).Do(context.Background())
	//res, err := client.Client.NewListOrdersService().Symbol(pair).Do(context.Background())
	//pp.Println(err)
	//pp.Println(len(res))
	last, err := client.GetLastFilledTransaction(pair)
	if err != nil {
		pp.Println(err)
	}
	pp.Println(last)
}

func testNet(client api.ApiInfo) {

	balances, err := client.GetBalances()
	if err != nil {
		pp.Println(err)
	}
	pp.Println(balances)
}

func getCoinAmount(client api.ApiInfo, coin string) (string, error) {
	balance, err := client.GetBalance(coin)
	if err != nil {
		return "", err
	}

	return balance.Free, nil
}

func buy(pair string, client api.ApiInfo) (float64, float64, error) {

	balance, err := getCoinAmount(client, "BTC")
	if err != nil {
		return 0.0, 0.0, err
	}
	pp.Println(balance)

	balance, err = getCoinAmount(client, "BUSD")
	if err != nil {
		return 0.0, 0.0, err
	}
	pp.Println(balance)

	//res, err := client.GetTickerPrices()
	//if err != nil {
	//pp.Println(err)
	//return 0.0, 0.0, err
	//}

	//pp.Println(res)

	resp, err := client.PlaceOrderMarket(binance.SideTypeBuy, pair, balance, "real")
	pp.Println(err, resp)

	//boughtAt, invest, err := getSynthese(resp)
	//if err != nil {
	//return 0.0, 0.0, nil
	//}

	//price, err := client.GetTickerPrice("BTCBUSD")
	//if err != nil {
	//return 0.0, 0.0, err
	//}
	//btcPrice, err := strconv.ParseFloat(price, 64)
	//if err != nil {
	//return 0.0, 0.0, nil
	//}
	//totalBUSD := btcPrice * invest

	//log.Printf("%s %s %s %.8f %s | %s %.8f %s %.2f %s\n", "💰 Bought", pair, "at :", boughtAt, "BTC", "Invested :", invest, "BTC |", totalBUSD, "$")

	return 0.0, 0.0, nil
}

func getLastTransaction(client api.ApiInfo) {
	resp, err := client.GetLastFilledTransaction("BNBBUSD")
	if err != nil {
		pp.Println(err)
		return
	}
	pp.Println(resp)
}

func getAllTransactions(client api.ApiInfo) {
	resp, err := client.GetOrdersHistory("BNBBUSD")
	if err != nil {
		pp.Println(err)
		return
	}

	for _, elem := range resp {
		if elem.Type == "MARKET" {
			pp.Println(elem)
		}
	}

}

func getPriceAtSpecificTime(client api.ApiInfo) {
	pp.Println(client.GetTransactionPriceAtTime("BNBBUSD", 1619692794756))
}

func main() {
	//binance.UseTestnet = true
	client := api.New()

	// calculateVelocity(client)
	//lamboTrunk(client)
	//getAllHistory(client)
	//buy("BTCBUSD", client)
	//getLastTransaction(client)
	// getAllTransactions(client)
	getPriceAtSpecificTime(client)
}
