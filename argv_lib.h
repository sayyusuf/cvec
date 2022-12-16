#ifndef ARGV_LIB_H
# define ARGV_LIB_H

# include <vector_lib.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct argv_s
{
	int		try_condition;
	size_t	len;
	size_t	capacity;
	void	**vector;
	size_t	try_index;
}	argv_t;


int		argv_del_one(argv_t *argv, size_t index, void (*del)(void *));
int		argv_del_n(argv_t *argv, size_t index, void (*del)(void *), size_t n);
int		argv_del_all(argv_t *argv, void (*del)(void *));

int		argv_check_capacity(argv_t *argv, size_t len);
int		argv_is_unique(argv_t *argv, void *addr);
int		argv_reverse(argv_t	*argv);

int		argv_insert(argv_t *argv, size_t index, void *addr);
int		argv_insert_vector(argv_t *argv, size_t index, void *addr[]);
int		argv_insert_vector_n(argv_t *argv, size_t index, void *addr[], size_t n);
int		argv_push(argv_t *argv, void *address);
void	*argv_pull(argv_t *argv);

int		argv_try(argv_t *argv, void *addr, size_t index, int (*fptr)(void *, void *));
argv_t	*argv_cut(argv_t *argv, size_t index, size_t n);
argv_t	*argv_new(void *vector[], void *(*fptr)(void *));
int		argv_destroy(argv_t *argv, void (*del)(void *));

#endif
