#include "./log/log.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fp = NULL;

	fp = fopen("debug.log", "a+");
	if (fp == NULL) {
		log_error("%s", strerror(errno));
		return (-1);
	}

	log_set_fp(fp);
	log_info("==================BEGINING OF SESSION !====================");

	log_info("Success !");

	log_info("=====================END OF SESSION !======================\n\n");

	fclose(fp);
}
