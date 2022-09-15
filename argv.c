#include <argv.h>

int	argv_destroy(argv_t *argv, void (*del)(void *))
{
	if (argv == NULL)
		return (-1);
	array_destroy(argv->array, del);
	free(argv);
	return (0);
}

int	argv_try(argv_t *argv, void *addr, size_t index, int (*fptr)(void *, void *))
{
	if (argv == NULL || addr == NULL || fptr == NULL || argv->len <= index)
		return (-1);
	while (index < argv->len)
	{
		if (fptr(argv->array[index], addr) == argv->try_condition)
		{
			argv->try_index = index;
			return (0);
		}
		++index;
	}
	return (-1);
}

argv_t	*argv_splice(argv_t *argv, size_t index, size_t n)
{
	argv_t	*ret;

	if (argv == NULL || n == 0 || argv->len <= index + n)
		return (NULL);
	ret = argv_new(NULL, NULL);
	argv_insert_array_n(ret, 0, &argv->array[index], n);
	argv_del_n(argv, index, NULL, n);
	return (ret);
}

argv_t	*argv_new(void *array[], void *(*fptr)(void *))
{
	argv_t	*argv;

	argv = malloc(sizeof(argv_t));
	if (argv == NULL)
		return (NULL);
	argv->try_index = 0;
	argv->try_condition = 0;
	argv->len = array_len(array);
	argv->capacity = 1 << find_max_bit(argv->len);
	if (fptr == NULL)
		argv->array = array_expand(array, argv->capacity);
	else
	{
		argv->array = array_expand(NULL, argv->capacity);
		array_deep_copy(argv->array, array, fptr);
	}
	return (argv);
}
