#include <stdint.h>
#include <task.h>

thread_t threads[10];

void thread_init()
{
    threads[0].state = 1;
    current_task = &threads[0];
}

void create_task()
{
    uint32_t stackaddr = 0x02000000;

    threads[1].esp = stackaddr;
    threads[1].state = 1;
}

#define EXEC_ADDR  0x01000000
#define EXEC_STACK 0x02000000

void jump_to_exec(void)
{
    asm volatile (
        "cli\n"
        "mov %0, %%esp\n"
        "mov %0, %%ebp\n"
        "jmp *%1\n"
        :
        : "r"(EXEC_STACK), "r"(EXEC_ADDR)
        : "memory"
    );

    __builtin_unreachable();
}

void kill_task()
{
    
}