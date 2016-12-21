#include <klibc.h>
int atoi(const char *str)
{
	int num=0;
	int sign=0;
	if(str!=NULL){
//step the space
		for(;*str==' '||*str=='\t';str++);
//judge the first num is 1 or -1
		if(*str=='-'){
			sign=1;
			str++;
		}
		if(*str=='+'){
			str++;
		}
//change
		while(*str!='\0'){
			if(*str>='0'&&*str<='9'){
				num=num*10+(*str-'0');
				str++;
			}
			else{
				num=num+0;
				break;
			}	
		}			
	}
	if(sign)
		num=0-num;
	return 0;
}

/* Parse S into tokens separated by characters in DELIM. 
   If S is NULL, the saved pointer in SAVE_PTR is used as 
   the next starting point.  For example: 
        char s[] = "-abc-=-def"; 
        char *sp; 
        x = strtok_r(s, "-", &sp);      // x = "abc", sp = "=-def" 
        x = strtok_r(NULL, "-=", &sp);  // x = "def", sp = NULL 
        x = strtok_r(NULL, "=", &sp);   // x = NULL 
                // s = "abc\0-def\0" 
*/  
char *strtok_r(char *s, const char *delim, char **save_ptr)
{
	char *token;  
  
	if (s == NULL) s = *save_ptr;  
  
	/* Scan leading delimiters.  */  
	s += strspn(s, delim);  
	if (*s == '\0')   
		return NULL;  
  
	/* Find the end of the token.  */  
	token = s;  
	s = strpbrk(token, delim);  
	if (s == NULL)  
		/* This token finishes the string.  */  
		*save_ptr = strchr(token, '\0');  
	else {  
		/* Terminate the token and make *SAVE_PTR point past it.  */  
		*s = '\0';  
		*save_ptr = s + 1;  
	}  
	return token;  
} 
/**
 * strspn, strcspn
 * get length of a prefix substring
 * @s string
 * @accept char set to accept
 * @reject char set to reject
 */
size_t strspn(const char *s, const char *accept)
{
	size_t size = 0;
	const char *ptr;
	for(; *s != NULL; s ++, size ++)
	{
		for(ptr = accept; *s != *ptr && *ptr != NULL; ptr ++);
		if (*ptr == NULL)
			return size;
	}
	return size;
}

size_t strcspn(const char *s, const char *reject)
{
	size_t size = 0;
	for(; *s != NULL; s ++, size ++)
		for(const char *ptr = reject; *ptr != NULL; ptr ++)
			if (*s == *ptr)
				return size;
	return size;
}

/**
 * strchr, strrchr
 * locate the first (last) occurrence of character c in the string s
 * @s string
 * @c character(one byte)
 * @retval pointer to the character in the string.
 */
char *strchr(const char *s, int c)
{
	for(; *s != c && *s != NULL; s ++);
	return (char *)s;
}
char *strrchr(const char *s, int c)
{
	const char *rs = strlen(s) + s - 1;
	for(; rs != s - 1; rs --)
		if (*rs == c)
			return (char *)rs;
	return NULL;
}
/**
 * strpbrk
 * search a string for any of a set of bytes
 * @s string
 * @accept set of bytes to locate
 * @retval pointer to the byte in @s that matches
 */
char *strpbrk(const char *s, const char *accept)
{
	for (; *s != NULL; s++)
		for (const char *p = accept; *p != NULL; p ++)
			if (*s == *p)
				return (char *)s;
	return NULL;
}
