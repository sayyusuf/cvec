
#include <stdlib.h>
#include <stddef.h>
#include <argv.h>


size_t find_max_bit(size_t num)
{
	size_t max;

	max = 0;
	while (num)
	{
		++max;
		num >>= 1;
	}
	return (max);
}
/*
	size_t tiüindeki bir sayının maksimum değerlikli bitini verir.
*/


size_t array_len(void *array[])
{
	size_t i;

	if (array == NULL)
		return (0);
	i = 0;
	while (array[i] != NULL)
		++i;
	return i;
}
/*
	verilen array'ın uzunlugunu verir
	hata durumları:
	1) parametre NULL ise 0 doner
	2 ) array'ın son parametresi NULL değil ise ölümcül hata olur
*/

int array_shift_right(void *array[], size_t n)
{
	size_t len;

	if (array == NULL)
		return (-1);
	if (n == 0)
		return (0);
	len  = array_len(array);
	array[len + n] = NULL; 
	while (len)
	{
		--len;
		array[len + n] = array[len];
	}
	return (n);
}
/*
	array'ı +n index kadar kaydırır başarılı ise n doner
	hata durumları:
	1) array NULL ise -1 doner
	2) array'ın son parametresi NULL değil ise ölümcül hata olur
	3) n == 0 ise 0

*/


