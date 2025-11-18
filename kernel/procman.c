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
    uint32_t stackaddr = 0x01100000;

    threads[1].esp = stackaddr;
    threads[1].state = 1;
}