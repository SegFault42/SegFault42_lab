package main

import (
	"encoding/json"

	"github.com/go-pkgz/jrpc"
)

// Server wraps jrpc.Server and adds synced map to store data
type Puglin struct {
	*jrpc.Server
}

func main() {
	// create plugin (jrpc server)
	plugin := jrpcServer{
		Server: &jrpc.Server{
			API:        "/command",     // base url for rpc calls
			AuthUser:   "user",         // basic auth user name
			AuthPasswd: "password",     // basic auth password
			AppName:    "jrpc-example", // plugin name for headers
			Logger:     logger,
		},
	}

	plugin.Add("mycommand", func(id uint64, params json.RawMessage) Response {
		return jrpc.EncodeResponse(id, "hello, it works", nil)
	})
}
