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

fs_context_t *fs_open(const char *path,int oflag)
{
	fs_context_t *fs_cont = malloc(sizeof(fs_context_t));
	file_node_t *node = fs_getnode(path);
	fs_cont->context = node->hook->open(node,path,oflag);
	if(fs_cont->context == NULL)
		return -1;
	fs_cont->node = node;
	return fs_cont;
}
int fs_close(fs_context_t *context);
{
	free(context);
	return 0;
	
}
int fs_read(fs_context_t *context, void *buf, uint64_t size)
{
	read(context->node,context,buf,size);
	return 0;
}
