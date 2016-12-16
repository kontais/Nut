#ifndef _FS_H_
#define _FS_H_

#include <list.h>



#define FILE_TYPE_DIRCTORY		0x01
#define FILE_TYPE_BLOCK_DEVICE		0x02
#define FILE_TYPE_CHARACTER_DEVICE	0x04
#define FILE_TYPE_SOCKET		0x08
#define FILE_TYPE_MOUNT_POINT		0x10
#define FILE_TYPE_PLAIN_FILE		0x20



typedef struct file_dsc
{
	char *name;
	uint64_t inode;
	uint64_t type;
	uint64_t size;
	uint64_t refs;
	
	struct list_head *parent;
	struct list_head content;
	struct list_head list;
	
	file_hook hook;
}file_dsc;

typedef struct file_hook
{
	uint64_t (*open_hook)(void *file);
	uint64_t (*read_hook)(void *file, void *buf, uint64_t size);
	uint64_t (*write_hook)(void *file, void *buf, uint64_t size);
	uint64_t (*lseek_hook)(void *file, uint64_t off);
	uint64_t (*close_hook)(void *file, void);
}file_hook;

void fs_init(void);
void fs_mknode(const char *path, file_dsc *dsc);
void fs_rmnode(const char *path);
file_dsc *fs_getnode(const char *path);


#endif
