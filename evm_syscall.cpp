#include "evm.h"
#define syscall_0 vmSyscall_stdin_read
#define syscall_1 vmSyscall_stdout_write
#define SYSCALL_NUM 2

uint8_t vmSyscall_stdin_read(void *instance){
    uint8_t ret2reg;
    void *readToAddr = ((EVM *)instance)->mem.heap+((EVM *)instance)->regs.B;
    unsigned length = ((EVM *)instance)->regs.C;
    ((EVM *)instance)->status.io = 1;
    ret2reg = read(0,readToAddr,length);
    ((EVM *)instance)->status.io = 0;
    return (uint8_t)ret2reg;
}

uint8_t vmSyscall_stdout_write(void *instance){
    uint8_t ret2reg;
    void *writeToAddr = ((EVM *)instance)->mem.heap+((EVM *)instance)->regs.B;
    unsigned length = ((EVM *)instance)->regs.C;
    ((EVM *)instance)->status.io = 1;
    ret2reg = write(1,writeToAddr,length);
    ((EVM *)instance)->status.io = 0;
    return (uint8_t)ret2reg;
}

uint8_t vmSyscall_int(void *instance, int scn){
    vmSyscall_vtable_solve(((EVM *)instance));
    if(scn < SYSCALL_NUM){
        return ((EVM *)instance)->syscalls.ptrArray[scn](((EVM *)instance));
    }
    else{
        std::cerr<<"[-] The system call number does not exist."<<std::endl;
        return -1;
    }
}

void vmSyscall_vtable_solve(void *instance){
    if(!((EVM *)instance)->syscalls.ifsolve){
        ((EVM *)instance)->syscalls.ptrArray = new vmSyscall_vptr[SYSCALL_NUM];
        ((EVM *)instance)->syscalls.ptrArray[0] = syscall_0;
        ((EVM *)instance)->syscalls.ptrArray[1] = syscall_1;
        ((EVM *)instance)->syscalls.ifsolve = 1; //solve标志
    }
}
