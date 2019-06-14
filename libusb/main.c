// gcc main.c `pkg-config --libs --cflags libusb-1.0`

#include <libusb.h>
#include <stdio.h>

int	print_info(libusb_device *dev)
{
	struct libusb_device_descriptor	desc;
	int							r = 0;

	r = libusb_get_device_descriptor(dev, &desc);
	if (r < 0) {
		printf("libusb_get_device_descriptor() failed\n");
		return (-1);
	}

	printf("%x\n", desc.idVendor);

	return (0);
}

int	main(void)
{
	int				init = 0;
	ssize_t			dev = 0;
	libusb_context	*ctx = NULL;
	libusb_device	**list = NULL;

	init = libusb_init(&ctx);

	if (init < 0) {
		printf("Init failed\n");
		return (-1);
	}

	libusb_set_debug(ctx, 3);

	dev = libusb_get_device_list(ctx, &list);
	if (dev < 0) {
		libusb_strerror(dev);
	}

	printf("%d\n", dev);

	print_info(list[0]);

	libusb_free_device_list(list, 1);
	libusb_exit(ctx);
	return (0);
}
