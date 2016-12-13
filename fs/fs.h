#ifndef _FS_H_
#define _FS_H_

typedef struct file_dsc
{
	uint64_t inode;
	uint64_t type;
	uint64_t size;
	uint64_t refs;
	uint64_t time;
}file_dsc;

void fs_init(void);
void fs_mknode(const char path);
void fs_rmnode(const char path);
void fs_
#endif
