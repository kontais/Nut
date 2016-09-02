#ifndef _LIST_H_
#define _LIST_H_

//Use this macro in a struct to define a link list
#define list_head(name, type)			\
	struct name{				\
		struct type *next;		\
		struct type *prev;		\
	}
//Retain the MEMBER in the object of the TYPE type pointed by PTR
#define list_head(ptr, type, MEMBER)		\
	(type *)((char *)ptr - ((size_t)&((type *)0->MEMBER)))
//Used to init struct LIST_HEAD
static LIST_HEAD_INIT(x)	\
	{ x.next = &x; x.prev = &x; }\
#define LIST_ADD
#endif
