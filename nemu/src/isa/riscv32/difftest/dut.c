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
#include <cpu/difftest.h>
#include "../local-include/reg.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  //bool flag = 0;
  for (int i = 0; i < 32; i++){
    //flag = (ref_r->gpr[i] == cpu.gpr[i]) ? true :false;//error only save the last result
    if(ref_r->gpr[i] != cpu.gpr[i]){
    printf("Mismatch in GPR[%d]: expected 0x%x, got 0x%x at PC 0x%x\n", i, ref_r->gpr[i], cpu.gpr[i], pc);
    return false;
    }
  }
  //flag = (ref_r->pc == cpu.pc) ? true :false;
  if(ref_r->pc != cpu.pc){
    printf("Mismatch in PC: expected 0x%x, got 0x%x\n", ref_r->pc, cpu.pc);
    return false;
  }
  return true;
}

void isa_difftest_attach() {
}
