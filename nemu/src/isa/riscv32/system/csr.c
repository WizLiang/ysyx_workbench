#include <isa.h>

// 如果只有少数CSR，直接用switch区分即可；也可做更复杂的映射。
word_t csr_read(int csr_index) {
  switch (csr_index) {
    case 0x300: // mstatus
      return cpu.csrs.mstatus;
    case 0x305: // mtvec
      return cpu.csrs.mtvec;
    case 0x341: // mepc
      return cpu.csrs.mepc;
    case 0x342: // mcause
      return cpu.csrs.mcause;
    // 更多CSR编号可在 spec 中查表
    default:
      panic("csr_read(0x%x) not implemented!\n", csr_index);
      return 0;
  }
}

void csr_write(int csr_index, word_t val) {
  switch (csr_index) {
    case 0x300: // mstatus
      cpu.csrs.mstatus = val;
      break;
    case 0x305: // mtvec
      cpu.csrs.mtvec = val;
      break;
    case 0x341: // mepc
      cpu.csrs.mepc = val;
      break;
    case 0x342: // mcause
      cpu.csrs.mcause = val;
      break;
    // 更多CSR编号可在 spec 中查表
    default:
      panic("csr_write(0x%x) not implemented!\n", csr_index);
  }
}
