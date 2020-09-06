#ifndef EVM_INSTRUCTIONS_H
#define EVM_INSTRUCTIONS_H

//instructions
//基础运算指令
#define iadd 0x20u
#define isub 0x21u
#define imul 0x22u
#define idiv 0x23u
#define icmp 0x24u
#define iinc 0x25u
#define idec 0x26u

//位运算指令
#define iand 0x30u
#define ior 0x31u
#define ixor 0x32u
#define inot 0x33u
#define ishl 0x34u
#define ishr 0x35

//栈操作
#define push 0x40u//立即值
#define pop 0x41u //立即值
#define pusha 0x42u//reg A
#define pushb 0x43u//reg B
#define pushc 0x44u//reg C
#define pushd 0x45u//reg D
#define popa 0x46u
#define popb 0x47u
#define popc 0x48u
#define popd 0x49u

//寄存器操作(接立即值)
#define mova 0x50u
#define movb 0x51u
#define movc 0x52u
#define movd 0x53u

//堆内存操作
#define storea 0x60u
#define storeb 0x61u
#define storec 0x62u
#define stored 0x63u
#define geta 0x64u
#define getb 0x65u
#define getc 0x66u
#define getd 0x67u

//转移指令
#define jmp 0x70u//接binary偏移
#define jz 0x71u
#define jnz 0x72u

//“系统调用”
#define syscall 0x80u//接调用表偏移

//结束
#define halt 0x90u

#endif