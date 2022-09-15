#include <argv.h>

int	argv_del_one(argv_t *argv, size_t index, void (*del)(void *))
{
	if (argv == NULL || argv->len <= index)
		return (-1);
	if (-1 != array_del_one(&argv->array[index], del))
	{
		--argv->len;
		return (1);
	}
	return (-1);
}

int	argv_del_all(argv_t *argv, void (*del)(void *))
{
	int	res;

	if (argv == NULL)
		return (-1);
	res = array_del_all(argv->array, del);
	if (-1 != res)
	{
		argv->len -= res;
		return (res);
	}
	return (-1);
}

int	argv_del_n(argv_t *argv, size_t index, void (*del)(void *), size_t n)
{
	int	res;

	if (argv == NULL || argv->len <= index + n || !n)
		return (-1);
	res = array_del_n(&argv->array[index], del, n);
	if (-1 != res)
	{
		argv->len -= res;
		return (res);
	}
	return (-1);
}
