/** @file
  This sample application bases on HelloWorld PCD setting 
  to print "UEFI Hello World!" to the UEFI Console.

  Copyright (c) 2006 - 2008, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials                          
  are licensed and made available under the terms and conditions of the BSD License         
  which accompanies this distribution.  The full text of the license may be found at        
  http://opensource.org/licenses/bsd-license.php                                            

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

**/

#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>

#include <Library/TimerLib.h>
#include <Library/UefiBootServicesTableLib.h>
// #include <Library/SerialPortLib.h>
#include <Library/IoLib.h>

#include <Protocol/SimpleFileSystem.h>
#include <Protocol/SerialIo.h>
/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.
*/
static inline void memdump(UINT64 addr)
{
	UINT64 result;
	asm(
		"mov %0, %%r8\n\t"
		"mov (%%r8), %1\n\t"
		:"=r"(result)        /* output */
		:"r" (addr)
		:        /* clobbered register */
	);
	
	Print (L"0x%16lX:0x%16lX\n", addr, result);
}
// void StartTimer(void)
// {
// 	UINT8 *ptr = (UINT8 *)0xb8000;
// 	for (int i = 0; i < 1024 * 768; i ++)
// 	{
// 		*(ptr + i) = 0;
// 	}
// }
int _strncmp(char *str1, char *str2, int n)
{
	int i = 0;
	for (; i < n; i ++)
	{
		if (*(str1 + i) != *(str2 + i))
			return -1;
		else if ((*(str1 + i) == '\0' && *(str2 + i) == '\0'))
			return 0;
	}
	return 0;
}

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
	EFI_STATUS Status;
	UINTN MemoryMapBufferSize;
	UINTN MapKey;
	UINTN DescriptorSize;
	UINT32 DescriptorVersion;
	EFI_MEMORY_DESCRIPTOR MemoryMap[128] = {0};
	MemoryMapBufferSize = sizeof(MemoryMap);
	
	
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFileSystem;
	EFI_FILE_PROTOCOL *Root;
	Status = gBS->LocateProtocol(&gEfiSimpleFileSystemProtocolGuid, NULL, (VOID **)&SimpleFileSystem);
	if (EFI_ERROR(Status)) {
		return Status;
	}
	Status = SimpleFileSystem->OpenVolume(SimpleFileSystem, &Root);
	
	EFI_FILE_PROTOCOL *Image_File_Handle;
	Status = Root->Open(Root,
		&Image_File_Handle,
		(CHAR16*)L"kernel.img",
		EFI_FILE_MODE_READ,
		0);
	if (EFI_ERROR(Status))
		Print(L"Cannot found kernel.\n");
	else 
	{
		UINT64 addr = 0x100000;
		gBS->AllocatePages(AllocateAddress, EfiLoaderCode, 0x100, &addr);
		UINTN BufferSize = 0x100000;
		Image_File_Handle->Read(Image_File_Handle, &BufferSize, (UINT64 *)addr);
		Print(L"Read file size %d.\n", BufferSize);
		Print(L"Read file addr %016lx.\n", addr);
		memdump((UINT64)addr);
		
		Status = gBS->GetMemoryMap(&MemoryMapBufferSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
		if (EFI_ERROR(Status))
		Print(L"MemoryMap buffer was too small.\n");
		Print(L"Memory map descriptor at address %016lx total size is %d bytes,%d bytes each,version %d.\n", MemoryMap, MemoryMapBufferSize, DescriptorSize, DescriptorVersion);
		
		gBS->ExitBootServices(ImageHandle, MapKey);
		asm (
			"push %4\r\n"
			"push %3\r\n"
			"lea %2, %%rax\r\n"
			"push %%rax\r\n"
			"push %1\r\n"
			"push %0\r\n"
			
			"mov %0, %%rax\r\n"
			"jmp *%%rax"
			:
			: "m" (addr), "m" (BufferSize), "m" (MemoryMap), "m"(DescriptorSize), "m" (MemoryMapBufferSize)
		);
// 		asm (
// 			"jmp *0x100000"
// 		);
	}
// 	EFI_SERIAL_IO_PROTOCOL *SerialPort;
// 	Status = gBS->LocateProtocol(&gEfiSerialIoProtocolGuid, NULL, (VOID **)&SerialPort);
// 	if (EFI_ERROR(Status)) {
// 		Print(L"No Serial IO Protocol.\n");
// 		return Status;
// 	}
// 	Status = SerialPort->SetAttributes(SerialPort, 115200, 0, 0, DefaultParity, 0, DefaultStopBits);
// 	UINTN count = 13;
// 	SerialPort->Write(SerialPort, &count, "Hello Moto.\n");
// 	
// 	IoWrite8(0x3F8 + 2, 0x00);
// asm (
// 	"here:"
// );
// 	SerialInitialize();
// 	Print(L"%02x\n", IoRead8(0x3F8));
// 	Print(L"%02x\n", IoRead8(0x3F8 + 1));
// 	Print(L"%02x\n", IoRead8(0x3F8 + 2));
// 	Print(L"%02x\n", IoRead8(0x3F8 + 3));
// 	Print(L"%02x\n", IoRead8(0x3F8 + 4));
// 	Print(L"%02x\n", IoRead8(0x3F8 + 5));
// 	Print(L"%02x\n", IoRead8(0x3F8 + 6));
// 	Print(L"%02x\n", IoRead8(0x3F8 + 7));
// 	char *str = "Hello,world.";
// 	SerialWrite((UINT8 *)str, 12);
	
//  	IoWrite8(0X3F8, 'A');
// 	IoWrite8(0X3F8, 0x0D);
// 	IoWrite8(0X3F8, 0x0A);
	
// 	IoWrite8(0x3F8 + 3, IoRead8(0x3F8 + 3) & (~(1 << 7)));
// 	Print(L"%02x\n", IoRead8(0x3CC));
// 	IoWrite8(0x3C4,0x00);
// 	IoWrite8(0x3C5,0x00);
// 	Print(L"%02x\n", IoRead8(0x3F9));
// 	IoWrite8(0x3F8 + 3, IoRead8(0x3F8 + 3) | (1 << 7));
// 	for (UINT8 i = 0; i < 8; i ++)
// 	{
// 		IoWrite8(0x3C4, i);
// 		Print(L"%02x\n", IoRead8(0x3C5));
// 	}
// 	IoWrite8(0x3CE, 0x06);
// 	IoWrite8(0x3CF, 0);
// 	for (int i = 0; i < 10; i ++)
// 	{
// 		Print(L"Devices %d:\n", i);
// 		IoWrite32(0x0CF8, 1 << 31 | i << 11);
// 		Print(L"%08x\n", IoRead32(0x0CFC));
// 		IoWrite32(0x0CF8, 1 << 31 | i << 11 | 1 << 2);
// 		Print(L"%08x\n", IoRead32(0x0CFC));
// 		IoWrite32(0x0CF8, 1 << 31 | i << 11 | 2 << 2);
// 		Print(L"%08x\n", IoRead32(0x0CFC));
// 	}
// 	UINT64 addr = 0x000000;
// 	gBS->AllocatePages(AllocateAddress, EfiLoaderCode, 256, &addr);
// 	for (char *ptr = (char *)0xe0090000; (UINT64)ptr <= 0xe0bfffff; ptr ++)
// 			*ptr = 0;
// 	for (char *ptr = (char *)0x000A0000; (UINT64)ptr <= 0x000BFFFF; ptr ++)
// 			*ptr = 0;
// 	
  return EFI_SUCCESS;
}
