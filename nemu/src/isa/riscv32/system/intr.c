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

#include <isa.h>

#ifdef CONFIG_ETRACE
// 定义一个环形缓冲区或数组来记录异常日志
#define ETRACE_BUF_SIZE 128
static struct {
  uint32_t epc;
  uint32_t cause;
} etrace_buf[ETRACE_BUF_SIZE];

static int etrace_index = 0;

static void etrace_record(uint32_t epc, uint32_t cause) {
  etrace_buf[etrace_index].epc = epc;
  etrace_buf[etrace_index].cause = cause;
  //add more there
  etrace_index = (etrace_index + 1) % ETRACE_BUF_SIZE;
}

void print_etrace(void){
  for (int i = 0; i < ETRACE_BUF_SIZE; i++) {
  printf("[ETRACE] cause = %d, epc = 0x%08x\n", 
         etrace_buf[i].cause, etrace_buf[i].epc);
}
}
#endif

word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
  //cpu.csrs.mstatus = 0x1800;
  cpu.csrs.mcause = NO;
  cpu.csrs.mepc = epc;
  #ifdef CONFIG_ETRACE
  // 在捕获异常时，记录一条 etrace 信息
  etrace_record(epc, NO);
  #endif
  return cpu.csrs.mtvec;
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
