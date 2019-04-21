#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct my_struct
{
	int a;
	char *b;
	char *c;
}				my_struct;

int main(void)
{
	my_struct *struc;

	struc = (my_struct *)malloc(sizeof(my_struct));

	printf("%p\n%p\n%p\n", &struc->a, &struc->b, &struc->c);

	struc->a = 42;
	struc->b = strdup("hello world");

	printf("\n%p\n%p\n%p\n", &struc->a, &struc->b, &struc->c);
	printf("%s\n%s\n", struc->b, struc->c);
	printf("size = %ld\n", sizeof(my_struct));
}
