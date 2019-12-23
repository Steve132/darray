#include "darray.h"
#include <stdio.h>

//custom copier/deleter for non-POD elements in array;
static void* copy_darray_int(void* dst,const void* src,size_t bytes);
static void delete_darray_int(void* o);

int main(int argc,char** argv)
{
	darray_t intarray=darray_create(sizeof(int));
	
	int tmp;

	tmp=1;
	darray_push_back(&intarray,&tmp);
	tmp=2;
	darray_push_back(&intarray,&tmp);
	tmp=10;
	darray_push_back(&intarray,&tmp);
	
	for(size_t i=0;i<intarray.size;i++)
	{
		int* dloc=intarray.data;
		printf("%d\n",dloc[i]);
	}
	darray_destroy(&intarray);


	//or do more complex allocations.  Use the advanced creation system to set custom functions for how to handle deletion and copying for more complex elements that need 
	darray_t doublearray=darray_create(sizeof(darray_t));
	doublearray.copy_func=copy_darray_int;
	doublearray.delete_func=delete_darray_int;

	darray_t tmp=darray_create(sizeof(int));
	int ti=1;
	darray_push_back(&tmp,&ti);
	darray_push_back(&tmp,&ti);
	
	darray_push_back(&doublearray,&tmp);
	darray_push_back(&doublearray,&tmp);
	
	return 0;
}

static void* copy_darray_int(void* dst,const void* src,size_t bytes)
{
	size_t num=bytes/sizeof(darray_t);
	const darray_t* srcelems=src;
	darray_t* dstelems=dst;
	for(size_t i=0;i<num;i++)
	{
		darray_t newintarray=darray_create(sizeof(int));
		darray_t srcintarray=srcelems[i];
		darray_extend_back(&newintarray,srcintarray.data,srcintarray.size);
		dstelems[i]=newintarray;
	}
}
static void delete_darray_int(void* o)
{
	darray_destroy(o);
}
