#include <array.h>

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

int	array_shift_right(void *array[], size_t n)
{
	size_t	len;

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

int	array_shift_left(void *array[], size_t n)
{
	size_t	len;
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
