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

#include "local-include/reg.h"
#include <cpu/cpu.h>
#include <cpu/ifetch.h>
#include <cpu/decode.h>

#define R(i) gpr(i)
#define Mr vaddr_read
#define Mw vaddr_write

enum {
  TYPE_I, TYPE_U, TYPE_S, TYPE_J, TYPE_R, TYPE_B,
  TYPE_N, // none
};



// Function to get the upper 32 bits of the product of two signed 32-bit integers
static inline int32_t signed_upper_half(int32_t src1, int32_t src2) {
    int64_t result = (int64_t)src1 * (int64_t)src2;
    return (int32_t)(result >> 32);
}

// Function to get the upper 32 bits of the product of two unsigned 32-bit integers
static inline uint32_t unsigned_upper_half(uint32_t src1, uint32_t src2) {
    uint64_t result = (uint64_t)src1 * (uint64_t)src2;
    return (uint32_t)(result >> 32);
}

// Function to get the upper 32 bits of the product of a signed and an unsigned 32-bit integers
static inline int32_t signed_unsigned_upper_half(int32_t src1, uint32_t src2) {
    int64_t result = (int64_t)src1 * (uint64_t)src2;
    return (int32_t)(result >> 32);
}

#define src1R() do { *src1 = R(rs1); } while (0)
#define src2R() do { *src2 = R(rs2); } while (0)
#define immI() do { *imm = SEXT(BITS(i, 31, 20), 12); } while(0)
#define immU() do { *imm = SEXT(BITS(i, 31, 12), 20) << 12; } while(0)
#define immS() do { *imm = (SEXT(BITS(i, 31, 25), 7) << 5) | BITS(i, 11, 7); } while(0)
//#define immJ() do { *imm = ((SEXT(BITS(i, 30, 21), 11)) | (BITS(i, 19, 12) << 12)|  (BITS(i, 31, 31) << 20)| (BITS(i, 20, 20) << 11)) << 1; } while(0)
#define immJ() do { *imm = (SEXT(BITS(i, 31, 31), 1) << 20)  /* imm[20] */\
                    | (BITS(i, 30, 21) << 1)                 /* imm[10:1] */\
                    | (BITS(i, 20, 20) << 11)                /* imm[11] */\
                    | (BITS(i, 19, 12) << 12);               /* imm[19:12] */\
                  } while(0)
#define immB() do { *imm = (SEXT(BITS(i, 31, 31), 1) << 12)  /* imm[12] */ \
                    | (BITS(i, 30, 25) << 5)                /* imm[10:5] */ \
                    | (BITS(i, 11, 8) << 1)                /* imm[4:1] */ \
                    | (BITS(i, 7, 7) << 11);                /* imm[11] */ \
                  } while(0);\
                  //printf("Calculated imm for B-type: %x\n", *imm);



/*
31 30-21 20 19-12
20 10:1 11
*/
static void decode_operand(Decode *s, int *rd, word_t *src1, word_t *src2, word_t *imm, int type) {
  uint32_t i = s->isa.inst;
  //printf("Instrution: %x\n", i);
  int rs1 = BITS(i, 19, 15);
  int rs2 = BITS(i, 24, 20);
  *rd     = BITS(i, 11, 7);
  switch (type) {
    case TYPE_I: src1R();          immI(); break;
    case TYPE_U:                   immU(); break;
    case TYPE_S: src1R(); src2R(); immS(); break;
    case TYPE_J:                   immJ(); break;
    case TYPE_R: src1R(); src2R();         break;
    case TYPE_B: src1R(); src2R();  immB();break;
    case TYPE_N: break;
    default: panic("unsupported type = %d", type);
  }
}

