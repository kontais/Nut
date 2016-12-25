#include<stdio.h>
#include<stdint.h>

//create struct
struct memblk{
	uint64_t used;
	uint64_t length;
	struct memblk *next;
};
struct memblk *memlist;

//change the request space 16 multiples

static inline uint64_t roundcmb(uint64_t size)
{
// 	if((size&0x15) != 0){
// 		size=(size>>4)+1;
// 		size=size<<4;
// 		return 0;
// 	}
// 	else 
// 		return size;
    return (size & 0xf) ? (size & 0xfffffffffffffff0) + 0x10 : size;
}
void malloc_init(void *buf, uint64_t size)
{
	memlist = buf;
	memlist->used = 0;
	memlist->length = size - sizeof(struct memblk);
	memlist->next = NULL;
}
void *_malloc(uint64_t size)
{
    uint64_t alloc_size = roundcmb(size);
	printf("%ld\n", alloc_size);
	for (struct memblk *it = memlist; it != NULL; it = it->next)
    {
		if (it->used && it->length < alloc_size)
			continue;
		if (it->length < alloc_size + sizeof(struct memblk) + 16)
		{
			it->used = 1;
			return (void *)it + sizeof(struct memblk);
		}
		else
		{
			it->length -= alloc_size + sizeof(struct memblk);
			struct memblk *new_block = (void *)it + it->length + sizeof(struct memblk);
			new_block->length = alloc_size;
			new_block->used = 1;
			new_block->next = it->next;
			it->next = new_block;
			return (void *)new_block + sizeof(struct memblk);
		}
    }
    return NULL;
}
void _free(void *buf)
{
	struct memblk *it = memlist;
	while(it->next != NULL && it->next < (void *)buf - sizeof(struct memblk))
	{
		it = it->next;
		it->next = it->next->next;
	}
	(struct memblk *)buf = it->next;
	buf->next = it->next->next;
	buf->used = 0;
	if(it->used == 0)
	{
		buf->length = buf->length + it->length + sizeof(struct memblk);
		it->next = buf->next;
		buf = it;
	}
	if(buf->next->used == 0)
	{
		buf->length = buf->length + buf->next->length +sizeof(struct memblk);
		buf->next = buf->next->next;
		
	}

}
int main(void)
{
	char buf[4096];
	malloc_init(buf, 4096);
	void *buf2[16] = {0};
	for (int i = 0; i < 16; i ++)
		buf2[i] = _malloc(i * 9);
	for (struct memblk *it = memlist; it != NULL; it = it->next)
    {
		printf("%d\t%lx\t%d\n",it->length, it->next, it->used);
    }
	return 0;
}



