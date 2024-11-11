/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <common.h>
#include <stdio.h>
#include <utils.h>

#define Log(format, ...) \
    _Log(ANSI_FMT("[%s:%d %s] " format, ANSI_FG_BLUE) "\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define Assert(cond, format, ...) \
  do { \
    if (!(cond)) { \
      MUXDEF(CONFIG_TARGET_AM, printf(ANSI_FMT(format, ANSI_FG_RED) "\n", ## __VA_ARGS__), \
        (fflush(stdout), fprintf(stderr, ANSI_FMT(format, ANSI_FG_RED) "\n", ##  __VA_ARGS__))); \
      IFNDEF(CONFIG_TARGET_AM, extern FILE* log_fp; fflush(log_fp)); \
      extern void assert_fail_msg(); \
      assert_fail_msg(); \
      assert(cond); \
    } \
  } while (0)

#define IRINGBUF_SIZE 16


typedef struct {
    uint32_t pc;
    uint32_t inst;
    char asm_str[32];
} InstEntry;


extern InstEntry iringbuf[IRINGBUF_SIZE];
extern int iringbuf_index;

static inline void print_iringbuf() {
    // printf("Instruction trace leading to the error:\n");
    // for (int i = 0; i < IRINGBUF_SIZE; i++) {
    //     int index = (iringbuf_index + i) % IRINGBUF_SIZE;
    //     if (index == iringbuf_index) {
    //         printf("--> 0x%08x: %s    %08x\n", iringbuf[index].pc, iringbuf[index].asm_str, iringbuf[index].inst);
    //     } else {
    //         printf("    0x%08x: %s    %08x\n", iringbuf[index].pc, iringbuf[index].asm_str, iringbuf[index].inst);
    //     }
    // }
    printf("Instruction Trace Leading to the Error:\n");
    printf("    %-12s %-20s %-10s\n", "Address", "Instruction", "Encoding"); 
    printf("    ---------------------------------------------\n");
    iringbuf_index--;//the index will be added after writing
    for (int i = 0; i < IRINGBUF_SIZE; i++) {
        int index = (iringbuf_index + i) % IRINGBUF_SIZE;
        if (index == iringbuf_index) {
            printf("--> 0x%08x: %-20s 0x%08x\n", iringbuf[index].pc, iringbuf[index].asm_str, iringbuf[index].inst);
        } else {
            printf("    0x%08x: %-20s 0x%08x\n", iringbuf[index].pc, iringbuf[index].asm_str, iringbuf[index].inst);
        }
    }
}



#define panic(format, ...) \
    do { \
        print_iringbuf(); \
        Assert(0, format, ## __VA_ARGS__); \
    } while (0)

//#define panic(format, ...) Assert(0, format, ## __VA_ARGS__)

#define TODO() panic("please implement me")

#endif
