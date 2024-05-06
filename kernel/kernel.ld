ENTRY(kernel_main)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
    .boot : {
        ./build/multiboot.o
    }
    .idt_data 0x8000 : {
        *(.idt_data)
    }
    .text 0x8E00 : {
        ./build/kboot.o
    }
    .rodata : {
        
    }
}