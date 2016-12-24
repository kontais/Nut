#include <fs_special.h>

void *stdio_open(file_node_t *node, const char *path, int oflag)
{
	return NULL;
}
int stdio_close(file_node_t *node, void *context)
{
	return 0;
}
ssize_t stdio_read(file_node_t *node, void *context, void *buf, uint64_t size)
{
	return 0;
}
ssize_t stdio_write(file_node_t *node, void *context, const void *buf, uint64_t size)
{
	char *temp = malloc(size + 1);
	memcpy(temp, buf, size);
	*(temp + size) = '\0';
	__stdout(temp);
	free(temp);
	return size;
}
int stdio_mknode(const char *path)
{
	int ret;
	ret = fs_mknode(path, FILE_TYPE_SPECIAL);
	if (ret != 0)
	{
		printf("Create special file failed:stdio\n");
		return ret;
	}
	ret = fs_reghook(path, FILE_HOOK_INDEX_OPEN, &stdio_open);
	if (ret != 0)
	{
		printf("Register hook function failed:open\n");
		return ret;
	}
	ret = fs_reghook(path, FILE_HOOK_INDEX_CLOSE, &stdio_close);
	if (ret != 0)
	{
		printf("Register hook function failed:close\n");
		return ret;
	}
	ret = fs_reghook(path, FILE_HOOK_INDEX_READ, &stdio_read);
	if (ret != 0)
	{
		printf("Register hook function failed:read\n");
		return ret;
	}
	ret = fs_reghook(path, FILE_HOOK_INDEX_WRITE, &stdio_write);
	if (ret != 0)
	{
		printf("Register hook function failed:write\n");
		return ret;
	}
	return 0;
}
