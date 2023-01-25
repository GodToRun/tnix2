#include "elf.h"
#include "task.h"
#include "syscall.h"
extern task_t *current_task;
void tfunc() {
    asm volatile("add $4, %esp");
    syscall_monitor_write("Hello, ELF!");
}
int exec(char *path) {
    int fret = fork();
    if (!fret) {
        fs_node_t *fsnode = finddir_fs(fs_root, path);
        int (*ptr)();
        /* Read in the binary contents */
        for (uintptr_t x = 0x30000000; x < 0x30000000 + fsnode->length; x += 0x1000) {
            alloc_frame(get_page(x, 1, current_directory), 0, 1);
        }
        Elf32_Ehdr *header = (Elf32_Ehdr *)0x30000000;
        read_fs(fsnode, 0, fsnode->length, (uint8_t *)header);
        /* Load the loadable segments from the binary */
	/*for (uintptr_t x = 0; x < (uint32_t)header->e_shentsize * header->e_shnum; x += header->e_shentsize) {
		Elf32_Shdr * shdr = (Elf32_Shdr *)((uintptr_t)header + (header->e_shoff + x));
		if (shdr->sh_addr) {
			 If this is a loadable section, load it up. */
			/*if (shdr->sh_addr < current_process->image.entry) {
				current_process->image.entry = shdr->sh_addr;
			}
			if (shdr->sh_addr + shdr->sh_size - current_process->image.entry > current_process->image.size) {
				current_process->image.size = shdr->sh_addr + shdr->sh_size - current_process->image.entry;
			}
			for (uintptr_t i = 0; i < shdr->sh_size + 0x2000; i += 0x1000) {
				alloc_frame(get_page(shdr->sh_addr + i, 1, current_directory), 0, 1);
			}
			if (shdr->sh_type == SHT_NOBITS) {
				memset((void *)(shdr->sh_addr), 0x0, shdr->sh_size);
			} else {
				memcpy((void *)(shdr->sh_addr), (void *)((uintptr_t)header + shdr->sh_offset), shdr->sh_size);
			}
		}
	}*/

        ptr = 0x30000000+header->e_entry;
        set_kernel_stack(current_task->kernel_stack+KERNEL_STACK_SIZE);
        switch_to_user((int)ptr);
        return 0xdeadcafe;
    }
    else {
        while(1) { }
    }
}