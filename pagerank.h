#ifndef _PAGERANK_
#define _PAGERANK_
//hardware address
#define REQUEST_ADDR    0x2010
#define READ_OFFSET     0x2000
#define READ_DATA       0x2008
//hardware configuration
#define READ_BUFF_SIZE  512
#define WRITE_BUFF_SIZE 512 //512*8 byte
#define NODE_SIZE
//type code
#define READ    0x00
#define WRITE_EN_1  0x1
#define WRITE_EN_2  0x2
#define WRITE_BUFF 0x3
//option code
#define WRITE_BUFF  0x1
#define READ_BUFF   0x0
#define READ_FINISH 0x0

#define type_mask   0x3
#define size_mask   0x3ff
#define addr_mask   0xfff_ffff
#define dptr_mask   0x3ff
//write back code
#define WRITE_BACK_ON   0x3
#define WRITE_BACK_OFF  0x1

#include<stdint.h>
#include"../riscv-tools/riscv-pk/pk/mmio.h"
//base layer
inline void send_request(uint8_t type, uint8_t option, uint16_t dsize, uint16_t dptr, uint16_t offset, uint32_t addr, \
                        uint32_t data, uint8_t write_back){
    uint64_t request;
    if(type == READ && option != READ_FINISH){
        request = 0 | ((dsize & size_mask) << 52) | ((dptr & dptr_mask) << 30) | ((addr & addr_mask) << 2) | (option & 0x3);
    }else if(type == WRITE_EN_1){
        request = 0 | (WRITE_EN_1 << 62) | ((dsize & size_mask) << 52) | ((dptr & dptr_mask) << 28) | (addr & addr_mask);
    }else if(type == WRITE_EN_2){
        request = 0 | (WRITE_EN_2 << 62) | (0x3 << 60) | (data << 28) | (addr & addr_mask);
    }else if(type == WRITE_BUFF && option == WRITE_BUFF){
        request = 0 | (WRITE_BUFF << 62) | (0x3 << 60) | ((dptr & dptr_mask) << 33) | (data << 1) | WRITE_BUFF
    }else if(type == WRITE_BUFF && option == READ_BUFF){
        request = 0 | (WRITE_BUFF << 62) | (0x3 << 60) | ((offset & dptr_mask) << 33) | (data << 1) | READ_BUFF
    }else if(type == READ && option == READ_FINISH){
        request = 0 | ((offset & dptr_mask) << 4) | (write_back << 2) | (option & 0x3);
    }else{
        printk("Wrong Type: 0x%x\n",type);
        exit(1);
    }
    reg_write64(REQUEST_ADDR, request);
}

inline void read_at(uint32_t offset){
    uint64_t addr = (uint64_t) offset;
    reg_write64(READ_OFFSET,addr);
}

//Middle layer
inline uint32_t GetValue(){

}

inline void MutableValue(){

}

inline void VoteToHalt(){

}

inline void SendMsgTo(){

}

inline void init_graph(){

}

void pagerank();

#define get_data(data1, data2)  \
    data = reg_read64(READ_DATA); \
    data1 = (uint32_t) (data >> 32); \
    data2 = (uint32_t) data;

#endif // _PAGERANK_