static int decode_exec(Decode *s) {
  s->dnpc = s->snpc;

#define INSTPAT_INST(s) ((s)->isa.inst)
#define INSTPAT_MATCH(s, name, type, ... /* execute body */ ) { \
  int rd = 0; \
  word_t src1 = 0, src2 = 0, imm = 0; \
  decode_operand(s, &rd, &src1, &src2, &imm, concat(TYPE_, type)); \
  __VA_ARGS__ ; \
}
//jal ret mv j 

  INSTPAT_START();

  //INSTPAT("0000000 00000 00001 000 00000 11001 11", ret    , I, R(rd) = s->pc + 4; s->dnpc = R(1););  // ret （等价于 jalr x0, x1, 0）
  //INSTPAT("0000000 ????? ????? 000 ????? 00100 11", mv     , I, R(rd) = src1;);//addi rd, rs, 0 
  //INSTPAT("??????? ????? ????? ??? 00000 11011 11", j      , J, R(rd) = s->pc + 4; s->dnpc = s->pc + imm;);//（jal x0, offset）
  //Arithmetic
  INSTPAT("0000000 ????? ????? 000 ????? 01100 11", add    , R, R(rd) = src2 + src1);
  INSTPAT("??????? ????? ????? 000 ????? 00100 11", addi   , I, R(rd) = (int32_t)imm + src1;);
  INSTPAT("0100000 ????? ????? 000 ????? 01100 11", sub    , R, R(rd) = src1 - src2);
  INSTPAT("0000001 ????? ????? 000 ????? 01100 11", mul    , R, R(rd) = (src1 * src2 )& 0xFFFFFFFF;);
  INSTPAT("0000001 ????? ????? 001 ????? 01100 11", mulh   , R, R(rd) = signed_upper_half(src1,src2););
  INSTPAT("0000001 ????? ????? 011 ????? 01100 11", mulhu  , R, R(rd) = unsigned_upper_half((uint32_t)src1, (uint32_t)src2));//untested
  INSTPAT("0000001 ????? ????? 010 ????? 01100 11", mulhsu , R, R(rd) = signed_unsigned_upper_half(src1, (uint32_t)src2));//untested

  INSTPAT("0000001 ????? ????? 100 ????? 01100 11", div    , R, R(rd) = (int32_t)src1 / (int32_t)src2;);
  INSTPAT("0000001 ????? ????? 101 ????? 01100 11", divu   , R, R(rd) = (uint32_t)src1 / (uint32_t)src2;);
  INSTPAT("0000001 ????? ????? 110 ????? 01100 11", rem    , R, R(rd) = (int32_t)src1 % (int32_t)src2;);//Remainder	rem rd, rs1, rs2	rd = rs1 % rs2
  INSTPAT("0000001 ????? ????? 111 ????? 01100 11", remu   , R, R(rd) = (uint32_t)src1 % (uint32_t)src2;);

  

  //branch
  //imm[12|10:5] rs2 rs1 funct3 imm[4:1|11] opcode B
  INSTPAT("??????? ????? ????? 000 ????? 11000 11", beq    , B, if ((int32_t)src1 == (int32_t)src2) s->dnpc = s->pc + imm;);//	if(rs1 == rs2) pc += imm 
  INSTPAT("??????? ????? ????? 101 ????? 11000 11", bge    , B, if ((int32_t)src1 >= (int32_t)src2) s->dnpc = s->pc + imm;);//Branch Greater or Equal if(rs1 ≥ rs2) pc += imm
  INSTPAT("??????? ????? ????? 001 ????? 11000 11", bne    , B, if ((int32_t)src1 != (int32_t)src2) s->dnpc = s->pc + imm;);//if(rs1 ≠ rs2) pc += imm
  INSTPAT("??????? ????? ????? 100 ????? 11000 11", blt    , B, if ((int32_t)src1 < (int32_t)src2) s->dnpc = s->pc + imm;);//Branch less than  if(rs1 < rs2) pc += imm
  INSTPAT("??????? ????? ????? 110 ????? 11000 11", bltu   , B, if ((uint32_t)src1 < (uint32_t)src2) s->dnpc = s->pc + imm;);//Branch less than  if(rs1 < rs2) pc += imm
  INSTPAT("??????? ????? ????? 111 ????? 11000 11", bgeu   , B, if ((uint32_t)src1 >= (uint32_t)src2) s->dnpc = s->pc + imm;);


  //bitwise logic  Integer Register-Register Operation
  INSTPAT("??????? ????? ????? 111 ????? 00100 11", andi   , I, R(rd) = src1 & (int32_t)imm;);
  //       0000111 11111 01110 111 01111 00100 11
  INSTPAT("0000000 ????? ????? 111 ????? 01100 11", and    , R, R(rd) = src1 & src2;);
  INSTPAT("0000000 ????? ????? 100 ????? 01100 11", xor    , R, R(rd) = src1 ^ src2;);
  INSTPAT("0000000 ????? ????? 110 ????? 01100 11", or     , R, R(rd) = src1 | src2;);

  //INSTPAT("??????? ????? ????? 100 ????? 00100 11", not    , I, R(rd) = ~src1;);// xori rd, rs, -1
  INSTPAT("1111111 11111 ????? 100 ????? 00100 11", not    , I, R(rd) = ~src1;);// xori rd, rs, -1
  //INSTPAT("??????? ????? ????? 100 ????? 00100 11", xori   , I, R(rd) = src1 ^ imm;);// check signed?



  
  INSTPAT("??????? ????? ????? ??? ????? 01101 11", lui    , U, R(rd) = imm;);
  INSTPAT("??????? ????? ????? 100 ????? 00100 11", xori   , I, R(rd) = src1 ^ (int32_t)imm ;);
  
  //set
  /*SLTU rd, x0, rs2 sets rd to 1 if rs2 is not equal to zero, otherwise sets rd to zero (assembler
  pseudoinstruction SNEZ rd, rs)*/
  INSTPAT("0000000 ????? 00000 011 ????? 01100 11", snez   , R, R(rd) = (src2 != 0) ? 1 : 0;);
  INSTPAT("0000000 ????? ????? 011 ????? 01100 11", sltu   , R, R(rd) = (uint32_t)src1 < (uint32_t)src2 ? 1 : 0;);//Set Less Than Unsigned
  INSTPAT("0000000 ????? ????? 010 ????? 01100 11", slt    , R, R(rd) = ((int32_t)src1 < (int32_t)src2) ? 1 : 0;);
  INSTPAT("0000000 00001 ????? 011 ????? 00100 11", seqz   , I, R(rd) = (src1 == 0) ? 1 : 0;); //sltiu rd, rs, 1

  //shift
  INSTPAT("0000000 ????? ????? 001 ????? 01100 11", sll    , R, R(rd) = (uint32_t)src1 << (src2 & 0x1F););//Shift Left Logical
  INSTPAT("0000000 ????? ????? 101 ????? 01100 11", srl    , R, R(rd) = (uint32_t)src1 >> (src2 & 0x1F););//Shift Right Logical
  INSTPAT("0100000 ????? ????? 101 ????? 01100 11", sra    , R, R(rd) = (int32_t)src1 >> (src2 & 0x1F););//Shift Right Logical//sra	Shift Right Arithmetic	sra rd, rs1, rs2	rd = rs1 >>> rs2
  INSTPAT("0000000 ????? ????? 001 ????? 00100 11", slli   , I, R(rd) = (uint32_t)src1 << (imm & 0x1F););
  INSTPAT("0000000 ????? ????? 101 ????? 00100 11", srli   , I, R(rd) = (uint32_t)src1 >> (imm & 0x1F););
  INSTPAT("0100000 ????? ????? 101 ????? 00100 11", srai   , I, R(rd) = (int32_t)src1 >> (imm & 0x1F););//Shift Right Arithmetic Immediate

  

  INSTPAT("??????? ????? ????? ??? ????? 00101 11", auipc  , U, R(rd) = s->pc + imm);
  INSTPAT("??????? ????? ????? 100 ????? 00000 11", lbu    , I, R(rd) = Mr(src1 + imm, 1));
  
  INSTPAT("??????? ????? ????? ??? ????? 11011 11", jal    , J,  R(rd) = s->pc + 4; s->dnpc = s->pc + imm;);
  INSTPAT("??????? ????? ????? 000 ????? 11001 11", jalr   , I,  R(rd) = s->pc + 4; s->dnpc = src1 + imm;);

  //load & store
  INSTPAT("??????? ????? ????? 000 ????? 01000 11", sb     , S, Mw(src1 + imm, 1, src2));
  INSTPAT("??????? ????? ????? 001 ????? 01000 11", sh     , S, Mw(src1 + imm, 2, src2));
  INSTPAT("??????? ????? ????? 010 ????? 01000 11", sw     , S, Mw(src1 + imm, 4, src2));
  INSTPAT("??????? ????? ????? 000 ????? 00000 11", lb     , I, R(rd) = (int32_t)((int16_t)(Mr(src1 + imm, 1))));
  INSTPAT("??????? ????? ????? 001 ????? 00000 11", lh     , I, R(rd) = (int32_t)((int16_t)(Mr(src1 + imm, 2))));
  INSTPAT("??????? ????? ????? 101 ????? 00000 11", lhu    , I, R(rd) = (uint32_t)((uint16_t)(Mr(src1 + imm, 2))));
  INSTPAT("??????? ????? ????? 010 ????? 00000 11", lw     , I, R(rd) = Mr(src1 + imm, 4));





  INSTPAT("0000000 00001 00000 000 00000 11100 11", ebreak , N, NEMUTRAP(s->pc, R(10))); // R(10) is $a0
  INSTPAT("??????? ????? ????? ??? ????? ????? ??", inv    , N, INV(s->pc));
  INSTPAT_END();

  R(0) = 0; // reset $zero to 0

  return 0;
}

int isa_exec_once(Decode *s) {
  s->isa.inst = inst_fetch(&s->snpc, 4);
  return decode_exec(s);
}
