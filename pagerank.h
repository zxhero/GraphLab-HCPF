#ifndef _PAGERANK_
#define _PAGERANK_
//hardware address#include"mmio.h"#include"../../rocket-chip/riscv-tools/riscv-pk/pk/pk.h"
#define READ_OFFSET1    0x2000#define READ_DATA1       0x2008#define READ_OFFSET23   0x2018#define READ_DATA23     0x2020#define REQUEST_ADDR    0x2030#define READ_STATUS1    0x2038#define READ_STATUS2    0x2040#define READ_STATUS3    0x2048#define WRITE_SENT      0x2050#define WRITEBACK_SENT    0x2051#define READ_SENT       0x2052
//hardware configuration
#define READ_BUFF_SIZE  1024
#define WRITE_BUFF_SIZE 1024 //1024*4 byte#define MAX_ID_NUM  63#define TYPE_1  1#define TYPE_2  2#define TYPE_3  3
/*#define NODE_SIZE
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
#define WRITE_BACK_OFF  0x1*///size, offset and ptr should be 10 bits width. raddr should be 28 bits width, and index is 2 bits width. data width is 32 bits and num width is 4 bits.#define Get_Read_Request(size, ptr, raddr, index)   ((((uint64_t)size) << 52) | (((uint64_t)ptr) << 30) | (((uint64_t)raddr) << 2) | (uint64_t)index)#define Get_Write1_Request(size, ptr, waddr)    ((((uint64_t)1) << 62) | (((uint64_t)size) << 52) | (((uint64_t)ptr) << 28) | (uint64_t)waddr)#define Get_WriteRB_Request(offset, data)       ((((uint64_t)3) << 62) | ((uint64_t)4 << 52) | (((uint64_t)offset) << 33) | (((uint64_t)data) << 1))#define Get_WriteWB_Request(ptr, data)  (((uint64_t)3 << 62) | ((uint64_t)4 << 52) | (((uint64_t)ptr) << 33) | (((uint64_t)data) << 1) | 1)#define Get_ReadF_WB_Request(size, num, ptr, offset)     ((((uint64_t)size) << 52) | (((uint64_t)num) << 48) | ((uint64_t)1 << 46) | (((uint64_t)ptr) << 14) | (((uint64_t)offset) << 4) | 12)#define Get_ReadF_Request(num, index)   ((((uint64_t)num) << 48) | (((uint64_t)index) << 46) | 4)#define Read_Format1(index, ptr_offset, data_offset1, data_offset2)  ((((uint64_t)index) << 62) | (((uint64_t)ptr_offset) << 56) | (((uint64_t)data_offset1) << 32) | (uint64_t)data_offset2)#define Read_Format23(index, data_offset1, data_offset2)    ((((uint64_t)index) << 62) | (((uint64_t)data_offset1) << 32) | (uint64_t)data_offset2)

uint32_t    queue_t[128];uint32_t    queue_ptr;uint32_t    operate_ptr;//free_ptr1//free_ptr2struct node{    uint32_t    id;    float       value;    uint32_t    in_edge_num;    uint32_t    in_edge_ptr;};struct edge{    //float       value;    uint32_t    source_nodeID;};#define node_num 1024#define node_size   sizeof(struct node)#define edge_size   sizeof(struct edge)
//base layer#define send_request(request)     reg_write64(REQUEST_ADDR,request)#define add_node_to_update_queue(nodeID);    queue_t[queue_ptr] = nodeID; \                                            if(queue_ptr == 127) queue_ptr = 0;\                                            else   queue_ptr ++;#define nodeID_to_Faddr(nodeID)#define fetch_node(nodeID);      send_request(Get_Read_Request(node_size,free_ptr1,nodeID_to_Faddr(nodeID),TYPE_1));   \                                if(free_ptr1 == MAX_ID_NUM)     free_ptr1 = 0;\                                else    free_ptr1++;#define fetch_edge(edge_faddr, edge_num);       send_request(Get_Read_Request(edge_size*edge_num, free_ptr2, edge_faddr, TYPE_2));  \                                                if(free_ptr2 == MAX_ID_NUM)     free_ptr2 = 0;  \                                                else    free_ptr2++;#define get_node(node_ptr_offset)              reg_write64(READ_OFFSET1, Read_Format1(TYPE_1, node_ptr_offset, 0, 2))#define get_edges(edgeID)        reg_write64(READ_OFFSET23, Read_Format23(TYPE_2, edgeID, edgeID+2))#define read_node_info(info1, info2, info3);     info3 = reg_read32(READ_DATA1+12);  \                                                 uint64_t data = reg_read64(READ_DATA1 + 4); \                                                 info2 = (uint32_t)(data >> 32); \                                                 info1 = (uint32_t)data;#define read_neighbor_value(value)              value = reg_read32(READ_DATA1+12);#define read_edges_hinfo(info1, info2)           uint64_t data = reg_read64(READ_DATA23);   \                                                 info1 = (uint32_t)data;    \                                                 info2 = (uint32_t)(data >> 32);#define read_edges_linfo(info1, info2)           uint64_t data = reg_read64(READ_DATA23 + 8);   \                                                 info1 = (uint32_t)data;    \                                                 info2 = (uint32_t)(data >> 32);//#define fetch_neighbor()//#define get_neighbor(neighbo_ptr)

void pagerank();

/*#define get_data(data1, data2)  \
    data = reg_read64(READ_DATA); \
    data1 = (uint32_t) (data >> 32); \
    data2 = (uint32_t) data;*/

#endif // _PAGERANK_
