cmake_minimum_required()

project(CB)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)

add_executable(${PROJECT_NAME} ./boot/boot.asm)

