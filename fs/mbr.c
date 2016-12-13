#include <mbr.h>

void MBR_Init(MBR_Record *record, const char *disk)
{
	int fd = open("/dev/sda", "r");
	read(fd, record, 512);
}
