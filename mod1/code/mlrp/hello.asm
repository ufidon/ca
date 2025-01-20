; yasm -f win64 hello.asm -o hello.obj
; link /subsystem:windows /entry:Start /LARGEADDRESSAWARE:NO hello.obj kernel32.lib user32.lib
; or
; cl /nologo /Fe:hello.exe hello.obj kernel32.lib user32.lib /link /entry:Start /subsystem:windows  /LARGEADDRESSAWARE:NO

section .data
    ; Define the message and title for the message box
    msg db 'Hello, World!', 0
    title db 'Hello', 0

section .text
    ; Import external Windows API functions
    extern __imp_MessageBoxA
    extern __imp_ExitProcess

global Start

Start:
    ; Call MessageBoxA to display the message box
    sub rsp, 28h                ; Align the stack (shadow space for 4 arguments + 8 bytes for alignment)
    xor rcx, rcx                ; hWnd = NULL (no owner window)
    lea rdx, [msg]              ; lpText = address of the message
    lea r8, [title]             ; lpCaption = address of the title
    xor r9, r9                  ; uType = MB_OK (0)
    call [rel __imp_MessageBoxA] ; Call MessageBoxA

    ; Call ExitProcess to exit the program
    xor rcx, rcx                ; uExitCode = 0
    call [rel __imp_ExitProcess] ; Call ExitProcess