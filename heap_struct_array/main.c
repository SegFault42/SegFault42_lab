#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

static char	*to_hex_8(uint8_t key)
{
    char	*value = "00";
    char	*hex = "0123456789ABCDEF";

    value[0] = hex[(key >> 4) & 0xF];
    value[1] = hex[key & 0xF];

	return (value);
}


static char	*to_hex_16(uint16_t key)
{
	char	*value = "0000";

	strcpy(&value[0], to_hex_8((key >> 8) & 0xFF));
	strcpy(&value[2], to_hex_8(key & 0xFF));

	return (value);
}

static char	*to_hex_32(uint32_t key)
{
	char	*value = "00000000";

	strcpy(&value[0], to_hex_8((key >> 24) & 0xFF));
	strcpy(&value[2], to_hex_8((key >> 16) & 0xFF));
	strcpy(&value[4], to_hex_8((key >> 8) & 0xFF));
	strcpy(&value[6], to_hex_8(key & 0xFF));

	return (value);
}

static void	print_hex_value(void *addr)
{
	// print hex value and padding
	for (int i = 0; i < 16; i++) {
		printf("%s", to_hex_8(*(uint8_t *)addr));

		if (i == 7)
 			printf("  ");
		else
			printf(" ");

		addr++;
	}

	printf(" |");
}

static void	print_ascii_value(void *addr)
{
	// Print value in ascii
	for (int i = 0; i < 16; i++) {
		if (isprint(*(uint8_t *)addr))
			putchar(*(uint8_t *)addr);
		else
			putchar('.');

		addr++;
	}

	puts("|");
}


static void	print_offset(void *addr)
{
	// Print offset and padding
	printf("%s", to_hex_32((uint32_t)addr));
	printf("  ");
}


static void	hexdump(void *addr)
{
	print_offset(addr);
	print_hex_value(addr);
	print_ascii_value(addr);
}



typedef struct s_test
{
	char	**a;	// 8 bytes
	int		b;		// 4 bytes
	int		c;		// 4 bytes
}				t_test;
// This struct = 16 bytes
//
//   Contigous memory for t_test struct
//  v------a------v    v--b--v    v--c--v
// -----------------  ---------  ---------
// | | | | | | | | |  | | | | |  | | | | |
// -----------------  ---------  ---------

int main(void)
{
	t_test	*my_struct = NULL;
	size_t	nb_elem = 10;

	my_struct = (t_test *)realloc(my_struct, sizeof(t_test) * nb_elem);
	if (!my_struct) {
		return (-1);
	}

	my_struct[0].b = 42;

	printf("%x", my_struct[1].b);

	return (0);
}
