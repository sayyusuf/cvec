#include <array.h>

int	array_del_all(void *array[], void (*del)(void *))
{
	size_t	i;

	if (array == NULL)
		return (-1);
	i = 0;
	if (del == NULL)
		return (array_shift_left(array, array_len(array)));
	while (array[i] != NULL)
		del(array[i++]);
	return (array_shift_left(array, i));
}

int	array_del_n(void *array[], void (*del)(void *), size_t n)
{
	size_t	i;
	size_t	len;

	len = 0;
	if (array == NULL)
		return (-1);
	i = 0;
	if (del == NULL)
	{
		len = array_len(array);
		if (n > len)
			n = len;
		return (array_shift_left(array, n));
	}
	while (array[i] != NULL && i < n)
		del(array[i++]);
	return (array_shift_left(array, i));
}

int	array_del_one(void *array[], void (*del)(void *))
{
	if (array == NULL)
		return (-1);
	if (del)
		del(array[0]);
	return (array_shift_left(array, 1));
}
