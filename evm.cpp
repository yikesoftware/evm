#include<iostream>
#include "evm.h"
int evmLoadBinaryFile(const char *binaryFileName,unsigned int stackSize,unsigned int heapSize){
    EVM *evmInstance = new EVM(binaryFileName,stackSize, heapSize);
    if(!runEvmInstance(evmInstance)){
        return 0;
    }
    return 1;
}

int runEvmInstance(EVM *evmInstance){
    if(evmInstance->status.error!=-1){
        std::cerr<<getErrorText(evmInstance->status.error)<<std::endl;
        return 0;
    }
    evmInstance->status.running = 1;
    std::cout<<"[*] Start running EVM instance..."<<std::endl;
    std::cout<<"###############EVM I/O START################"<<std::endl;
    std::cout<<"###############EVM I/O STOP#################"<<std::endl;
    return 1;
}