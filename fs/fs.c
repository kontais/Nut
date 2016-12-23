#include <klibc.h>
#include <fs.h>

file_node_t *root;
void *desc_table;

void fs_init(void)
{
	root = malloc(sizeof(file_node_t));
	root->name = malloc(2);
	strcpy(root->name,  "/");
	root->type = FILE_TYPE_ROOT;
	root->inode = NULL;
	
	list_init(&root->content);
	list_init(&root->list);
	root->parent = NULL;
	root->hook = NULL;
}
int fs_mknode(const char *path, file_node_t *dsc)
{
	
}
int fs_rmnode(const char *path)
{
	
}
file_node_t *fs_getnode(const char *path)
{
	
}
