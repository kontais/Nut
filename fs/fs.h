#ifndef _FS_H_
#define _FS_H_

#include <list.h>
#include <klibc.h>

#define FILE_TYPE_ROOT			0x00
#define FILE_TYPE_DIRCTORY		0x01
#define FILE_TYPE_BLOCK_DEVICE		0x02
#define FILE_TYPE_CHARACTER_DEVICE	0x04
#define FILE_TYPE_SOCKET		0x08
#define FILE_TYPE_MOUNT_POINT		0x10
#define FILE_TYPE_PLAIN_FILE		0x20



typedef struct dir_fd
{
	uint64_t pos;
	
}dir_fd_t;
typedef struct file_fd
{
	uint64_t pos;
}file_fd_t;

typedef struct fd
{
	struct file_node_t *node;
	void *context;
}fd_t;

typedef struct inode
{
	
	
}inode_t;


typedef struct file_node
{
	char *name;
	uint64_t type;
	inode_t *inode;
	
	struct list_head list;
	struct list_head content;
	struct list_head *parent;
	
	struct file_hook_t *hook;
}file_node_t;

typedef struct file_hook
{
	int (*open)(file_node_t *node, void *fd);
	int (*close)(file_node_t *node, void *fd);
	int (*read)(file_node_t *node, void *fd, void *buf, uint64_t size);
	int (*write)(file_node_t *node, void *fd, void *buf, uint64_t size);
	int (*ioctl)(file_node_t *node, void *fd, int request, ...);
	
}file_hook_t;


void fs_init(void);
void fs_mknode(const char *path, file_node_t *dsc);
void fs_rmnode(const char *path);
file_node_t *fs_getnode(const char *path);

#endif
