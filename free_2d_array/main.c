#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void	free_2d_array(char **array)
{
	for (size_t idx = 0; array[idx]; idx++) {
		free(array[idx]);
		array[idx] = NULL;
	}

	free(array);
	array = NULL;
}

static void	print_2d_array(char **array)
{
	if (array == NULL) {
		printf("NULL");
		return ;
	}

	printf("[ ");

	for (int idx = 0; array[idx]; idx++) {
		if (array[idx +1] == NULL) {
			printf("[ %s ] ", array[idx]);
		} else {
			printf("[ %s ], ", array[idx]);
		}
	}

	printf(" ]");
}

int main(void)
{
	char **array = NULL;

	array = calloc(sizeof(char *), 10);
	if (array == NULL)
		return (-1);

	for (int i = 0; i < 9; i++) {
		array[i] = strdup("Hello");
	}

	print_2d_array(array);
	free_2d_array(array);

}
