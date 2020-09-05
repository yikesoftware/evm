#ifndef EVM_SYSCALL_H
#define EVM_SYSCALL_H
#include<unistd.h>
#include<stdint.h>
#include "evm.h"

uint8_t vmSyscall_stdin_read(EVM *instance, uint8_t len, uint8_t offset);
uint8_t vmSyscall_stdout_write(EVM *instance, uint8_t len, uint8_t offset);

struct vmSyscall_vtable{
    void *vmSyscall_0 = vmSyscall_stdin_read;
    void *vmSyscall_1 = vmSyscall_stdout_write;
};

#endif