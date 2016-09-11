#
#Init GDT, LDT, IDT, and TS.
#
init:

	#Fisrt disable page so that we can access physical address
	call mem_init
	
	