int	array_shift_left(void *array[], size_t n)
{
		size_t	len;
		size_t	i;

		if (array == NULL)
			return (-1);
		if (n == 0)
			return (0);
		len  = array_len(array);
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
/*
	array'ı -n index kadar kaydırır ve (0 + n - 1)indexe kadar olanlar silinir  başarılı ise  kaydırdığı kadarı doner
	hata durumları:
	1) array NULL ise -1 doner
	2) array'ın son parametresi NULL değil ise ölümcül hata olur
	3) n == 0 ise 0
*/

int	array_destroy(void *array[], void (*dell)(void *))
{
	size_t	i;

	if (array == NULL)
		return (-1);
	i  = 0;
	if (dell != NULL)
		while (array[i] != NULL)
		{
			dell(array[i]);
			++i;
		}
	free(array);
	return (0);
}
/*
	array'ın tum elemanlarına dell != NULL ise dell fonksiyonu uygular ve array'den siler.  Enson arrayı free yapar. Başarılı ise  sildiği kadar geri doner
	hata durumları:
	1) array NULL ise -1 done
	2) array'ın son parametresi NULL değil ise ölümcül hata olur
*/

int	array_dell_all(void *array[], void (*dell)(void *))
{
	size_t	i;

	if (array == NULL)
		return (-1);
	i  = 0;
	if (dell == NULL)
		return (array_shift_left(array, array_len(array)));
	while (array[i] != NULL)
		dell(array[i++]);
	return (array_shift_left(array, i));
}
/*
	array'ın tum elemanlarına dell != NULL ise dell fonksiyonu uygular ve array'den siler. Başarılı ise  sildiği kadar geri doner
	hata durumları:
	1) array NULL ise -1 doner
	2) array'ın son parametresi NULL değil ise ölümcül hata olur
*/

int	array_dell_n(void *array[], void (*dell)(void *), size_t n)
{
	size_t	i;
	size_t	len;

	len = 0;
	if (array == NULL)
		return (-1);
	i  = 0;
	if (dell == NULL)
	{
		len = array_len(array);
		if (n > len)
			n = len;
		return (array_shift_left(array, n));
	}
	while (array[i] != NULL && i < n)
		dell(array[i++]);
	return (array_shift_left(array, i));
}

/*
	array'ın n kadar elemanına dell != NULL ise dell fonksiyonu uygular ve array'den siler. Başarılı ise  sildiği kadar geri doner
	hata durumları:
	1) array NULL ise -1 doner
	2) array'ın son parametresi NULL değil ise ölümcül hata olur
*/

int	array_dell_one(void *array[], void (*dell)(void *))
{
	if (array == NULL)
		return (-1);
	if (dell)
		dell(array[0]);
	return (array_shift_left(array, 1));
}
/*
	array'ın 0. elemanını dell != NULL ise dell fonksiyonu uygular ve array'den siler. Başarılı ise  sildiği kadar geri doner
	hata durumları:
	1) array NULL ise -1 doner
	2) array'ın son parametresi NULL değil ise ölümcül hata olur
*/

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
/*
	src'nin tüm elemanlarını dest'e copyalar ve başarılı ise dest'i döner
	hata durumları:
	1) src ==  NULL yada dest == NULL ise NULL doner
	2) src'nin son parametresi NULL değil ise ölümcül hata olur
*/

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
/*
	src'nin n kadar elemanını dest'e copyalar ve başarılı ise dest'i döner
	hata durumları:
	1) src ==  NULL yada dest == NULL ise NULL doner
	2) src'nin son parametresi NULL değil ise ölümcül hata olur
*/

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
/*
	src'nin tüm elemanlarını copy fonksiyonu ile  dest'e copyalar ve başarılı ise dest'i döner
	hata durumları:
	1) src ==  NULL yada dest == NULL ise NULL doner
	2) src'nin son parametresi NULL değil ise ölümcül hata olur
	3) copy == NULL ise NULL doner
*/

void	**array_deep_copy_n(void *dest[], void *src[], void *(*copy)(void *),  size_t n)
{
	size_t	i;

	if (dest == NULL || src == NULL || !n  || copy == NULL)
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
/*
	src'nin n kadar elemanını copy fonksiyonu ile  dest'e copyalar ve başarılı ise dest'i döner
	hata durumları:
	1) src ==  NULL yada dest == NULL ise NULL doner
	2) src'nin son parametresi NULL değil ise ölümcül hata olur
	3) copy == NULL ise NULL doner
*/

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
/*
	expansion_len + 1 kadar bir dizi oluşturu ve içine array'ı kopyalar ve yeni diziyi doner
	hata durumları:
	1) array ==  NULL ise NULL doner
	2) array'nin son parametresi NULL değil ise ölümcül hata olur
	3) malloc hatasında NULL doner
*/

int	array_insert(void *array[], void *addr)
{
	if (array == NULL || addr == NULL)
		return (-1);
	array_shift_right(array, 1);
	array[0] = addr;
	return (1);
}
/*
	array'ın 0. indexine   addr değerini yerletirir. Başarılı ise 1 doner
	hata durumları:
	1) array ==  NULL veya addr == NULL ise -1 doner
	2) array'nin son parametresi -1 değil ise ölümcül hata olur
	3) malloc hatasında -1 doner
*/

int	array_insert_array(void *array[], void *addr[])
{
	size_t	len;

	if (array == NULL || addr == NULL)
		return (-1);
	len = array_len(addr);
	array_shift_right(array, len);
	array_copy_addr(array, addr);
	return (len);
}
/*
	array'ın 0. indexinden itibaren  addr dizisini yerletirir. Başarılı ise addr_len doner
	hata durumları:
	1) array ==  NULL veya addr == NULL ise -1 doner
	2) array'nin yada addr'in son parametresi NULL değil ise ölümcül hata olur
	3) malloc hatasında -1 doner
*/

int	array_insert_array_n(void *array[], void *addr[], size_t n)
{
	size_t	len;

	if (array == NULL || addr == NULL || !n)
		return (-1);
	len = array_len(addr);
	if(len < n)
		n = len;
	array_shift_right(array, n);
	array_copy_addr_n(array, addr, n);
	return (n);
}
/*
	array'ın 0. indexinden itibaren  addr dizisinin n kadar elemanını yerletirir. Başarılı ise yerleştirdiği kadar doner
	hata durumları:
	1) array ==  NULL veya addr == NULL ise -1 doner
	2) array'nin yada addr'in son parametresi NULL değil ise ölümcül hata olur
	3) malloc hatasında -1 doner
*/

int	array_reverse_all(void * array[])
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
/*
	array'ın tüm elemanlarını tersine sırlar Başarılı ise 0
	hata durumları:
	1) array == NULL ise -1 doner
	2) array_len == 0 ise 0 doner
*/



int	argv_destroy(argv_t *argv, void (*dell)(void *))
{
	if (argv == NULL)
		return (-1);
	array_destroy(argv->array, dell);
	free(argv);
	return (0);
}

int	argv_dell_one(argv_t *argv, size_t index, void (*dell)(void *))
{
	if (argv == NULL || argv->len <= index)
		return (-1);
	if (-1 != array_dell_one(&argv->array[index], dell))
	{
		--argv->len;
		return (1);
	}
	return (-1);
}

int	argv_dell_all(argv_t *argv, void (*dell)(void *))
{
	int	res;

	if (argv == NULL)
		return (-1);
	res = array_dell_all(argv->array, dell);
	if (-1 != res)
	{
		argv->len -= res;
		return (res);
	}
	return (-1);
}


int	argv_dell_n(argv_t *argv, size_t index, void (*dell)(void *), size_t n)
{
	int res;

	if (argv == NULL || argv->len <= index + n  || !n)
		return (-1);
	res = array_dell_n(&argv->array[index], dell, n);
	if (-1 != res)
	{
		argv->len -= res;
		return (res);
	}
	return (-1);
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
	void **tmp;
	size_t ex_len;

	if (argv == NULL || !len)
		return (-1);
	tmp = NULL;
	ex_len = argv->capacity;
	while (ex_len <= len)
	{
		ex_len *= 2;
		if (ex_len <= len)
			continue;
		tmp = array_expand(argv->array, ex_len);
		if (tmp == NULL)
			return (-1);
		argv->capacity = ex_len;
		free(argv->array);
		argv->array = tmp;
		break;
	}
	return (0);
}

int	argv_insert(argv_t *argv, size_t index, void *addr)
{
	if (argv == NULL || addr == NULL || index > argv->len)
		return (-1);
	argv_check_capacity(argv, argv->len + 1);
	if (-1 == array_insert(&argv->array[index], addr))
		return (-1);
	++argv->len;
	return (0);
}


int	argv_insert_array(argv_t *argv, size_t index, void *addr[])
{
	size_t len;
	int	res;

	if (argv == NULL || addr == NULL || index > argv->len)
		return (-1);
	len = array_len(addr);
	argv_check_capacity(argv, argv->len + len);
	res = array_insert_array(&argv->array[index], addr);
	if (-1 == res)
		return (-1);
	argv->len += res;
	return (0);
}

int	argv_insert_array_n(argv_t *argv, size_t index, void *addr[], size_t n)
{
	size_t len;
	int	res;

	if (argv == NULL || addr == NULL || index > argv->len || !n)
		return (-1);
	len = array_len(addr);
	if (len < n)
		n = len;
	argv_check_capacity(argv, argv->len + n);
	res = array_insert_array_n(&argv->array[index], addr, n);
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

int	argv_try(argv_t *argv, void *addr, size_t index , int (*fptr)(void *, void *))
{

	if (argv == NULL || addr == NULL || fptr == NULL || argv->len <= index)
		return (-1);
	while(index < argv->len)
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

int	argv_reverse(argv_t	*argv)
{
	if (argv == NULL)
		return (-1);
	return(array_reverse_all(argv->array));
}

argv_t	*argv_splice(argv_t *argv, size_t index, size_t n)
{
	argv_t	*ret;

	if (argv == NULL || n == 0 || argv->len <= index + n)
		return NULL;
	ret = argv_new(NULL, NULL);
	argv_insert_array_n(ret, 0, &argv->array[index], n);
	argv_dell_n(argv, index, NULL, n);
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
