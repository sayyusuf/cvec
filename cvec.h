#ifndef CVEC_H
# define CVEC_H

# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>

typedef struct cvec_s
{
	size_t		size;		// number of elements
	size_t		pcap;		// + capacity	
	size_t		ncap;		// - capacity
	size_t		tcap;		// total capacity
	size_t		tsz;		// type size
	void		*aaddr;	// alloced address
	void		*vaddr;	// vector address
} cvec_t;


#define CVEC_NEW(vec, type, capacity) cvec_init(&vec, sizeof(type), capacity)

int		cvec_init(cvec_t *vec ,size_t type_size, size_t capacity);
void	cvec_destroy(cvec_t *vec , void (*iter)(void *));


int 	cvec_push(cvec_t *vec, void *addr);
int 	cvec_pop(cvec_t *vec, void *addr);
int		cvec_get(cvec_t *vec, void *addr, size_t index);

int		cvec_insert(cvec_t *vec, void *addr, size_t index);
int		cvec_erase(cvec_t *vec, size_t index, void (*destroy)(void*));

int 	cvec_iter(cvec_t *vec, void *any, void (*f)(void *elemnet_addr, void *any));


#endif