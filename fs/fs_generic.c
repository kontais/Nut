#include <fs_generic.h>

void *fat_open(file_node_t *node, const char *path, int oflag)
{
	fat_context_t *context = malloc(sizeof(fat_context_t));
	context->fs = malloc(sizeof(FATFS_Type));
	fatfs_init(context->fs);
	context->oflag = oflag;
	
	char *path_buf = malloc(strlen(path) + 1);
	char *real_path = malloc(strlen(path) + 1);
	char *aim_path = NULL;
	strcpy(path_buf,path);
	char *node_name = strtok_r(path_buf, "/", &aim_path);
	while(node_name != NULL)
	{
		if(strcmp(node_name, node->name) != 0 )
			break;
		node_name = strtok_r(NULL, "/", &aim_path);
	}
	strcpy(real_path,"/");
	strcat(real_path, aim_path);
	
	context->file = malloc(sizeof(FATFile_Type));
	if (fatfs_searchfile(context->fs, context->file, real_path) != 0)
	{
		bug("Search file faild %s by %s", real_path, path);
		fatfs_destroy(context->fs);
		free(context->fs);
		free(context);
		free(path_buf);
		free(real_path);
		free(context->file);
		return NULL;
	}
	
	context->offset = 0;
	uint32_t bufsize = computer_needed_buf_size(context->fs, context->file);
	context->buf = malloc(bufsize);
	uint32_t ret =  fatfs_readfile(context->fs, context->file, context->buf, bufsize);
	if (ret != bufsize)
	{
		bug("Read file faild");
		fatfs_destroy(context->fs);
		free(context->fs);
		free(context);
		free(path_buf);
		free(real_path);
		free(context->file);
		return NULL;
	}
	free(path_buf);
	free(real_path);
	return context;
}
int fat_close(file_node_t *node, fat_context_t *context)
{
	fatfs_destroy(context->fs);
	free(context->file);
	free(context->fs);
	context->oflag = 0;
	free(context);
	return 0;
}
ssize_t fat_read(file_node_t *node, fat_context_t *context, void *buf, uint64_t size)
{
	if (context->offset + size > context->file->FileSize)
		return 0;
	memcpy(buf, context->buf, size);
	context->offset += size;
	return size;
}
off_t lseek(file_node_t *node, fat_context_t *context, off_t offset, int whence)
{
	switch(whence)
	{
		case FILE_LSEEK_WHENCE_SEEK_SET:
			context->offset = offset;
			break;
		case FILE_LSEEK_WHENCE_SEEK_CUR:
			context->offset += offset;
			break;
		case FILE_LSEEK_WHENCE_SEEK_END:
			context->offset = context->file->FileSize + offset;
			break;
		default:
			return -1;
			break;			
	}
	return context->offset;
}
