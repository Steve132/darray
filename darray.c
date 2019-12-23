#include<stdlib.h>
#include<string.h>
#include "darray.h"

static void nop(void* v)
{};
darray_t darray_create(size_t elem_size)
{
	darray_t o;
	o.elem_size=elem_size;
	o.reservation=16;
	o.data=malloc(elem_size*o.reservation);
	o.copy_func=memcpy;
	o.delete_func=nop;
	o.size=0;
	return o;
}

static size_t nextpoweroftwo(size_t v)
{
	//https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v |= v >> 32;
	v++;
	return v;
}

void darray_destroy(darray_t* o)
{
	for(size_t i=0;i<o->size;i++)
	{
		o->delete_func(o->data+i*o->elem_size);
	}
	free(o->data);
}

void darray_push_back(darray_t* o,const void* element)
{
	darray_extend_back(o,element,1);
}

void darray_extend_back(darray_t* o,const void* element,size_t count)
{
	size_t newsize=o->size+count;
	if(newsize > o->reservation)
	{
		size_t newres=nextpoweroftwo(newsize);
		void* data=malloc(o->elem_size*newres);
		o->copy_func(data,o->data,o->elem_size*o->size);
		o->reservation=newres;
	}
	o->copy_func(o->data+o->size*o->elem_size,element,o->elem_size*count);
	o->size=newsize;
}
int darray_pop_back(darray_t* o)
{
	if(o->size)
	{
		o->delete_func(o->data+(o->size-1)*o->elem_size);
		o->size--;
		return 1;
	}
	return 0;
}
