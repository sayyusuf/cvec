#include <argv_lib.h>

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

	if (argv == NULL || n == 0 || argv->len <= index || argv->len < index + n || !n)
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

int	argv_del_one(argv_t *argv, size_t index, void (*del)(void *))
{
	if (argv == NULL || argv->len <= index)
		return (-1);
	if (-1 != array_del_one(&argv->array[index], argv->len - index, del))
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
	res = array_del_all(argv->array, argv->len, del);
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

	if (argv == NULL || argv->len <= index || argv->len < index + n || !n)
		return (-1);
	res = array_del_n(&argv->array[index], argv->len - index, del, n);
	if (-1 != res)
	{
		argv->len -= res;
		return (res);
	}
	return (-1);
}

int	argv_insert(argv_t *argv, size_t index, void *addr)
{
	if (argv == NULL || addr == NULL || argv->len <= index)
		return (-1);
	argv_check_capacity(argv, argv->len + 1);
	if (-1 == array_insert(&argv->array[index], argv->len - index, addr))
		return (-1);
	++argv->len;
	return (0);
}

int	argv_insert_array(argv_t *argv, size_t index, void *addr[])
{
	size_t	len;
	int		res;

	if (argv == NULL || addr == NULL || argv->len <= index)
		return (-1);
	len = array_len(addr);
	argv_check_capacity(argv, argv->len + len);
	res = array_insert_array(&argv->array[index], argv->len - index, addr);
	if (-1 == res)
		return (-1);
	argv->len += res;
	return (0);
}

int	argv_insert_array_n(argv_t *argv, size_t index, void *addr[], size_t n)
{
	size_t	len;
	int		res;

	if (argv == NULL || addr == NULL || argv->len <= index || !n)
		return (-1);
	len = array_len(addr);
	if (len < n)
		n = len;
	argv_check_capacity(argv, argv->len + n);
	res = array_insert_array_n(&argv->array[index], argv->len - index, addr, n);
	if (-1 == res)
		return (-1);
	argv->len += res;
	return (0);
}

int	argv_push(argv_t *argv, void *addr)
{
	if (argv == NULL || addr == NULL)
		return (-1);
	argv_check_capacity(argv, argv->len + 1);
	argv->array[argv->len] = addr;
	++argv->len;
	return (0);
}

void	*argv_pull(argv_t *argv)
{
	void	*tmp;

	if (argv == NULL)
		return (NULL);
	if (argv->len)
	{
		tmp = argv->array[argv->len - 1];
		argv->array[argv->len - 1] = NULL;
		--argv->len;
		return (tmp);
	}
	return (NULL);
}

int	argv_is_unique(argv_t *argv, void *addr)
{
	size_t	i;

	if (argv == NULL || addr == NULL)
		return (0);
	i = 0;
	while (i < argv->len)
		if (argv->array[i++] == addr)
			return (0);
	return (1);
}

int	argv_check_capacity(argv_t *argv, size_t len)
{
	void	**tmp;
	size_t	ex_len;

	if (argv == NULL || !len)
		return (-1);
	tmp = NULL;
	ex_len = argv->capacity;
	while (ex_len <= len)
	{
		ex_len *= 2;
		if (ex_len <= len)
			continue ;
		tmp = array_expand(argv->array, ex_len);
		if (tmp == NULL)
			return (-1);
		argv->capacity = ex_len;
		free(argv->array);
		argv->array = tmp;
		break ;
	}
	return (0);
}

int	argv_reverse(argv_t	*argv)
{
	if (argv == NULL)
		return (-1);
	return (array_reverse_all(argv->array, argv->len));
}
