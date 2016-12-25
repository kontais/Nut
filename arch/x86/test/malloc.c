#include<stdio.h>
#include<stdint.h>

//create struct
struct memblk{
	int	muse;
	int  	mlength;
	struct 	memblk *mnext;
};
struct memblk *memlist;

//change the request space 16 multiples

uint64_t roundcmb(uint64_t size)
{
	if((size&0x15) != 0){
		size=(size>>4)+1;
		size=size<<4;
		return 0;
	}
	else 
		return size;
}

void *malloc(uint64_t size)
{
	struct memblk *prev,*curr,*leftover;

//initialize memlist
	memlist->mlength=4080;
	memlist->muse=0;
	prev=memlist;
	memlist->mnext=NULL;
	curr=prev->mnext;

	if(size == 0)
		return NULL;

	size=roundcmb(size+16);
//traverse list
	while(prev->muse==1 || prev->mlength<(size-16)){
		prev=curr;
		curr=curr->mnext;
	}
	if(prev->mnext == NULL){
//the free space is not enough
		if(prev->mlength < (size-16))
			return 0;
		else if(prev->mlength < size){
				prev->muse=1;
				return prev;
			}
			else{
				leftover=(struct memblk *)((uint64_t)prev+size);
				leftover->mnext=curr;
				prev->mnext=leftover;
				curr=leftover;

//initialize curr which is new free space
				curr->muse=0;
				curr->mlength=prev->mlength-size;


//change the value of prev 
				prev->muse=1;
				prev->mlength=size-16;
				return prev;
			
			}
	}
	if(prev->mnext != NULL){
		if(prev->mlength < size){
			prev->muse=1;
			return prev;
		}
		else{
			leftover=(struct memblk *)((uint64_t)prev+size);
			leftover->mnext=curr;
			prev->mnext=leftover;
			curr=leftover;

			curr->muse=0;
			curr->mlength=prev->mlength-size;

			prev->muse=1;
			prev->mlength=size-16;
			return prev;
		}
	}
}




void free(void * ptr)
{
	
}


int main()
{
	char buf[4096];
	char *buffer;
	memlist=(struct memblk *)buf;
	buffer=(char*)malloc(32);
	if(buffer==NULL) printf("false!");
	printf("please input a string\n");
	scanf("%s",buffer);
	printf("%s",buffer);
	return 0;
}
















