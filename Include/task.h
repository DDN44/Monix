#ifndef _TASK_H_
#define _TASK_H_

#include <stdint.h>

// task states:
// 0 - null
// 1 - Running
// 2 - Suspended

typedef struct threadstrct{
    void *esp;
    uint8_t state;
    uint8_t prio;
} __attribute__((packed)) thread_t;

extern uint32_t current_task;
extern thread_t threads[10];

extern void create_task();
extern void switch_task(thread_t *thread);
extern void thread_init();

#endif