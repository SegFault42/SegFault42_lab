#include <stdio.h>
#include <errno.h>

int main(void)
{
	FILE	*fp = NULL;

	fp = fopen("test?file=ok", "wb");
	if (fp == NULL) {
		perror("fopen");
	} else {
		fclose(fp);
	}

	return (0);
}
