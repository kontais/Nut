#include <ktypes.h>
void *kmemcpy(void *dest, const void *src, size_t n)
{
	while (n-- > 0)
		*(dest++) = *(src++);
	return dest;
}
