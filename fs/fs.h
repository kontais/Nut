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


typedef struct file_node
{
	char *name;
	uint64_t type;
	
	struct list_head list;
	struct list_head content;
	file_node *parent;
	
	struct file_hook_t *hook;
}file_node_t;

typedef struct file_hook
{
	int (*open)(file_node_t *node, void **context, int oflag);
	int (*close)(file_node_t *node, void **context);
	int (*read)(file_node_t *node, void **context, void *buf, uint64_t size);
	int (*write)(file_node_t *node, void **context, void *buf, uint64_t size);
	off_t (*lseek)(file_node_t *node, void **context, off_t offset, int whence);
	int (*ioctl)(file_node_t *node, void **context, int request, ...);
	int (*stat)(file_node_t *node, void **context, void *buf);
}file_hook_t;

typedef struct context
{
	file_node_t *node;
	void **context;
}context_t;

void fs_init(void);
int fs_mknode(const char *path, uint64_t type);
int fs_rmnode(const char *path);
file_node_t *fs_getnode(const char *path);

int fs_reghook_open(const char *path, int (*open)(file_node_t *node, void **context, int oflag));
int fs_reghook_close(const char *path,int (*close)(file_node_t *node, void **context));
int fs_reghook_read(const char *path, int (*read)(file_node_t *node, void **context, void *buf, uint64_t size));
int fs_reghook_write(const char *path, int (*write)(file_node_t *node, void **context, void *buf, uint64_t size));
int fs_reghook_lseek(const char *path, off_t (*lseek)(file_node_t *node, void **context, off_t offset, int whence));
int fs_reghook_ioctl(const char *path, int (*ioctl)(file_node_t *node, void **context, int request, ...));
int fs_reghook_stat(const char *path, int (*stat)(file_node_t *node, void **context, void *buf));

int fs_open(context_t **context, const char *path,, int oflag);
int fs_close(context_t **context);
int fs_read(context_t **context, void *buf, uint64_t size);
int fs_write(context_t **context, void *buf, uint64_t size);
int fs_lseek(context_t **context, off_t offset, int whence);
int fs_ioctl(context_t **context, int request, ...);
int fs_stat(context_t **context, void *buf);



#endif
