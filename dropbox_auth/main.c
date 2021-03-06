#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define REQUEST_LENGHT 101

size_t func(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	return size * nmemb;
}

int main(void)
{
	CURL				*curl;
	CURLcode			res;
	struct curl_slist	*chunk = NULL;
	char				*data = "Hello\n";
	char				*filename = "/file.txt";
	char				*filename_request = NULL;

	filename_request = (char *)calloc(REQUEST_LENGHT + strlen(filename) + 1, sizeof(char));
	if (filename_request == NULL) {
		return (-1);
	}

	sprintf(filename_request, "Dropbox-API-Arg: {\"path\": \"%s\",\"mode\": \"add\",\"autorename\": true,\"mute\": false,\"strict_conflict\": false}", filename);

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();

	if(curl) {

		// data to send (set size and content)
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 6L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

		// silent output
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &func);

		// append all header
		chunk = curl_slist_append(chunk, "Authorization: Bearer _G3bZFuCKiAAAAAAAAAADbubss3eXFcWBIJb5awT7_zNVKUuh68WHN_G8BHsPbpc");
		chunk = curl_slist_append(chunk, filename_request);
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
	curl_slist_free_all(chunk);

	free(filename_request);
  	return 0;
}
