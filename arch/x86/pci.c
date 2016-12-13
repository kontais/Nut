#include <pci.h>

void ide_interface_init(void)
{

	printf("\n");
	for (int i = 0; i < 10; i ++)
	{
		printf("%x\n", __pci_read_reg(0, 1, 1, i));
	}
	for (int i = 0; i < 10; i ++)
	{
		printf("%x\n", __pci_read_reg(0, 1, 0, i));
	}

}
