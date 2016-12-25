#include<stdio.h>
#include<stdint.h>
struct memblk{
	struct memblk *mnext;
	uint64_t mlength;	
};
struct memblk *memlist;

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


void *malloc(size_t size)
{
	struct memblk *prev,*curr,*leftover;
//***if the request storage memory is 0
	if(size==0){	
		return  NULL;
	}
//use memblk multiples 
	size=(uint64_t)roundcmb(size);

//initialize memlist
	                              ////////.......
	prev=memlist;
	curr=prev->mnext;
	while(curr != NULL){
		curr->mlength=128;
		curr->mnext=curr+4;

//the block is just ok
		if(curr->mlength==size){
			prev->mnext=curr->mnext;

//memlist.mlength is used to store the whole free storage memory;
			memlist->mlength-=size;
//return request storage memory header address
			return curr+1;
		}

//the block is more than the request storage memory
//????what should we do if the left space less than the size of struct?????


		else if(curr->mlength>size){
			leftover=(struct memble*)((uint64_t)curr+size+1);   //get address of leftover
			prev->mnext=leftover;
//initialize leftover 
			leftover->mnext=curr->mnext;
			leftover->mlength=curr->mlength-size;
			memlist->mlength-=size;
			return curr+1;
			 
		}

//the block is less than the request storage memory
		else{
			prev=curr;
			curr=curr->mnext;
		}
	}
}



void free(void *ptr)
{
	uint64_t size,top;                           
	struct memblk *next,*pre,*block;


//????  the mlength of ptr and the *mnext of ptr
	block=(struct memblk *)ptr;
	block->mlength=32;
	block->mnext=block+4;
	size=block->mlength;
//make free space 8 multiples
	size=(uint64_t)roundcmb(size);

//initialize memlist
                           /////////.........
	pre=memlist;
	next=memlist->mnext;
//initialize   next
	next->mlength=128;
	next->mnext=next+4;

//query the free space before block 
	while((next!=NULL) && (next<block)){
		pre=next;
		next=next->mnext;
	}
//change whole variable
	//(uint64_t)next=(uint64_t)(block+32+block->mlength);


//if the space we should free is just memlist
//top is represent the (uint64_t)address before block 
	 if(pre == memlist)
		top=(uint64_t)NULL;
	else 
		top=(uint64_t)pre+pre->mlength+32;

	
	memlist->mlength+=size;
//if the free space can combine with after block
	if(top == (uint64_t)block){
		pre->mlength+=size;
		block=pre;
	}
//if neither before or after has no free space
	else{
		block->mnext=next;
		block->mlength=size;
		pre->mnext=block;
	}
//if the free space can combine with after block
	if((uint64_t)block+block->mlength == (uint64_t)next){
		block->mlength+=next->mlength;
		block->mnext=next->mnext;
}

}

int main()
{
	int i;
	char *buffer;
	char buf[4096];
	memlist=(struct memblk *)buf;
	memlist->mlength=2048;
	memlist->mnext=memlist+4;
	printf("please input chars\n");
	buffer=(char*)malloc(32);
	if(buffer==NULL) printf("false!");
	scanf("%s",buffer);
	printf("%s",buffer);
	memlist->mlength-=32;
	/*free(buffer);
	buffer=NULL;*/
	return 0;
}








/* #include <stdlib.h>
  *
  *      void *malloc(size_t size);
  *      void free(void *ptr);
  *      void *calloc(size_t nmemb, size_t size);
  *      void *realloc(void *ptr, size_t size);
*/

