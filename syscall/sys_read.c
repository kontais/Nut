#include <syscall.h>

ssize_t sys_read(int fd, void *buf, uint64_t count)
{
	fs_context_t *fs_context = get_fd_ptr(fd);
	if (fs_context == NULL)
		return -1;
// 	ssize_t ret = fs_read(fs_context, buf, count);
// 	printf("RET:%d\n", ret);
// 	return ret;
	return fs_read(fs_context, buf, count);
}
