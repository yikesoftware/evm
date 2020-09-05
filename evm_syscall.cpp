#include "evm_syscall.h"

uint8_t vmSyscall_stdin_read(EVM *instance, uint8_t len, uint8_t offset){
    uint8_t ret2reg;
    ret2reg = read(0,instance->mem.heap+offset,len);
    return ret2reg;
}

uint8_t vmSyscall_stdout_write(EVM *instance, uint8_t len, uint8_t offset){
    uint8_t ret2reg;
    ret2reg = write(1,instance->mem.heap+offset,len);
    return ret2reg;
}
