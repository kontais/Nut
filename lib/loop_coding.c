#include<stdio.h>


int loop_unicode_into_utf8(int *unicode, char *utf8)
{
	int size;
	int sum_size=0;
	for(; *unicode!= 0x0000; unicode++)
	{
		unicode_into_utf8(*unicode,utf8);
		size=unicode_into_utf8(*unicode,utf8+sum_size);
		sum_size+=size;
	}
	return sum_size;
}
