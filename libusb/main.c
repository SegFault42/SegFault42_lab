// gcc main.c `pkg-config --libs --cflags libusb-1.0`

#include <libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

static void init_daemon()
{
	pid_t pid;

	/* Fork off the parent process */
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);

	/* Success: Let the parent terminate */
	if (pid > 0)
		exit(EXIT_SUCCESS);

	printf("%d\n", pid);

	/* On success: The child process becomes session leader */
	if (setsid() < 0)
		exit(EXIT_FAILURE);

	/* Catch, ignore and handle signals */
	/*TODO: Implement a working signal handler */
	signal(SIGCHLD, SIG_IGN);
	signal(SIGHUP, SIG_IGN);

	/* Fork off for the second time*/
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);

	/* Success: Let the parent terminate */
	if (pid > 0)
		exit(EXIT_SUCCESS);

	/* Set new file permissions */
	umask(0);

	/* Change the working directory to the root directory */
	/* or another appropriated directory */
	chdir("/");

	printf("%d\n", pid);
	/* Close all open file descriptors */
	// int x;
	// for (x = sysconf(_SC_OPEN_MAX); x >= 0; x--)
	// {
	// 	close(x);
	// }

	/* Open the log file */
	openlog("firstdaemon", LOG_PID, LOG_DAEMON);
}

int my_detect_usb_periph()
{
	libusb_context *context = NULL;
	libusb_device **list = NULL;
	int err = 0;
	ssize_t count = 0;

	syslog(LOG_NOTICE, "[PID] : [%d]\n", getppid());

	err = libusb_init(&context);
	if (err != 0)
	{
		return (err);
	}

	count = libusb_get_device_list(context, &list);
	assert(count > 0);

	for (size_t idx = 0; idx < count; ++idx)
	{
		libusb_device *device = list[idx];
		struct libusb_device_descriptor desc = {0};

		err = libusb_get_device_descriptor(device, &desc);
		if (err != 0)
		{
			return (err);
		}
		syslog(LOG_NOTICE, "Vendor:Device = %04x:%04x\n", desc.idVendor, desc.idProduct);
		// printf("Vendor:Device = %04x:%04x\n", desc.idVendor, desc.idProduct);
	}

	libusb_free_device_list(list, count);
	libusb_exit(context);

	return (0);
}

int main()
{
	int err = 0;

	init_daemon();
	syslog(LOG_NOTICE, "daemon started.");

	while (1)
	{
		my_detect_usb_periph();
		sleep(3);
	}

	syslog(LOG_NOTICE, "daemon terminated.");
	closelog();

	return EXIT_SUCCESS;
}