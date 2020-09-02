#include<cstdio>
#include<cstring>
#include<stdlib.h>

#include<iostream>
#include "evm.h"

void goInit(){
    setvbuf(stdin,0,2,0);
    setvbuf(stdout,0,2,0);
    setvbuf(stderr,0,2,0);
}

void info(){
    std::cout<<"EVM V0.0.1"<<std::endl;
}

int main(int argc, char *argv[]){
    const char *binaryFileName = argv[1];
    std::cout<<"[*] Try to instantiate a new EVM instance from: "<<binaryFileName<<std::endl;
    unsigned int initStackSize = atoi(argv[2]);
    unsigned int initHeapSize = atoi(argv[3]);
    if(!evmLoadBinaryFile(binaryFileName,initStackSize,initHeapSize)){
        std::cerr<<"[-] Fail to load your binary file!"<<std::endl;
        exit(0);
    }
    else{
        std::cout<<"[+] Finished."<<std::endl;
    }
    return 0;
}