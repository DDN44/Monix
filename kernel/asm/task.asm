bits 32
global switch_task, current_task

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

    pop ebp
    pop edi
    pop esi
    pop ebx

    ret

