#include <syscall.h>

ssize_t sys_write(int fd, const void *buf, size_t count)
{
	fs_context_t *fs_context = get_fd_ptr(fd);
	if (fs_context == NULL)
		return -1;
	printf("syscall write size is:%d\n",count);
	return fs_write(fs_context, buf, count);
}
