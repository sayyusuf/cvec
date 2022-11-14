#ifndef VECTOR_LIB_H
# define VECTOR_LIB_H
# include <stdlib.h>
# include <stddef.h>

size_t	find_max_bit(size_t num);
size_t	vector_len(void *vector[]);
int		vector_shift_right(void *vector[], size_t len, size_t n);
int		vector_shift_left(void *vector[], size_t len, size_t n);

int		vector_destroy(void *vector[], void (*del)(void *), size_t len);
int		vector_del_n(void *vector[], size_t len, void (*del)(void *), size_t n);

void	**vector_copy_addr_n(void *dest[], void *src[], size_t n);
void	**vector_deep_copy_n(void *dest[], void *src[], void *(*copy)(void *), size_t n);

void	**vector_expand(void *vector[], size_t expansion_len);
int		vector_insert(void *vector[], size_t len, void *addr);
int		vector_insert_vector_n(void *vector[], size_t len, void *addr[], size_t n);

int	vector_reverse_all(void *vector[], size_t len);

#endif