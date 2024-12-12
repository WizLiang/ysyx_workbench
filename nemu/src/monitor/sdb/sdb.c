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
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include <memory/paddr.h>

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}
void parse_elf_file();
void test_find_function_by_pc();
void ftrace_on();

static int cmd_e(char *args){
  ftrace_on();
  parse_elf_file(args);
  return 0;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}

//bool exit_flag = 0;  
extern NEMUState nemu_state;

static int cmd_q(char *args) {
  //return -1;
  /*  (nemu) q
make: *** [/home/wizard/ysyx-workbench/nemu/scripts/native.mk:38: run] Error 1
*/
  //exit_flag = 1;
  nemu_state.state = NEMU_QUIT;
  return 0;
  //exit(0);
}

//watchpoint
static int cmd_w(char *args) {
  if (args == NULL) {
    printf("Usage: w EXPR\n");
    return 0;
  }

  new_wp(args);

  return 0;
}

static int cmd_d(char *args) {
  if (args == NULL) {
    printf("Usage: d N\n");
    return 0;
  }

  int n = atoi(args);  // 将字符串转换为整数
  free_wp(n);          // 调用free_wp函数删除监视点

  return 0;
}



static int cmd_help(char *args);

static int cmd_si(char *args){
  uint64_t n =1;
  if(args != NULL){
    n = strtoull(args, NULL, 10); // unsigned long long int
  }
  if(n < 1)printf("invalid input!");
  cpu_exec(n);
  return 0;
};

static int cmd_info(char *args){
  //illegal input check
  if (args == NULL) {
    printf("Usage: info r or info w \n");
    return 0;
  }
  if(!strcmp(args,"r")){isa_reg_display();}
  if (!strcmp(args, "w"))
  {
    //printf("Sorry! I haven't implemented this function so far.\n");
    int active_wp_count = print_all_wp();
    printf("Total active watchpoints: %d\n", active_wp_count);
  }
  return 0;
};

static int cmd_x(char *args){
  char *n_str;
  char *expr_str;

  //use strtok flatten the args
  n_str = strtok(args," ");
  expr_str = strtok(NULL," ");

  //illegal input check
  if (n_str == NULL || expr_str == NULL) {
    printf("Usage: x N EXPR\n");
    return 0;
  }
  // char to int
  int N = strtol(n_str, NULL, 10);//long int -- strtol while unsigned long int --strtoul
  if (N <= 0) {
    printf("Invalid number of words: %s\n", n_str);
    return 0;
  }  
  // EXPR (expression) to a starting memory address.
  // For now, we assume EXPR is a simple hexadecimal number.
  paddr_t addr = strtoull(expr_str, NULL, 16);

  // Loop through N 4-byte words and print them in hexadecimal.
  for (int i = 0; i < N; i++) {
    word_t data = paddr_read(addr + i * 4, 4);  // Read 4 bytes (1 word) from memory.
    printf("0x%08x: 0x%08x\n", addr + i * 4, data);
  }

  return 0;
}

static int cmd_p(char *args) {
  if (args == NULL) {
    printf("Usage: p EXPR\n");
    return 0;
  }

  bool success = true;
  word_t result = expr(args, &success);

  if (success) {
    printf("%u  in Hex:%x\n", result,result);
  } else {
    printf("Invalid expression!\n");
  }

  return 0;
}
//test function
static int cmd_t(char *args){
  // uint32_t test_pc = 0x80000010; // test pc
  // test_find_function_by_pc(test_pc);
  printf("Nothing to test!\n");
  return 0;
}


static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  
  /* TODO: Add more commands */
  { "si", "Step through N instructions, default is 1 if not specified", cmd_si},
  { "info", "Print the register state or monitor information", cmd_info},
  { "x", "Scan memory: x N EXPR", cmd_x },//note : this function haven't fully implemented yet.
  { "p", "Evaluate the expression EXPR and display the result", cmd_p },
  { "w", "Set a watchpoint with expression EXPR", cmd_w },  
  { "d", "Delete the watchpoint with number N", cmd_d },   
  { "e", "ELF file reading", cmd_e },
  { "t", "Test", cmd_t },      
};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }
    
    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
    //if (exit_flag ) {exit(0);}
    if (nemu_state.state == NEMU_QUIT) {  // 检查退出标志和全局状态
      break;
    }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
