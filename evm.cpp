#include<iostream>
#include "evm.h"
#include "evm_instructions.h"
int evmLoadBinaryFile(const char *binaryFileName,unsigned int stackSize,unsigned int heapSize){
    //初始化虚拟机实例
    EVM *evmInstance = new EVM(binaryFileName,stackSize, heapSize);
    int result;
    std::cout<<"[*] Start running EVM instance..."<<std::endl;
    std::cout<<"###############EVM I/O START################"<<std::endl;
    result = runEvmInstance(evmInstance);
    std::cout<<"###############EVM I/O STOP#################"<<std::endl;
    return (!result)?0:1;
}

int abortWithError(EVM *instance){
    std::cerr<<getErrorText(instance->status.error)<<std::endl;
    return 0;
}

int runEvmInstance(EVM *evmInstance){
    //运行前检查是否成功初始化
    if(evmInstance->status.error!=-1){
        std::cerr<<getErrorText(evmInstance->status.error)<<std::endl;
        return 0;
    }
    evmInstance->status.running = 1; //设置运行标志
    uint8_t nI;
    uint8_t *stackBase = evmInstance->mem.stack;
    uint8_t *heapBase = evmInstance->mem.heap;
    uint8_t x,y;
    do{
        nI = fetchNext(evmInstance,evmInstance->regs.ip);
        x^=x;y^=y;
        switch(nI){
            case iadd:
                evmInstance->regs.sp -= 1;
                if(checkStackOverflow(evmInstance) || checkStackUnderflow(evmInstance)){
                    evmInstance->status.error = 4;
                    return abortWithError(evmInstance);
                }
                x = *(stackBase+evmInstance->regs.sp);
                y = *(stackBase+evmInstance->regs.sp+1);
                if(((unsigned int)x+(unsigned int)y)&0xFF00 > 0)
                    setOverflowFlag(evmInstance);
                *(stackBase+evmInstance->regs.sp+1) = (x+y)&0xFF;
                evmInstance->regs.sp += 1;
                nextIp(evmInstance);
                break;
            case isub:
                evmInstance->regs.sp -= 1;
                if(checkStackOverflow(evmInstance) || checkStackUnderflow(evmInstance)){
                    evmInstance->status.error = 4;
                    return abortWithError(evmInstance);
                }
                x = *(stackBase+evmInstance->regs.sp);
                y = *(stackBase+evmInstance->regs.sp+1);
                if(((unsigned int)x-(unsigned int)y)&0xFF00 > 0)
                    setOverflowFlag(evmInstance);
                *(stackBase+evmInstance->regs.sp+1) = (x-y)&0xFF;
                evmInstance->regs.sp += 1;
                nextIp(evmInstance);
                break;
            case imul:
                evmInstance->regs.sp -= 1;
                if(checkStackOverflow(evmInstance) || checkStackUnderflow(evmInstance)){
                    evmInstance->status.error = 4;
                    return abortWithError(evmInstance);
                }
                x = *(stackBase+evmInstance->regs.sp);
                y = *(stackBase+evmInstance->regs.sp+1);
                if(((unsigned int)x*(unsigned int)y)&0xFF00 > 0)
                    setOverflowFlag(evmInstance);
                *(stackBase+evmInstance->regs.sp+1) = (x*y)&0xFF;
                evmInstance->regs.sp += 1;
                nextIp(evmInstance);
                break;
            case idiv:
                evmInstance->regs.sp -= 1;
                if(checkStackOverflow(evmInstance) || checkStackUnderflow(evmInstance)){
                    evmInstance->status.error = 4;
                    return abortWithError(evmInstance);
                }
                x = *(stackBase+evmInstance->regs.sp);
                y = *(stackBase+evmInstance->regs.sp+1);
                *(stackBase+evmInstance->regs.sp+1) = (x/y)&0xFF;
                evmInstance->regs.sp += 1;
                nextIp(evmInstance);
                break;
            case icmp:
                evmInstance->regs.sp -= 1;
                if(checkStackOverflow(evmInstance) || checkStackUnderflow(evmInstance)){
                    evmInstance->status.error = 4;
                    return abortWithError(evmInstance);
                }
                x = *(stackBase+evmInstance->regs.sp);
                y = *(stackBase+evmInstance->regs.sp+1);
                if(x^y)
                    setZeroFlag(evmInstance);
                evmInstance->regs.sp += 1;
                nextIp(evmInstance);
                break;

            case iand:
                evmInstance->regs.sp -= 1;
                if(checkStackOverflow(evmInstance) || checkStackUnderflow(evmInstance)){
                    evmInstance->status.error = 4;
                    return abortWithError(evmInstance);
                }
                x = *(stackBase+evmInstance->regs.sp);
                y = *(stackBase+evmInstance->regs.sp+1);
                *(stackBase+evmInstance->regs.sp+1) = (x&y)&0xFF;
                evmInstance->regs.sp += 1;
                nextIp(evmInstance);
                break;
            case ior:
                evmInstance->regs.sp -= 1;
                if(checkStackOverflow(evmInstance) || checkStackUnderflow(evmInstance)){
                    evmInstance->status.error = 4;
                    return abortWithError(evmInstance);
                }
                x = *(stackBase+evmInstance->regs.sp);
                y = *(stackBase+evmInstance->regs.sp+1);
                *(stackBase+evmInstance->regs.sp+1) = (x||y)&0xFF;
                evmInstance->regs.sp += 1;
                nextIp(evmInstance);
                break;
            case ixor:
                evmInstance->regs.sp -= 1;
                if(checkStackOverflow(evmInstance) || checkStackUnderflow(evmInstance)){
                    evmInstance->status.error = 4;
                    return abortWithError(evmInstance);
                }
                x = *(stackBase+evmInstance->regs.sp);
                y = *(stackBase+evmInstance->regs.sp+1);
                *(stackBase+evmInstance->regs.sp+1) = (x^y)&0xFF;
                evmInstance->regs.sp += 1;
                nextIp(evmInstance);
                break;
            case inot:
                if(checkStackOverflow(evmInstance) || checkStackUnderflow(evmInstance)){
                    evmInstance->status.error = 4;
                    return abortWithError(evmInstance);
                }
                x = *(stackBase+evmInstance->regs.sp);
                *(stackBase+evmInstance->regs.sp) = (!x)&0xFF;
                nextIp(evmInstance);
                break;
            case ishl:
                evmInstance->regs.sp -= 1;
                if(checkStackOverflow(evmInstance) || checkStackUnderflow(evmInstance)){
                    evmInstance->status.error = 4;
                    return abortWithError(evmInstance);
                }
                x = *(stackBase+evmInstance->regs.sp);
                y = *(stackBase+evmInstance->regs.sp+1);
                *(stackBase+evmInstance->regs.sp) = (x<<y)&0xFF;
                evmInstance->regs.sp += 1;
                nextIp(evmInstance);
                break;
            case ishr:
                evmInstance->regs.sp -= 1;
                if(checkStackOverflow(evmInstance) || checkStackUnderflow(evmInstance)){
                    evmInstance->status.error = 4;
                    return abortWithError(evmInstance);
                }
                x = *(stackBase+evmInstance->regs.sp);
                y = *(stackBase+evmInstance->regs.sp+1);
                *(stackBase+evmInstance->regs.sp) = (x>>y)&0xFF;
                evmInstance->regs.sp += 1;
                nextIp(evmInstance);
                break;
            case halt:
                evmInstance->status.running = 0;
                std::cout<<"[*] Halt signal."<<std::endl;
                return 1;
            default:
                evmInstance->status.error = 3;
                std::cerr<<getErrorText(evmInstance->status.error)<<nI<<std::endl;
                return 0;
        }
    }while(1);
    return 0;
}