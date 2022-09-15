#include <array.h>

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

int	array_reverse_all(void *array[])
{
	size_t	len;
	size_t	i;
	void	*tmp;

	if (array == NULL)
		return (-1);
	len = array_len(array);
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
