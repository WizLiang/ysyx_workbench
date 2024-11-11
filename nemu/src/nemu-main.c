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

#include <common.h>
#include "./monitor/sdb/sdb.h"

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();
void test_p();
void parse_elf_file();

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
  if(elf_file_path){
    parse_elf_file(elf_file_path);
  }
  else{
    printf("No ELF file specified!\n");
  }
#endif
  //test_p();
  /* Start engine. */
  engine_start();

  return is_exit_status_bad();
}

void test_p(void){
    
  FILE *input_fp = fopen("./tools/gen-expr/input3", "r");

  assert(input_fp != NULL);

 
  char line[65536];
  while (fgets(line, sizeof(line), input_fp) != NULL) {
    unsigned expected_result;
    char expression[65536];

    sscanf(line, "%u %[^\n]", &expected_result, expression);

    bool success = true;
    unsigned actual_result = expr(expression, &success);


    if (success) {
      if (actual_result != expected_result) {
        printf("Error: expected %u but got %u for expression: %s\n",
               expected_result, actual_result, expression);
        return ;
      } else {
        printf("Success: %u == %s\n", actual_result, expression);
      }
    } else {
      printf("Error evaluating expression: %s\n", expression);
    }
  }

  fclose(input_fp);

}