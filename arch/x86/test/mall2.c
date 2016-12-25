#include<stdio.h>
#include<stdint.h>

//create struct
struct memblk{
	uint64_t mlength;
	struct memblk *mnext;
};
struct memblk *memlist;

//change the request space 16 multiples
size_t roundcmb(size_t size)
{
	if((size&0x15) != 0){
		size=(size>>4)+1;
		size=size<<4;
		return 0;
	}
	else 
		return size;
}


//function malloc
void *malloc(size_t size)
{
	struct memblk *prev,*curr,*leftover,*pte;

//if request space is zero
	if(size == 0)
		return NULL;

//the size of struct is 16,what we request is the space which not has struct
	size+=16;
	size=(uint64_t)roundcmb(size);

	prev=memlist;
	curr=prev->mnext;
	while(curr != NULL){

//initialize curr
		curr->mlength=128;
		curr->mnext=curr+10;
		
		if(curr->mlength==size){
			prev->mnext=curr->mnext;
			memlist->mlength-=size; 
			pte=curr+1;		    //size include the size of struct
			pte->mlength=size-16;
			return pte;             //curr itself has struct,the address of the 							  //space we request is start after curr's struct
		}
		else if(curr->mlength>size){
			if((curr->mlength-size)>=16){
				leftover=(struct memblk *)((uint64_t)curr+16+size);
				prev->mnext=leftover;
				leftover->mnext=curr->mnext;
				leftover->mlength=curr->mlength-size-16;
				memlist->mlength-=size;
			}
			else{
				prev->mnext=curr->mnext;
				memlist->mlength-=curr->mlength;
			}
			pte=curr+1;
			pte->mlength=size-16;
			return pte;
		}
		else{
			prev=curr;
			curr=curr->mnext;
		}
	}
}


//function free

void free(void *ptr)
{
	uint64_t top;
	struct memblk *next,*prev,*block;
//initialize block
	block=(struct memblk *)ptr;

	prev=memlist;
	next=prev->mnext;

//initialize next
	next->mlength=128;
	next->mnext=next+10;

	while(next!=NULL && next<block){
		prev=next;
		next=next->mnext;	
	}
	if(prev==memlist)
		top=(uint64_t)NULL;
	else
		top=(uint64_t)prev+prev->mlength+16;


//block can combine with before free space
	if(top==(uint64_t)block){
		block=prev;
		block->mlength=block->mlength+prev->mlength+16;
		memlist->mlength=memlist->mlength+block->mlength;
	}
		
//block can not combine with before free space
	if(top<(uint64_t)block){
		block->mnext=next;
		prev->mnext=block;
		block->mlength=block->mlength;
		memlist->mlength=memlist->mlength+block->mlength+16;
	}
//block can combine with after free space
	if(((uint64_t)block+block->mlength+16) == (uint64_t)next){
		block->mnext=next->mnext;
		block->mlength=block->mlength+next->mlength+16;
		memlist->mlength=memlist->mlength+block->mlength;
	}
}

int main()
{
	char buf[4096];
	char *buffer;
	memlist=(struct memblk *)buf;
	memlist->mlength=4096 - sizeof(struct memblk);
	memlist->mnext=NULL;
//	buffer=(char*)malloc(32);
//	if(buffer==NULL) printf("false!");
//	printf("please input a string:\n");
//	scanf("%s",buffer);
//	printf("%s",buffer);
//	free(buffer);
	void *ptr[128] = {0};
	for (int i = 0; i < 128; i ++)
		ptr[i] = malloc(4);
	for (int i = 0; i < 128; i ++)
		free(ptr[i]);
	return 0;
	
}



















