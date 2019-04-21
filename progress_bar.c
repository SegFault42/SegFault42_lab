#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#define BUFF_SIZE 1024

typedef void (*ptrProgressBar)(double, double);

void	progressBar(double TotalToDownload, double NowDownloaded)
{
	// ensure that the file to be downloaded is not empty
    // because that would cause a division by zero error later on
    if (TotalToDownload <= 0.0) {
        return ;
    }

    // how wide you want the progress meter to be
    int totaldotz=80;
    double fractiondownloaded = NowDownloaded / TotalToDownload;
    // part of the progressmeter that's already "full"
    int dotz = round(fractiondownloaded * totaldotz);

    // create the "meter"
    int ii=0;
    printf("%3.0f%% [",fractiondownloaded*100);
    // part  that's full already
    for ( ; ii < dotz;ii++) {
        printf("=");
    }
    // remaining part (spaces)
    for ( ; ii < totaldotz;ii++) {
        printf(" ");
    }
    // and back to line begin - do not forget the fflush to avoid output buffering problems!
    printf("]\r");
    fflush(stdout);

    return ;
}

bool	copyFile(const char *dest, const char *src, ptrProgressBar progress)
{
	int		fd_src = 0;
	int		fd_dest = 0;
	ssize_t	ret = 0;
	char	buff[BUFF_SIZE] = {0};

	fd_src = open(src, O_RDONLY);
	if (fd_src == -1) {
		return (false);
	}

	fd_dest = open(dest, O_RDWR | O_TRUNC | O_CREAT, 0600);
	if (fd_dest == -1) {
		close(fd_src);
		return (false);
	}

	double downNow = 0;
	while ((ret = read(fd_src, &buff, BUFF_SIZE)) > 0) {
		downNow += ret;
		if (progress != NULL)
			(*progress)(61650901, downNow);
		write(fd_dest, buff, ret);
	}

	close(fd_src);
	close(fd_dest);

	return (true);
}

int main(void)
{
	copyFile("dest", "/home/segfault42/Downloads/Crypt of the NecroDancer [0100CEA007D08800][v196608][SwitchBounty].nsp", progressBar);
}
