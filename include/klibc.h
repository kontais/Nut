#ifndef _KLIBC_H_
#define _KLIBC_H_
#include <SerialPortLib.h>
/**
 * This is the routine of standard C library for use in the kernel.
 */


//String
/**
 * Similar function as standard string functions.
 * @str the string to evaluate length of
 * @return the length of the string,
 */
static inline int kstrlen(char *str)
{
	int len = 0;
	while (*str++ != '\0')
		len ++;
	return len;
}
//Memory
/**
 * Use @ch to initialize @buf of size @count bytes.
 * @buf pointer to the buffer to be initialized
 * @ch content to be used to initialize
 * @count size of the buffer
 * @return pointer to the buffer
 */
static inline void *kmemset(void *dest, int ch, size_t n)
{
	char *dest_ptr = dest;
	while(n-- > 0)
		*(dest_ptr++) = ch;
	return dest;
}
/**
 * Copy @count bytes data from @src to @dest.
 * @dest pointer to destination buffer
 * @src pointer to souce buffer
 * @n size of data to be copied
 * @return pointer to dest
 */
static inline void *kmemcpy(void *dest, const void *src, size_t n)
{
	char *dest_ptr = dest;
	const char *src_ptr = src;
	while (n-- > 0)
		*(dest_ptr++) = *(src_ptr++);
	return dest;
}
/**
 * Allocate continuous @size bytes of a array.
 * @size number of bytes to be allocted
 * @return pointer to the allocated memory,NULL on error
 */
extern void *kmalloc(size_t size);
/**
 * Free memory allocated by kmalloc.
 * @ptr pointer to allocated memory
 */
extern void kfree(void *ptr);

//Input/Output
static inline void kprint(char *str)
{
	SerialPortWrite(str, kstrlen(str));
}
//Debug
/**
 * To help programmers find bugs.
 * If the exp is false,the kernel will panic.
 * TODO:Add the support to print line number and expression.
 * @exp expression to check
 */
#ifdef NDEBUG
#define assert(expr) (void)(0)
#elif

extern void __assert_fail (char *exp, char *file, char *name, char *func);

#define assert(expr)							\
	((expr)								\
	? (void)(0)							\
	: __assert_fail (#expr, __FILE__, __LINE__, __PRETTY_FUNCTION__))
#endif

#endif
