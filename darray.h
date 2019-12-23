#ifndef DARRAY_H
#define DARRAY_H
#include<stdlib.h>

typedef struct
{
	size_t size;
	void* data;

	size_t elem_size;
	size_t reservation;
	
	void* (*copy_func)(void*,const void*,size_t);
	void (*delete_func)(void*);
} darray_t;

darray_t darray_create(size_t elem_size);
void darray_destroy(darray_t* o);
void darray_push_back(darray_t* o,const void* element);
void darray_extend_back(darray_t* o,const void* element,size_t count);
int darray_pop_back(darray_t* o);

#endif
