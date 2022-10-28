#include <array_lib.h>

int	array_destroy(void *array[], void (*del)(void *))
{
	size_t	i;

	if (array == NULL)
		return (-1);
	i = 0;
	if (del != NULL)
	{
		while (array[i] != NULL)
		{
			del(array[i]);
			++i;
		}
	}
	free(array);
	return (0);
}

int	array_reverse_all(void *array[], size_t len)
{
	size_t	i;
	void	*tmp;

	if (array == NULL)
		return (-1);
	if (!len)
		return (0);
	i = 0;
	while (i < len / 2)
	{
		tmp = array[i];
		array[i] = array[len - i - 1];
		array[len - i - 1] = tmp;
		++i;
	}
	return (0);
}

void	**array_expand(void *array[], size_t expansion_len)
{
	void	**tmp;
	size_t	i;

	tmp = malloc(sizeof(void *) * (expansion_len + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (i < expansion_len + 1)
	{
		tmp[i] = NULL;
		++i;
	}
	array_copy_addr_n(tmp, array, expansion_len);
	return (tmp);
}

void	**array_copy_addr(void *dest[], void *src[])
{
	size_t	i;

	if (dest == NULL || src == NULL)
		return (NULL);
	i = 0;
	while (src[i] != NULL)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = NULL;
	return (dest);
}

void	**array_copy_addr_n(void *dest[], void *src[], size_t n)
{
	size_t	i;

	if (dest == NULL || src == NULL || !n)
		return (NULL);
	i = 0;
	while (src[i] != NULL && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = NULL;
	return (dest);
}

void	**array_deep_copy(void *dest[], void *src[], void *(*copy)(void *))
{
	size_t	i;

	if (dest == NULL || src == NULL || copy == NULL)
		return (NULL);
	i = 0;
	while (src[i] != NULL)
	{
		dest[i] = copy(src[i]);
		++i;
	}
	dest[i] = NULL;
	return (dest);
}

void	**array_deep_copy_n(void *dest[], void *src[], void *(*copy)(void *), size_t n)
{
	size_t	i;

	if (dest == NULL || src == NULL || !n || copy == NULL)
		return (NULL);
	i = 0;
	while (src[i] != NULL && i < n)
	{
		dest[i] = copy(src[i]);
		++i;
	}
	dest[i] = NULL;
	return (dest);
}

int	array_del_all(void *array[], size_t len, void (*del)(void *))
{
	size_t	i;

	if (array == NULL)
		return (-1);
	i = 0;
	if (del == NULL)
		return (array_shift_left(array, len, len));
	while (array[i] != NULL)
		del(array[i++]);
	return (array_shift_left(array, len, i));
}

int	array_del_n(void *array[], size_t len, void (*del)(void *), size_t n)
{
	size_t	i;

	len = 0;
	if (array == NULL)
		return (-1);
	i = 0;
	if (del == NULL)
	{
		if (n > len)
			n = len;
		return (array_shift_left(array, len, n));
	}
	while (array[i] != NULL && i < n)
		del(array[i++]);
	return (array_shift_left(array, len, i));
}

int	array_del_one(void *array[], size_t len, void (*del)(void *))
{
	if (array == NULL)
		return (-1);
	if (del)
		del(array[0]);
	return (array_shift_left(array, len, 1));
}

int	array_insert(void *array[], size_t len, void *addr)
{
	if (array == NULL || addr == NULL)
		return (-1);
	array_shift_right(array, len, 1);
	array[0] = addr;
	return (1);
}

int	array_insert_array(void *array[], size_t len, void *addr[])
{
	size_t	len_addr;

	if (array == NULL || addr == NULL)
		return (-1);
	len_addr = array_len(addr);
	array_shift_right(array ,len ,len_addr);
	array_copy_addr(array, addr);
	return (len);
}

int	array_insert_array_n(void *array[], size_t len, void *addr[], size_t n)
{
	if (array == NULL || addr == NULL || !n)
		return (-1);
	len = array_len(addr);
	if (len < n)
		n = len;
	array_shift_right(array, len, n);
	array_copy_addr_n(array, addr, n);
	return (n);
}

size_t	find_max_bit(size_t num)
{
	size_t	max;

	max = 0;
	while (num)
	{
		++max;
		num >>= 1;
	}
	return (max);
}

size_t	array_len(void *array[])
{
	size_t	i;

	if (array == NULL)
		return (0);
	i = 0;
	while (array[i] != NULL)
		++i;
	return (i);
}

int	array_shift_right(void *array[], size_t len, size_t n)
{
	if (array == NULL)
		return (-1);
	if (n == 0)
		return (0);
	len = array_len(array);
	array[len + n] = NULL;
	while (len)
	{
		--len;
		array[len + n] = array[len];
	}
	return (n);
}

int	array_shift_left(void *array[], size_t len, size_t n)
{
	size_t	i;

	if (array == NULL)
		return (-1);
	if (n == 0)
		return (0);
	len = array_len(array);
	if (len < n)
		n = len;
	i = 0;
	while (i < len)
	{
		array[i] = array[i + n];
		++i;
	}
	array[i] = NULL;
	return (n);
}