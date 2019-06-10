// gcc main.c `pkg-config --libs --cflags libusb-1.0`

#include <libusb.h>
#include <stdio.h>

int	main(void)
{
	int				init = 0;
	ssize_t			err = 0;
	libusb_context	*ctx = NULL;
	libusb_device	**list = NULL;

	init = libusb_init(&ctx);

	if (init != 0)
		return (-1);

	if ((err = libusb_get_device_list(ctx, &list)) < 0) {
		libusb_strerror(err);
	}

	printf("%d\n", err);

	return (0);
}
