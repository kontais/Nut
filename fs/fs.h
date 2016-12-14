#ifndef _FS_H_
#define _FS_H_

#include <list.h>

typedef struct file_dsc
{
	uint64_t inode;
	uint64_t type;
	uint64_t size;
	uint64_t refs;
	uint64_t time;
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
void fs_mknode(const char path);
void fs_rmnode(const char path);
void fs_reghook(const char path, void *callback);
void 
#endif
