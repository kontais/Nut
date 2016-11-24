#ifndef _KLIBC_H_
#define _KLIBC_H_

#include<types.h>
/**
 * This is the routine of standard C library for use in the kernel.
 */

//String
/**
 * 
 * 
 * 
 */

/**
 * Similar function as standard string functions.
 * @str the string to evaluate length of
 * @return the length of the string,
 */
static inline int strlen(char *str)
{
	int len = 0;
	while (*str++ != '\0')
		len ++;
	return len;
}
/**
 * String copy function,with a limit of the nubmer of characters.
 * @dst destination buffer
 * @src source string
 * @retval dst destination buffer
 * 
 */
static inline char *strcat(char *dst, const char *src)
{
	while(*dst != '\0')
		dst++;
	while((*dst++ = *src++)!= '\0');
	*dst = '\0';
	return dst;
}
/**
 * String copy function,with a limit of the nubmer of characters.
 * @dst destination buffer
 * @src source string
 * @retval dst destination buffer
 * 
 */
static inline char *strcpy(char *dst, const char *src)
{
	while((*dst++ = *src++) != '\0');
	*dst = '\0';
	return dst;
}
/**
 * String copy function,with a limit of the nubmer of characters.
 * @dst destination buffer
 * @src source string
 * @n   maximum number of characters in total
 * @retval pointer to dst destination buffer
 * 
 */
static inline char *strncpy(char *dst, const char *src, uint64_t n)
{
	while(n-- > 0 && (*dst++ = *src++) != '\0');
	return dst;
}
//Memory
/**
 * Use @ch to initialize @buf of size @count bytes.
 * @buf pointer to the buffer to be initialized
 * @ch content to be used to initialize
 * @count size of the buffer
 * @retval pointer to the buffer
 */
static inline void *memset(void *dest, char ch, uint64_t n)
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
 * @retval pointer to dest
 */
static inline void *memcpy(void *dest, const void *src, uint64_t n)
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
 * @retval pointer to the allocated memory,NULL on error
 */
extern void *kmalloc(uint64_t size);
/**
 * Free memory allocated by kmalloc.
 * @ptr pointer to allocated memory
 */
extern void kfree(void *ptr);

//Input/Output
extern void (*__stdout)(char *str);
/**
 * Formatted output fuction
 * @fmt format string
 * @buf buffer to hold string
 * @... (optional)multiple variable to output
 * @retval number of characters outputted
 * Note:
 * 	Current implementation of printf only support a subset
 * of format conversion specifiers including:%d, %s, %c, %x
 * TODO:
 * 	Add support for more functions.
 */
extern int printf(char *fmt, ...);
extern int sprintf(char *buf, char *fmt, ...);
//Debug
/**
 * To help programmers find bugs.
 * If the exp is false,the kernel will panic.
 * TODO:Add the support to print line number and expression.
 * @exp expression to check
 */
#ifdef NDEBUG
#define assert(expr) (void)(0)
#else
#define assert(expr)							\
	((expr)								\
	? (void)(0)							\
	: __assert_fail (#expr, __FILE__, __LINE__, __PRETTY_FUNCTION__))
extern void __assert_fail(const char *__assertion, const char *__file, unsigned int __line, const char *__function);
#endif

#endif
