#include <klibc.h>
#include <fs.h>

file_node_t *root;
void *desc_table;

int dir_open(file_node_t *file)
{
	
	return 0;
}
int dir_close(file_node_t *file)
{
	return 0;
}
int dir_read(file_node_t *file, void *buf, uint64_t size)
{
	
}
int dir_write(file_node_t *file, void *buf, uint64_t size)
{
	
}
int dir_ioctl(file_node_t *file, int request, ...)
{
	
}

int file_open(file_node_t *file)
{
	
	return 0;
}
int file_close(file_node_t *file)
{
	return 0;
}

int file_read(file_node_t *file, void *buf, uint64_t size)
{
	
}
int file_write(file_node_t *file, void *buf, uint64_t size)
{
	
}
int file_ioctl(file_node_t *file, int request, ...)
{
	
}
void fs_init(void)
{
	root = malloc(sizeof(file_node_t));
	root->name = malloc(sizeof("/"));
	strcpy(root->name,  "/");
	root->type = FILE_TYPE_ROOT;
	root->inode = NULL;
	
	list_init(&root->content);
	list_init(&root->list);
	root->parent = NULL;
}
void fs_mknode(const char *path, file_node_t *dsc)
{
	
}
void fs_rmnode(const char *path)
{
	
}
file_node_t *fs_getnode(const char *path)
{
	
}
