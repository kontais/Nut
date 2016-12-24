#ifndef _FS_SPECIAL_H_
#define _FS_SPECIAL_H_
#include <klibc.h>
#include <fs.h>

void *stdio_open(file_node_t *node, const char *path, int oflag);
int stdio_close(file_node_t *node, void *context);
ssize_t stdio_read(file_node_t *node, void *context, void *buf, uint64_t size);
ssize_t stdio_write(file_node_t *node, void *context, const void *buf, uint64_t size);


#endif
