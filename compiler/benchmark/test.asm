global lexer_process

section .text

; rsi : string data (const char*)
; rax : current char
; rbx : current shape
; rcx : loop counter
; rdx : temporary data
; r8 : shape (shape*)
    ; +0 uint8_t id = 0;
    ; +8 uint8_t type = 0;
    ; +16 uint64_t data = 0;


scalar_element equ 0x00000001
vector_sequence equ 0x00000006

shape_type equ 8
shape_data equ 16

; input
    ; rcx : data
    ; rdx : vector<shapes>.data
lexer_process:
    ;push rsi

    mov rax, [rdx + shape_data]
    ret

    mov rsi, rcx
    xor rcx, rcx
    not rcx
    xor rax, rax

    mov r8, rdx
    xor r10, r10


main_loop:
    inc rcx                      ; start at 0
    mov al, [rsi + rcx]          ; copy data char to rax
    cmp rax, 0
    je main_end                  ; rax == 0 : end of string

    mov rbx, [r8 + shape_type]
    mov rdx, scalar_element
    cmp rbx, rdx                 ; compare shape_type
    je process_scalar_element

    mov rdx, vector_sequence
    cmp rbx, rdx                 ; compare shape_type
    je process_vector_sequence


    jmp main_loop

main_end:
    ;pop rsi
    mov rax, r10
    ret

process_scalar_element:
    cmp rax, [r8 + shape_data]
    je scalar_element_match
    jmp main_loop

scalar_element_match:
    inc r10
    jmp main_loop

process_vector_sequence:

    jmp main_loop


