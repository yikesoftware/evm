#include<iostream>
#include "evm.h"
int evmLoadBinaryFile(const char *binaryFileName,unsigned int stackSize,unsigned int heapSize){
    //初始化虚拟机实例
    EVM *evmInstance = new EVM(binaryFileName,stackSize, heapSize);

    std::cout<<"[*] Start running EVM instance..."<<std::endl;
    std::cout<<"###############EVM I/O START################"<<std::endl;
    if(!runEvmInstance(evmInstance)){
        return 0;
    }
    std::cout<<"###############EVM I/O STOP#################"<<std::endl;
    return 1;
}

int runEvmInstance(EVM *evmInstance){
    //运行前检查是否成功初始化
    if(evmInstance->status.error!=-1){
        std::cerr<<getErrorText(evmInstance->status.error)<<std::endl;
        return 0;
    }
    evmInstance->status.running = 1; //设置运行标志
    
    do{
        
    }while(1);
    
    return 1;
}