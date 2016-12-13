#ifndef _PCI_H_
#define _PCI_H_

#include <io.h>
#include <klibc.h>

#define PCI_CONF_ADDR_REG_ADDR	0x0CF8
#define PCI_CONF_DATA_REG_ADDR	0x0CFC

static inline void __pci_conf_addr_reg_write(uint8_t bus, uint8_t dev, uint8_t func, uint8_t reg)
{
	assert(dev >> 5 == 0 && func >> 3 == 0 && reg >> 6 == 0);
	__io_write_32(PCI_CONF_ADDR_REG_ADDR, 1 << 31 | bus << 16 | dev << 11 | func << 8 | reg << 2);
}
static inline void __pci_conf_data_reg_write(uint32_t data)
{
	__io_write_32(PCI_CONF_DATA_REG_ADDR, data);
}
static inline uint32_t __pci_conf_addr_reg_read(void)
{
	return __io_read_32(PCI_CONF_ADDR_REG_ADDR);
}
static inline uint32_t __pci_conf_data_reg_read(void)
{
	return __io_read_32(PCI_CONF_DATA_REG_ADDR);
}

static inline void __pci_write_reg(uint8_t bus, uint8_t dev, uint8_t func, uint8_t reg, uint32_t data)
{
	__pci_conf_addr_reg_write(bus, dev, func, reg);
	__pci_conf_data_reg_write(data);
}
static inline uint32_t __pci_read_reg(uint8_t bus, uint8_t dev, uint8_t func, uint8_t reg)
{
	__pci_conf_addr_reg_write(bus, dev, func, reg);
	return __pci_conf_data_reg_read();
}



#endif
