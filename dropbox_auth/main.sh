curl -X POST https://content.dropboxapi.com/2/files/upload \
    --header "Authorization: Bearer <token here>" \
    --header "Dropbox-API-Arg: {\"path\": \"/test.txt\",\"mode\": \"add\",\"autorename\": true,\"mute\": false,\"strict_conflict\": false}" \
    --header "Content-Type: application/octet-stream" \
    --data-binary @./main.sh
