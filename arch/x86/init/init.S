/**
  * Parameter passing by stack:
  * [         Image loading address          ]
  * [             Image size                 ]
  * [       UEFI memory map desc address     ]
  * [       UEFI memory map desc size        ]
  * [     UEFI memory map desc total size    ]
  *
  * 
  * After this,memory dialog looks like :
  * [Kernel Image] [UEFI Memory Descriptor Array] [Page tables]
  * All region boundary is aligned to 4KB boundary.
  * Kernel image consist of two parts:
  * Init: 
  * 	Initializing page tables and switch into virtual memory space,and execute kernel in the end.
  * Kernel:
  * 	The main body of kernel.
 **/
.globl _init,__INIT_END
_init:
	call	early_print_init
	
	mov	(%rsp),%rbp
	popq	image_base(%rbp)
	popq	image_size(%rbp)
	popq	mm_desc_addr(%rbp)
	popq	mm_desc_size(%rbp)
	popq	mm_desc_total(%rbp)
	
	call	init_mm_map
	call	load_mm_map
	call	init_dsc_tables
	call	load_dsc_tables_and_seg_sels
	
	mov	$0xfffff0fffffffff8, %rsp
	lea	__INIT_END, %rax
	add	$0xffffffff80000000, %rax
	jmp	*%rax
	
.globl	image_base, image_size, mm_desc_addr, mm_desc_size, mm_desc_total, page_table_base, page_table_size, stack_page_base, stack_pages
image_base:.quad 0
image_size:.quad 0
mm_desc_addr:.quad 0
mm_desc_size:.quad 0
mm_desc_total:.quad 0
page_table_base:.quad 0
page_table_size:.quad 0
stack_page_base:.quad 0
stack_pages:.quad 1
.section .zero
