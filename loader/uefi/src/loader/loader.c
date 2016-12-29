#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>

#include <Library/TimerLib.h>
#include <Library/UefiBootServicesTableLib.h>
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
	}

  return EFI_SUCCESS;
}
