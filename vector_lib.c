#include <vector_lib.h>

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

size_t	vector_len(void *vector[])
{
	size_t	i;

	if (vector == NULL)
		return (0);
	i = 0;
	while (vector[i] != NULL)
		++i;
	return (i);
}

int	vector_shift_right(void *vector[], size_t len, size_t n)
{
	if (vector == NULL)
		return (-1);
	if (n == 0)
		return (0);
	vector[len + n] = NULL;
	while (len)
	{
		--len;
		vector[len + n] = vector[len];
	}
	return (0);
}

int	vector_shift_left(void *vector[], size_t len, size_t n)
{
	size_t	i;

	if (vector == NULL || len < n)
		return (-1);
	if (n == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		vector[i] = vector[i + n];
		++i;
	}
	vector[i] = NULL;
	return (0);
}

int	vector_destroy(void *vector[], void (*del)(void *), size_t len)
{
	size_t	i;

	if (vector == NULL)
		return (-1);
	i = 0;
	if (del != NULL)
	{
		while (i < len)
		{
			del(vector[i]);
			++i;
		}
	}
	free(vector);
	return (0);
}

int	vector_reverse_all(void *vector[], size_t len)
{
	size_t	i;
	void	*tmp;

	if (vector == NULL)
		return (-1);
	if (!len)
		return (0);
	i = 0;
	while (i < len / 2)
	{
		tmp = vector[i];
		vector[i] = vector[len - i - 1];
		vector[len - i - 1] = tmp;
		++i;
	}
	return (0);
}

void	**vector_expand(void *vector[], size_t expansion_len)
{
	void	**tmp;
	size_t	i;

	if (vector == NULL)
		return (NULL);
	tmp = malloc(sizeof(void *) * (expansion_len + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (i < expansion_len + 1)
	{
		tmp[i] = NULL;
		++i;
	}
	vector_copy_addr_n(tmp, vector, expansion_len);
	return (tmp);
}

void	**vector_copy_addr_n(void *dest[], void *src[], size_t n)
{
	size_t	i;

	if (dest == NULL || src == NULL || !n)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = NULL;
	return (dest);
}

void	**vector_deep_copy_n(void *dest[], void *src[], void *(*copy)(void *), size_t n)
{
	size_t	i;

	if (dest == NULL || src == NULL || !n || copy == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = copy(src[i]);
		++i;
	}
	dest[i] = NULL;
	return (dest);
}

int	vector_del_n(void *vector[], size_t len, void (*del)(void *), size_t n)
{
	size_t	i;

	if (vector == NULL)
		return (-1);
	i = 0;
	if (del == NULL)
	{
		if (len < n)
			return (-1);
		return (vector_shift_left(vector, len, n));
	}
	while (i < n)
		del(vector[i++]);
	return (vector_shift_left(vector, len, i));
}

int	vector_insert(void *vector[], size_t len, void *addr)
{
	if (vector == NULL || addr == NULL)
		return (-1);
	vector_shift_right(vector, len, 1);
	vector[0] = addr;
	return (0);
}

int	vector_insert_vector_n(void *vector[], size_t len, void *addr[], size_t n)
{
	if (vector == NULL || addr == NULL || !n)
		return (-1);
	vector_shift_right(vector, len, n);
	vector_copy_addr_n(vector, addr, n);
	return (0);
}

