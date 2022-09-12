#ifndef ARGV_H
#define ARGV_H

//typedef struct argv_s argv_t;

typedef struct argv_s
{
	int	try_condition;
	size_t	len;
	size_t	capacity;
	void	**array;
	size_t	try_index;
} argv_t;

argv_t	*argv_new(void *array[], void *(*fptr)(void *));

int	argv_destroy(argv_t *argv, void (*dell)(void *));

int	argv_dell_one(argv_t *argv, size_t index, void (*dell)(void *));

int	argv_is_unique(argv_t *argv, void *addr);

int	argv_insert(argv_t *argv, size_t index, void *addr);

int	argv_push(argv_t *argv, void *address);

void	*argv_pull(argv_t *argv);

int	argv_try(argv_t *argv, void *addr, size_t index, int (*fptr)(void *, void *));

#endif
