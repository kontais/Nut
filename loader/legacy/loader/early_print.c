#include <BIOS_interrupt.h>
#include <klibc.h>
#include <cpu_reg.h>
#include <stdarg.h>
#include <types.h>
static const char hex_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void (*__stdout)(char *str);

void print_init(void)
{
	__stdout = &print_str16;
}
void print_str16(char *str)
{
	reg16 reg;
	reg.ax = 0x1301;
	reg.bx = 0X000C;
	reg.cx = kstrlen(str);
	asm 
	(
		"mov	%%ds, %0"
		: "=m" (reg.es)
		:
	);
// 	reg.es = 
 	reg.bp = (uint16_t)str;
	bios_int16(&reg, 0x10);
}
static inline char *__print_hex(char *buf, uint64_t hex, int num)
{
	while(num --> 0)
	{
		*(buf ++) = hex_table[hex >> (num * 4) & 0x0f];
	}
	return buf;
}
static inline char *__print_deci(char *buf, int64_t deci)
{
	char temp_buf[21];
	int i = 0;
	int sign = 0;
	if (deci < 0)
	{
		sign = 1;
		deci = -deci;
	}
	while((temp_buf[i ++] = deci % 10) != 0)
		deci /= 10;
	if (sign == 1)
		temp_buf[i ++] = '-';
	while(i > 0)
		*buf ++ = temp_buf[-- i];
	return buf;
}
static inline char *__print_str(char *buf, char *str)
{
	int len = strlen(str);
	assert(len <= 128);
	kstrcpy(buf, str, 128);
	return buf + len;
}
static inline char *__print_ch(char *buf, char ch)
{
	*buf = ch;
	return buf + 1;
}

void printf(char *fmt, ...)
{
	char buf[128];
	char *ptr = buf;
	
	va_list ap;
// 	long long ll;
// 	long l;
	unsigned int ud;
	int d;
	char c;
	char *s;
	
	va_start(ap, fmt);
	while(*fmt)
		switch (*fmt ++) {
			case 's':
				s = va_arg(ap, char *);
				ptr = __print_str(ptr, s);
				break;
			case 'c':
				c = va_arg(ap, char);
				ptr = __print_ch(ptr, c);
				break;
			case 'd':
				d = va_arg(ap, int);
				ptr = __print_deci(ptr, d);
				break;
			case 'x':
				ud = va_arg(ap, unsigned int);
				ptr = __print_hex(ptr, ud);
				break;
			default:
				if (*fmt == '%')
					break;
				else 
					*ptr ++ = *fmt ++;
		};
	va_end(ap);
	(*__stdout)(buf);
}
