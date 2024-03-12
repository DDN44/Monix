ENTRY(kernel_main)
OUTPUT_FORMAT(binary)

SECTIONS
{
    .text 0x8E00 : {
        ./build/kboot.o
    }
}