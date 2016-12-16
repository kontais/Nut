#include <syscall.h>
#include <klibc.h>
#include <mm.h>
#include <paging.h>
uint64_t *syscall_table = NULL;

void syscall_init(void)
{
	syscall_table = (uint64_t *)page_alloc(SYS_CALL_TABLE_SIZE);
	assert(syscall_table != INVALID_ADDR);
	
	memset(syscall_table, 0, SYS_CALL_TABLE_SIZE << 12);
	modify_chunk_mapping(get_current_plm4e(), SYSCALL_BASE, __convert_virt_to_phy((uint64_t)syscall_table), SYS_CALL_TABLE_SIZE, DEFAULT_PTE_FLAG);
	
// 	*syscall_table++ = &sys_syscall;
// 	*syscall_table++ = &sys_exit;
// 	*syscall_table++ = &sys_fork;
// 	*syscall_table++ = &sys_read;
// 	*syscall_table++ = &sys_write;
// 	*syscall_table++ = &sys_open;
// 	*syscall_table++ = &sys_close;
// 	*syscall_table++ = &sys_wait4;
}
