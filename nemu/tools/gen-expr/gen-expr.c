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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
#define MAX_BUF_SIZE 65536

static char buf[MAX_BUF_SIZE] = {};
static char code_buf[MAX_BUF_SIZE + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";
static int buf_pos = 0;

//put a char to buf and manage the buf_Position
void gen(char c) {
  if (buf_pos < MAX_BUF_SIZE - 1) {
    buf[buf_pos++] = c;
    buf[buf_pos] = '\0';
  }
}

//0-999
void gen_num() {
  unsigned num = rand() % 1000; 
  char num_str[12];//  10 +1('\0') +1(buf)
  sprintf(num_str, "%u", num);


  if (buf_pos + strlen(num_str) < MAX_BUF_SIZE - 1) {
    strcat(buf + buf_pos, num_str);
    buf_pos += strlen(num_str);
  }
}

// operator
void gen_rand_op() {
  char ops[] = {'+', '-', '*', '/'};
  char op = ops[rand() % 4];
  if (rand() % 2 == 0) gen(' ');
  gen(op);
  if (rand() % 2 == 0) gen(' ');
}

// random number smaller than n
uint32_t choose(uint32_t n) {
  return rand() % n;
}


void gen_rand_expr() {
  //overflow
  if (buf_pos >= MAX_BUF_SIZE - 10) 
  return; 
  
  switch (choose(3)) {
    case 0:
      gen_num(); 
      break;
    case 1:
      gen('('); 
      if (rand() % 2 == 0) gen(' '); 
      gen_rand_expr();
      if (rand() % 2 == 0) gen(' '); 
      gen(')');
      break;
    default:
      gen_rand_expr(); 
      if (rand() % 2 == 0) gen(' ');  
      gen_rand_op(); 

      if (buf[buf_pos - 1] == '/') {
        unsigned num = 0;
        while (num == 0) {
          num = rand() % 1000; 
        }
        char num_str[12];
        sprintf(num_str, "%u", num);
        strcat(buf + buf_pos, num_str);
        buf_pos += strlen(num_str);
      } else {
        gen_rand_expr(); 
      }
      break;
  }
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    buf_pos = 0;

    gen_rand_expr();

    sprintf(code_buf, code_format, buf);//the expression to calculate is placed into %s.

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc  -Werror -Wdiv-by-zero -Woverflow -Wconversion /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }
  return 0;
}
