#include<cstdio>
#include<unistd.h>
#include<stdint.h>



#ifndef EVM_H
#define EVM_H

#define BINARY_MAX_SIZE 255
#define STACK_MIN_SIZE 32
#define STACK_MAX_SIZE 255
#define HEAP_MIN_SIZE 32
#define HEAP_MAX_SIZE 255

const char statusToText[5][128] = {
    "[-] ERROR 00: EVM instance memory allocation failed!",
    "[-] ERROR 01: The binary file size exceeds the upper limit!",
    "[-] ERROR 02: Unable to read binary file!",
    "[-] ERROR 03: Unknown instruction: ",
    "[-] ERROR 04: Stack smash detected!"
};

#define getErrorText(code) ({           \
    const char *text;                   \
    text = statusToText[code];          \
    text;                               \
})

#define getStackSize(size) ({           \
unsigned int retSize;                   \
if(size<STACK_MIN_SIZE){                \
    retSize = STACK_MIN_SIZE;           \
}                                       \
if(size>STACK_MAX_SIZE){                \
    retSize = STACK_MAX_SIZE;           \
}                                       \
else{                                   \
    retSize = size;                     \
}                                       \
retSize;                                \
})                                       

#define getHeapSize(size) ({            \
unsigned int retSize;                   \
if(size<HEAP_MIN_SIZE){                 \
    retSize = HEAP_MIN_SIZE;            \
}                                       \
if(size>HEAP_MAX_SIZE){                 \
    retSize = HEAP_MAX_SIZE;            \
}                                       \
else{                                   \
    retSize = size;                     \
}                                       \
retSize;                                \
})      

#define getBinaryFileSize(binFILE) ({               \
unsigned int binStart = ftell(binFILE);             \
fseek(binFILE, 0, SEEK_END);                        \
unsigned int binSize = ftell(binFILE) - binStart;   \
fseek(binFILE, 0, SEEK_SET);                        \
binSize;                                            \
})

#define nextIp(instance)({          \
    instance->regs.ip++;            \
})

#define setCarryFlag(instance)({                \
    instance->regs.eflag |= 0x1;                \
})

#define setOverflowFlag(instance)({             \
    instance->regs.eflag |= 0x2;                \
})

#define setZeroFlag(instance)({                 \
    instance->regs.eflag |= 0x4;                \
})

#define checkStackUnderflow(instance)({                             \
    int result = (instance->regs.sp) <= instance->mem.stackSize?0:1;\
    result;                                                         \
})

#define checkStackOverflow(instance)({                  \
    int result = (instance->regs.sp)<0?1:0;             \
    result;                                             \
})

#define checkHeapOverflow(instance, offset)({                       \
    int result = (offset) <= instance->mem.heapSize?0:1;            \
    result;                                                         \
})

#define checkHeapUnderflow(instance, offset)({          \
    int result = (offset)<0?1:0;                        \
    result;                                             \
})

#define fetchNext(instance,ip)({                                        \
    uint8_t nextInstruction;                                            \
    if(ip>instance->mem.binarySize){                                    \
        std::cerr<<"[-] Out of memory!"<<std::endl;                     \
        return 0;                                                       \
    }                                                                   \
    nextInstruction = *(uint8_t *)((instance->mem.binaryMem)+ip);       \
    ip++;                                                               \
    nextInstruction;                                                    \
})

struct REGs{
    uint8_t eflag; //[0,0,0,0,0,(zero flag),(溢出),(进位)]
    uint8_t A, B, C, D;
    unsigned int sp;
    unsigned int ip;
};

struct STATUS{
    uint8_t running;
    unsigned int io;
    int error;
};

struct MEM{
    unsigned int binarySize;
    uint8_t *binaryMem;
    unsigned int stackSize;
    uint8_t* stack;
    unsigned int heapSize;
    uint8_t* heap;
};

class EVM{
    public:
        REGs regs;
        STATUS status;
        MEM mem;
        EVM(const char *binaryFileName,unsigned int stackSize, unsigned int heapSize){
            std::cout<<"[*] EVM instance initializing..."<<std::endl;
            memset(&this->regs,0,sizeof(REGs));
            memset(&this->status,0,sizeof(STATUS));
            status.error = -1;
            mem.stackSize = getStackSize(stackSize); //获取正确的内存大小
            mem.heapSize = getHeapSize(heapSize);
            mem.stack = (uint8_t *)malloc(mem.stackSize);
            mem.heap = (uint8_t *)malloc(mem.heapSize);
            if(!mem.stack || !mem.heap){
                status.error = 0; //无法分配内存
            }
            FILE *bin = fopen(binaryFileName, "rb");
            if(!bin){
                status.error = 2; //无法载入二进制文件
            }
            unsigned int binaryFileSize = getBinaryFileSize(bin);
            if(binaryFileSize>BINARY_MAX_SIZE){
                status.error = 1; //二进制文件过大
            }
            mem.binarySize = binaryFileSize-1;
            mem.binaryMem = (uint8_t *)malloc(binaryFileSize+1);
            if(!mem.binaryMem){
                status.error = 0; //无法分配内存
            }
            fread(mem.binaryMem, 1, binaryFileSize, bin);
            fclose(bin);
        }
};

int evmLoadBinaryFile(const char *binaryFileName,unsigned int stackSize,unsigned int heapSize);
int runEvmInstance(EVM *evmInstance);

#endif