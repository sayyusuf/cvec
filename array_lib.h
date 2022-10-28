#ifndef ARRAY_LIB_H
# define ARRAY_LIB_H
# include <stdlib.h>
# include <stddef.h>

size_t	find_max_bit(size_t num);
size_t	array_len(void *array[]);
int		array_shift_right(void *array[], size_t len, size_t n);
int		array_shift_left(void *array[], size_t len, size_t n);

int		array_destroy(void *array[], void (*del)(void *));
int		array_del_all(void *array[], size_t len, void (*del)(void *));
int		array_del_n(void *array[], size_t len, void (*del)(void *), size_t n);
int		array_del_one(void *array[],size_t len, void (*del)(void *));

void	**array_copy_addr(void *dest[], void *src[]);
void	**array_copy_addr_n(void *dest[], void *src[], size_t n);
void	**array_deep_copy(void *dest[], void *src[], void *(*copy)(void *));
void	**array_deep_copy_n(void *dest[], void *src[], void *(*copy)(void *), size_t n);

void	**array_expand(void *array[], size_t expansion_len);
int		array_insert(void *array[], size_t len, void *addr);
int		array_insert_array(void *array[], size_t len, void *addr[]);

int		array_insert_array_n(void *array[], size_t len, void *addr[], size_t n);

int	array_reverse_all(void *array[], size_t len);

#endif