
#include <stdlib.h>
#include <stdio.h>
#include "argv.h"
#include <string.h>

int main()
{
	argv_t *a = argv_new(NULL, NULL);
	size_t	i;

	printf("%lu | %lu | %p | %p\n", a->len, a->capacity, &a->array[0], &a->array[a->len]);
	printf("******\n");	
	i = 0;
	while(i < a->len)
		printf("%s\n", a->array[i++]);
	printf("**********\n");



	argv_push(a, strdup("hello"));
	printf("%lu | %lu | %p | %p\n", a->len, a->capacity, &a->array[0], &a->array[a->len]);
	printf("******\n");	
	i = 0;
	while(i < a->len)
		printf("%s\n", a->array[i++]);
	printf("**********\n");

	argv_push(a, strdup("world"));
	printf("%lu | %lu | %p | %p\n", a->len, a->capacity, &a->array[0], &a->array[a->len]);
	printf("******\n");	
	i = 0;
	while(i < a->len)
		printf("%s\n", a->array[i++]);
	printf("**********\n");


	argv_push(a, strdup("hii"));
	printf("%lu | %lu | %p | %p\n", a->len, a->capacity, &a->array[0], &a->array[a->len]);
	printf("******\n");	
	i = 0;
	while(i < a->len)
		printf("%s\n", a->array[i++]);
	printf("**********\n");

	argv_insert(a, 1, strdup("aloooo"));
	printf("%lu | %lu | %p | %p\n", a->len, a->capacity, &a->array[0], &a->array[a->len]);
	printf("******\n");	
	i = 0;
	while(i < a->len)
		printf("%s\n", a->array[i++]);
	printf("**********\n");

	
	printf("******\n");
	
	i = 0;
	while(i < a->len)
		printf("%s\n", a->array[i++]);
	printf("**********\n");
	perror("");
	if (0 == argv_try(a, "world",0, strcmp))
	{
		printf("deleted: %s\n", a->array[a->try_index]);
		argv_dell_one(a, a->try_index , free);
	}
	i = 0;
while(i < a->len)
		printf("%s\n", a->array[i++]);

printf("xxxxxxxxx**********\n");
	void *mm =  argv_pull(a);
	printf("%s\n\n", mm);
	free(mm);
	printf("%lu | %lu | %p | %p\n", a->len, a->capacity, &a->array[0], &a->array[a->len]);
	printf("%s\n\n", a->array[a->len - 1]);

	free(argv_pull(a));
	printf("%lu | %lu | %p | %p\n", a->len, a->capacity, &a->array[0], &a->array[a->len]);
	printf("%s\n\n", a->array[0]);
	argv_destroy(a, free);
	return 0;
}
