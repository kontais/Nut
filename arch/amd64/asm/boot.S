#
#After uefi firmware set processor to run in 64-bit mode,
#then bootloader load the kernel image to memory,and start
#execution from here.
#
boot:
	jmp        init        #Init global structures
	
	call        _mm_init   #Init the memory
	
	jmp        _main       #Run the kernel
	
