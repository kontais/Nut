#include <ktypes.h>
void *kmemset(void *dest, int ch, size_t n)
{
	while(n-- > 0)
		*(dest++) = ch;
	return dest;
}
