#include <defer.h>
#include <stdlib.h>
#include <stdio.h>

void	alloc()
{
	defer_scope_begin();
	char *test = (char *)malloc(10);
	if (test == NULL) {
		printf("Alloc failure !");
		return ;
	}
	defer(free, test);

	test[1] = 'd';
}

int	main()
{
	alloc();
}
