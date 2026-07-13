bits 32
global switch_task, current_task
extern tss

cur_task:
current_task dd 0

switch_task:
    push ebx
    push esi
    push edi
    push ebp

    mov [current_task], esp
    mov eax, [esp + 4]

    mov ebx, cur_task
    mov [ebx], eax

    mov esp, [eax]
    mov [tss + 4], esp

    pop ebp
    pop edi
    pop esi
    pop ebx

    ret

