#ifndef _E820_H_
#define _E820_H_

#include <types.h>

typedef struct mm_desc_t
{
	uint32_t base_addr_low;
	uint32_t base_addr_high;
	uint32_t length_low;
	uint32_t length_high;
	uint32_t type;
	uint32_t extended_attibutes;
}mm_desc_t;


#endif
