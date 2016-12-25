#include<stdio.h>
#include<stdint.h>

struct memblk{
	struct memblk *mnext;
	uint64_t mlength;	
};
struct memblk memlist;

//request storage memory become the beishu(size of memble) of 8
size_t roundcmb(size_t s)
{
	if(s&0x7==0)
		return s;
	else{
		s=(s>>3)+1;
		s=s<<3;
		return 0;
	}
}
void free(void *ptr)
{
	uint64_t size,top;                           
	struct memblk *next,*prev,*block;


//make free space 8 multiples

	size=(uint64_t)roundcmb(size);

	block=(struct memblk *)ptr;
	size=block->mlength;
	prev=&memlist;
	next=memlist.mnext;


//query the free space before block 
	while((next!=NULL) && (next<block)){
		prev=next;
		next=next->mnext;
	}


//if the space we should free is just memlist
//top is represent the (uint64_t)address before block 
	 if(prev==&memlist)
		top=(uint64_t)NULL;
	else 
		top=(uint64_t)prev+prev->mlength;

	
	memlist.mlength+=size;
//if the free space can combine with after block
	if(top==(uint64_t)block){
		prev->mlength+=size;
		block=prev;
	}
//if neither before or after has no free space
	else{
		block->mnext=next;
		block->mlength=size;
		prev->mnext=block;
	}
//if the free space can combine with after block
	if((uint64_t)block+block->mlength == (uint64_t)next){
		block->mlength+=next->mlength;
		block->mnext=next->mnext;
}

}
         

















