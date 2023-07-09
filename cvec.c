#include "cvec.h"
#include <string.h>

int	cvec_resize(cvec_t *vec, size_t capacity)
{
	void	*tmp;
	void	*vtmp;

	if (!vec || !capacity)
		return (-1);
	capacity &= ~(1);
	tmp = malloc(capacity * vec->tsz);
	if (!tmp)
		return (-1);
	vtmp = tmp + (capacity / 2 * vec->tsz);
	memcpy(vtmp, vec->vaddr, vec->size * vec->tsz);
	free(vec->aaddr);
	*vec = (cvec_t){.aaddr = tmp, .tsz = vec->tsz, .ncap = capacity >> 1, .pcap = capacity >> 1, .size = vec->size, .tcap = capacity, .vaddr = vtmp};
	return (0);
}

int cvec_init(cvec_t *vec,size_t type_size, size_t capacity)
{
	if (!vec)
		return (-1);
	*vec = (cvec_t){.tsz = type_size, .tcap = capacity & ~(1), .pcap = capacity >> 1, .ncap = capacity >> 1};
	vec->aaddr = malloc(vec->tsz * vec->tcap);
	if (!vec->aaddr)
		return (-1);
	vec->vaddr = vec->aaddr + (vec->ncap * vec->tsz);
	return (0);
}

void	cvec_destroy(cvec_t *vec, void (*iter)(void *))
{
	size_t	i;

	if (!vec)
		return ;
	i = 0;
	if (iter)
		while (i < vec->size)
			iter(vec->vaddr + (i++ * vec->tsz));
	free(vec->aaddr);
}



int cvec_push(cvec_t *vec, void *addr)
{
	if (!vec || !addr)
		return (-1);
	if (vec->size >= vec->pcap)
		if (cvec_resize(vec, vec->tcap * 2) < 0)
			return (-1);
	memcpy(vec->vaddr + (vec->tsz * vec->size++), addr, vec->tsz);
	return (0);
}

int	cvec_pop(cvec_t *vec, void *addr)
{
	if (!vec || !addr || !vec->size)
		return (-1);
	memcpy(addr, vec->vaddr + (vec->tsz * --vec->size), vec->tsz);
	return 0;
}

int	cvec_get(cvec_t *vec, void *addr, size_t index)
{
	if (!vec || !addr || !vec->size || index > vec->size - 1)
		return (-1);
	memcpy(addr, vec->vaddr + (vec->tsz * index), vec->tsz);
	return 0;
}



int	cvec_insert(cvec_t *vec, void *addr, size_t index)
{
	if (!vec || !addr || index > vec->size)
		return (-1);
	if (index > vec->pcap >> 1)
	{
		if (vec->size >= vec->pcap)
			if (cvec_resize(vec, vec->tcap * 2) < 0)
				return (-1);
		memmove(vec->vaddr + (vec->tsz * (index + 1)), vec->vaddr + (vec->tsz * index), (vec->size++ - index) * vec->tsz);
		memcpy(vec->vaddr + (vec->tsz * index), addr, vec->tsz);
	}
	else
	{
		if (vec->ncap == 0)
			if (cvec_resize(vec, vec->tcap * 2) < 0)
				return (-1);
		memmove(vec->vaddr - vec->tsz, vec->vaddr, vec->tsz * (index + 1));
		vec->vaddr -= vec->tsz;
		memcpy(vec->vaddr + (vec->tsz * index ), addr, vec->tsz);
		++vec->size;
		++vec->pcap;
		--vec->ncap;
	}
	return (0);
}

int	cvec_erase(cvec_t *vec, size_t index, void (*destroy)(void*))
{

	if (!vec || index >= vec->size)
		return (-1);
	if (destroy)
		destroy(vec->vaddr + (vec->tsz * index));
	if (index > vec->pcap >> 1)
	{
		memmove(vec->vaddr + (vec->tsz * index), vec->vaddr + (vec->tsz * (index + 1)), (vec->size-- - index - 1) * vec->tsz);
	}
	else
	{
		memmove(vec->vaddr + vec->tsz, vec->vaddr, vec->tsz * index);
		vec->vaddr += vec->tsz;
		--vec->size;
		--vec->pcap;
		++vec->ncap;
	}
	return (0);
}

int cvec_iter(cvec_t *vec, void *any,  void (*f)(void *elemnet_addr, void *any))
{
	size_t i;

	if (!vec || !f)
		return (-1);
	i = 0;
	while (i < vec->size)
		f(vec->vaddr + (vec->tsz * i++), any);
	return (0);
}