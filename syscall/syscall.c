#include <syscall.h>
#include <klibc.h>
#include <mm.h>
#include <paging.h>
uint64_t *syscall_table = (uint64_t *)SYSCALL_BASE;

void syscall_init(void)
{
	uint64_t temp = page_alloc(SYS_CALL_TABLE_SIZE);
	assert(temp != INVALID_ADDR);
	modify_chunk_mapping(get_current_plm4e(), SYSCALL_BASE, (uint64_t)temp, SYS_CALL_TABLE_SIZE, DEFAULT_PTE_FLAG);
	memset(syscall_table, 0, SYS_CALL_TABLE_SIZE << 12);
	
	*(syscall_table + SYS_syscall) = (uint64_t)&sys_syscall;
	*(syscall_table + SYS_write) = (uint64_t)&sys_write;
	*(syscall_table + SYS_open) = (uint64_t)&sys_open;

// 	*syscall_table++ = &sys_exit;
// 	*syscall_table++ = &sys_fork;
// 	*syscall_table++ = &sys_read;
// 	*syscall_table++ = &sys_write;
// 	*syscall_table++ = &sys_open;
// 	*syscall_table++ = &sys_close;
// 	*syscall_table++ = &sys_wait4;
}
