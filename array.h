#ifndef ARRAY_H
# define ARRAY_H
# include <stdlib.h>
# include <stddef.h>

size_t	find_max_bit(size_t num);
/*
	girilen sayının maximum degerlikli bitinin index + 1 degerini doner
*/

size_t	array_len(void *array[]);
/*
	verilen array'ın uzunlugunu verir
	hata durumları:
	1) parametre NULL ise 0 doner
	2 ) array'ın son parametresi NULL değil ise ölümcül hata olur
*/

int		array_shift_right(void *array[], size_t n);
/*
	array'ı +n index kadar kaydırır başarılı ise n doner
	hata durumları:
	1) array NULL ise -1 doner
	2) array'ın son parametresi NULL değil ise ölümcül hata olur
	3) n == 0 ise 0

*/

int		array_shift_left(void *array[], size_t n);
/*
	array'ı -n index kadar kaydırır ve (0 + n - 1)indexe kadar olanlar silinir
		başarılı ise  kaydırdığı kadarı doner
	hata durumları:
	1) array NULL ise -1 doner
	2) array'ın son parametresi NULL değil ise ölümcül hata olur
	3) n == 0 ise 0
*/

int		array_destroy(void *array[], void (*del)(void *));
/*
	array'ın tum elemanlarına del != NULL ise
		del fonksiyonu uygular ve array'den siler.
		Sonra arrayı free yapar. Başarılı ise  sildiği kadar geri doner
	hata durumları:
	1) array NULL ise -1 done
	2) array'ın son parametresi NULL değil ise ölümcül hata olur
*/

int		array_del_all(void *array[], void (*del)(void *));
/*
	array'ın tum elemanlarına del != NULL ise
		del fonksiyonu uygular ve array'den siler.
		Başarılı ise  sildiği kadar geri doner
	hata durumları:
	1) array NULL ise -1 doner
	2) array'ın son parametresi NULL değil ise ölümcül hata olur
*/

int		array_del_n(void *array[], void (*del)(void *), size_t n);
/*
	array'ın n kadar elemanına del != NULL ise del fonksiyonu uygular ve
		array'den siler. Başarılı ise  sildiği kadar geri doner
	hata durumları:
	1) array NULL ise -1 doner
	2) array'ın son parametresi NULL değil ise ölümcül hata olur
*/

int		array_del_one(void *array[], void (*del)(void *));
/*
	array'ın 0. elemanını del != NULL ise del fonksiyonu uygular ve
		array'den siler. Başarılı ise  sildiği kadar geri doner
	hata durumları:
	1) array NULL ise -1 doner
	2) array'ın son parametresi NULL değil ise ölümcül hata olur
*/

void	**array_copy_addr(void *dest[], void *src[]);
/*
	src'nin tüm elemanlarını dest'e copyalar ve başarılı ise dest'i döner
	hata durumları:
	1) src ==  NULL yada dest == NULL ise NULL doner
	2) src'nin son parametresi NULL değil ise ölümcül hata olur
*/

void	**array_copy_addr_n(void *dest[], void *src[], size_t n);
/*
	src'nin n kadar elemanını dest'e copyalar ve başarılı ise dest'i döner
	hata durumları:
	1) src ==  NULL yada dest == NULL ise NULL doner
	2) src'nin son parametresi NULL değil ise ölümcül hata olur
*/

void	**array_deep_copy(void *dest[], void *src[], void *(*copy)(void *));
/*
	src'nin tüm elemanlarını copy fonksiyonu ile  dest'e copyalar ve
		başarılı ise dest'i döner
	hata durumları:
	1) src ==  NULL yada dest == NULL ise NULL doner
	2) src'nin son parametresi NULL değil ise ölümcül hata olur
	3) copy == NULL ise NULL doner
*/

void	**array_deep_copy_n(void *dest[], void *src[], void *(*copy)(void *), size_t n);
/*
	src'nin n kadar elemanını copy fonksiyonu ile  dest'e copyalar ve başarılı ise dest'i döner
	hata durumları:
	1) src ==  NULL yada dest == NULL ise NULL doner
	2) src'nin son parametresi NULL değil ise ölümcül hata olur
	3) copy == NULL ise NULL doner
*/

void	**array_expand(void *array[], size_t expansion_len);
/*
	expansion_len + 1 kadar bir dizi oluşturu ve içine array'ı kopyalar ve yeni diziyi doner
	hata durumları:
	1) array ==  NULL ise NULL doner
	2) array'nin son parametresi NULL değil ise ölümcül hata olur
	3) malloc hatasında NULL doner
*/

int		array_insert(void *array[], void *addr);
/*
	array'ın 0. indexine   addr değerini yerletirir. Başarılı ise 1 doner
	hata durumları:
	1) array ==  NULL veya addr == NULL ise -1 doner
	2) array'nin son parametresi -1 değil ise ölümcül hata olur
	3) malloc hatasında -1 doner
*/

int		array_insert_array(void *array[], void *addr[]);
/*
	array'ın 0. indexinden itibaren  addr dizisini yerletirir.
		Başarılı ise addr_len doner
	hata durumları:
	1) array ==  NULL veya addr == NULL ise -1 doner
	2) array'nin yada addr'in son parametresi NULL değil ise ölümcül hata olur
	3) malloc hatasında -1 doner
*/

int		array_insert_array_n(void *array[], void *addr[], size_t n);
/*
	array'ın 0. indexinden itibaren  addr dizisinin n kadar elemanını yerletirir.
		Başarılı ise yerleştirdiği kadar doner
	hata durumları:
	1) array ==  NULL veya addr == NULL ise -1 doner
	2) array'nin yada addr'in son parametresi NULL değil ise ölümcül hata olur
	3) malloc hatasında -1 doner
*/

int		array_reverse_all(void *array[]);
/*
	array'ın tüm elemanlarını tersine sırlar Başarılı ise 0
	hata durumları:
	1) array == NULL ise -1 doner
	2) array_len == 0 ise 0 doner
*/

#endif