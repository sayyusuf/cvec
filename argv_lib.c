#include <argv_lib.h>

int	argv_destroy(argv_t *argv, void (*del)(void *))
{
	if (argv == NULL)
		return (-1);
	vector_destroy(argv->vector, del, argv->len);
	free(argv);
	return (0);
}

int	argv_try(argv_t *argv, void *addr, size_t index, int (*fptr)(void *, void *))
{
	if (argv == NULL || addr == NULL || fptr == NULL || argv->len <= index)
		return (-1);
	while (index < argv->len)
	{
		if (fptr(argv->vector[index], addr) == argv->try_condition)
		{
			argv->try_index = index;
			return (0);
		}
		++index;
	}
	return (-1);
}

argv_t	*argv_cut(argv_t *argv, size_t index, size_t n)
{
	argv_t	*ret;

	if (argv == NULL || n == 0 || argv->len <= index || argv->len < index + n || !n)
		return (NULL);
	ret = argv_new(NULL, NULL);
	argv_insert_vector_n(ret, 0, &argv->vector[index], n);
	argv_del_n(argv, index, NULL, n);
	return (ret);
}

argv_t	*argv_new(void *vector[], void *(*fptr)(void *))
{
	argv_t	*argv;
	size_t	vector_l;

	vector_l = vector_len(vector);
	argv = malloc(sizeof(argv_t));
	if (argv == NULL)
		return (NULL);
	argv->try_index = 0;
	argv->try_condition = 0;
	argv->len = vector_l;
	argv->capacity = 0;
	if (fptr == NULL)
	{
		argv->vector = vector_expand(vector, 1 << find_max_bit(argv->len));
		if (argv->vector != NULL)
			argv->capacity = 1 << find_max_bit(argv->len);
	}	
	else
	{
		argv->vector = vector_expand(NULL, argv->capacity);
		vector_deep_copy_n(argv->vector, vector, fptr, vector_l);
	}
	return (argv);
}

int	argv_del_one(argv_t *argv, size_t index, void (*del)(void *))
{
	if (argv == NULL || argv->len <= index)
		return (-1);
	if (0 < vector_del_n(&argv->vector[index], argv->len - index, del, 1))
		return (-1);
	--argv->len;
	return (0);
}

int	argv_del_all(argv_t *argv, void (*del)(void *))
{
	if (argv == NULL)
		return (-1);
	if (0 < vector_del_n(argv->vector, argv->len, del, argv->len))
		return (-1);
	argv->len -= 0;
	return (0);
}

int	argv_del_n(argv_t *argv, size_t index, void (*del)(void *), size_t n)
{
	if (argv == NULL || argv->len <= index || argv->len < index + n || !n)
		return (-1);
	if (0 < vector_del_n(&argv->vector[index], argv->len - index, del, n))
		return (-1);
	argv->len -= n;
	return (0);
}

int	argv_insert(argv_t *argv, size_t index, void *addr)
{
	if (argv == NULL || addr == NULL || argv->len <= index)
		return (-1);
	argv_check_capacity(argv, argv->len + 1);
	if (0 < vector_insert(&argv->vector[index], argv->len - index, addr))
		return (-1);
	++argv->len;
	return (0);
}

int	argv_insert_vector(argv_t *argv, size_t index, void *addr[])
{
	size_t	len;

	if (argv == NULL || addr == NULL || argv->len <= index)
		return (-1);
	len = vector_len(addr);
	argv_check_capacity(argv, argv->len + len);
	if (0 < vector_insert_vector_n(&argv->vector[index], argv->len - index, addr, len))
		return (-1);
	argv->len += len;
	return (0);
}

int	argv_insert_vector_n(argv_t *argv, size_t index, void *addr[], size_t n)
{
	size_t	len;

	if (argv == NULL || addr == NULL || argv->len <= index || !n)
		return (-1);
	len = vector_len(addr);
	if (len < n)
		return (-1);
	argv_check_capacity(argv, argv->len + n);
	if (0 < vector_insert_vector_n(&argv->vector[index], argv->len - index, addr, n))
		return (-1);
	argv->len += n;
	return (0);
}

int	argv_push(argv_t *argv, void *addr)
{
	if (argv == NULL || addr == NULL)
		return (-1);
	argv_check_capacity(argv, argv->len + 1);
	argv->vector[argv->len] = addr;
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
		tmp = argv->vector[argv->len - 1];
		argv->vector[argv->len - 1] = NULL;
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
		if (argv->vector[i++] == addr)
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
		if (!ex_len)
			ex_len = 1;
		ex_len *= 2;
		if (ex_len <= len)
			continue ;
		tmp = vector_expand(argv->vector, ex_len);
		if (tmp == NULL)
			return (-1);
		argv->capacity = ex_len;
		free(argv->vector);
		argv->vector = tmp;
		break ;
	}
	return (0);
}

int	argv_reverse(argv_t	*argv)
{
	if (argv == NULL)
		return (-1);
	return (vector_reverse_all(argv->vector, argv->len));
}
