#include <stdio.h>
#include <curl/curl.h>

int main(void)
{
	CURL				*curl;
	CURLcode			res;
	struct curl_slist	*chunk = NULL;
	char				*data = "Hello\n";

  	curl_global_init(CURL_GLOBAL_ALL);

  	curl = curl_easy_init();

  	if(curl) {

		// data to send (set size and content)
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 6L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

		// append all header
		chunk = curl_slist_append(chunk, "Authorization: Bearer <token here>");
		chunk = curl_slist_append(chunk, "Dropbox-API-Arg: {\"path\": \"/filename\",\"mode\": \"add\",\"autorename\": true,\"mute\": false,\"strict_conflict\": false}");
		chunk = curl_slist_append(chunk, "Content-Type: application/octet-stream");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    	curl_easy_setopt(curl, CURLOPT_URL, "https://content.dropboxapi.com/2/files/upload");

    	/* Perform the request, res will get the return code */ 
    	res = curl_easy_perform(curl);
    	/* Check for errors */ 
    	if(res != CURLE_OK)
      		fprintf(stderr, "curl_easy_perform() failed: %s\n",
              		curl_easy_strerror(res));

    	/* always cleanup */ 
    	curl_easy_cleanup(curl);
  	}
  	curl_global_cleanup();
  	return 0;
}
