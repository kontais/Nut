#ifndef _KLIBC_H_
#define _KLIBC_H_

/**
 * This is the routine of standard C library for use in the kernel.
 */

//Input/Output

//String

//Memory
/**
 * Use @ch to initialize @buf of size @count bytes.
 * @buf pointer to the buffer to be initialized
 * @ch content to be used to initialize
 * @count size of the buffer
 * @return pointer to the buffer
 */
void *kmemset(char *buf, char ch, size_t count);
/**
 * Copy @count bytes data from @src to @dest.
 * @dest pointer to destination buffer
 * @src pointer to souce buffer
 * @n size of data to be copied
 * @return pointer to dest
 */
int kmemcpy(char *dest, const char *src, size_t n);
/**
 * Allocate continuous @size bytes of a array.
 * @size number of bytes to be allocted
 * @return pointer to the allocated memory,NULL on error
 */
void *kmalloc(size_t size);
/**
 * Free memory allocated by kmalloc.
 * @ptr pointer to allocated memory
 */
void kfree(void *ptr);

#endif
