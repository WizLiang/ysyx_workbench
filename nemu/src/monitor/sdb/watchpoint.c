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

#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  char expression[128]; // expression 
  sword_t last_value; 

} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);

    wp_pool[i].expression[0] = '\0';  
    wp_pool[i].last_value = 0;        
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */


/*
add new watchpoint (from free to head)\
return the poiner of the watchpoint
*/

void new_wp(const char *EXPR) {
  // full
  assert(free_ != NULL);

  WP *wp = free_;
  free_ = free_->next;

  wp->next = head;
  head = wp;

  strncpy(wp->expression, EXPR, sizeof(wp->expression)); // 设置监视点表达式
  wp->expression[sizeof(wp->expression) - 1] = '\0'; // 确保字符串结尾
  bool success = false;
  wp->last_value = expr(wp->expression, &success); // 初次求值
  printf("Watchpoint %d: %s %d\n", wp->NO, wp->expression ,wp->last_value);
  assert(success);

  //return wp;
}

/*
Delete an activate watchpoint version 1
*/
// void free_wp(WP *wp){
//   //input check preliminary
//   assert(wp != NULL);

//   //WP *cur= NULL;
//   // WP *prev = NULL;
//   WP **curr = &head;  // curr 是指向 head 的指针，即保存了 head 的地址

//   while (*curr != NULL && *curr != wp) {
//     curr = &((*curr)->next);  // curr 保存的是当前节点的 next 指针的地址
//   }

//   // 找到要删除的节点后，修改 next 指针
//   if (*curr == wp) {
//     *curr = wp->next;  // 直接修改前一个节点的 next 指针，跳过当前节点

//     // 重置 expression 和 last_value
//     wp->expression[0] = '\0';  // 清空表达式
//     wp->last_value = 0;        // 重置上一次的值
//   }

//   wp->next = free_;
//   free_ = wp;


// }

void free_wp(int NO) {
  
  if (head == NULL) {
    printf("No active watchpoints to delete.\n");
    return;
  }

  WP **curr = &head;  // 指向head的指针，用来遍历链表

  // 遍历链表，查找NO匹配的监视点
  while (*curr != NULL) {
    if ((*curr)->NO == NO) {
      WP *wp_to_free = *curr;  // 找到要删除的监视点
      *curr = wp_to_free->next;  // 重新连接链表，跳过该监视点

      // 重置 expression 和 last_value，放回free_链表
      wp_to_free->expression[0] = '\0';
      wp_to_free->last_value = 0;
      wp_to_free->next = free_;
      free_ = wp_to_free;

      printf("Watchpoint %d deleted.\n", NO);
      return;
    }
    else curr = &((*curr)->next);  // 继续下一个监视点
  }

  // 如果没有找到匹配的NO，输出提示信息
  printf("Watchpoint %d not found.\n", NO);
}

// void check_watchpoints() {
//   WP *wp = head;
//   bool success = false;
//   while (wp != NULL) {
//     uint64_t new_value = expr(wp->expression, &success); 
//     if (!success) {
//       printf("Failed to evaluate watchpoint expression: %s\n", wp->expression);
//       wp = wp->next;
//       continue;
//     }
//     if (new_value != wp->last_value) {
//       printf("Watchpoint %d triggered: %s\n", wp->NO, wp->expression);
//       printf("Old value = " FMT_WORD ", New value = " FMT_WORD "\n", wp->last_value, new_value);
//       wp->last_value = new_value; 
//       nemu_state.state = NEMU_STOP; 
//     }
//     wp = wp->next;
//   }
// }

void check_watchpoints() {
  WP *wp = head;
  bool success = false;
  bool triggered = false; //mark the wps change
  while (wp != NULL) {
    sword_t new_value = expr(wp->expression, &success); 
    if (!success) {
      printf("Failed to evaluate watchpoint expression: %s\n", wp->expression);
      wp = wp->next;
      continue;
    }
    if (new_value != wp->last_value) {
      printf("Watchpoint %d triggered: %s\n", wp->NO, wp->expression);
      printf("Old value = %x , New value = %x \n", wp->last_value, new_value);
      wp->last_value = new_value; //updata value
      triggered = true; 
    }
    wp = wp->next;
  }
  if (triggered) {
    nemu_state.state = NEMU_STOP; // stop execute
  }
}

// return the active wp amount
int print_all_wp() {
  WP *wp = head;  
  int count = 0;  
  
  if (wp == NULL) {
    printf("No active watchpoints.\n");  
    return 0;
  }

  printf("Active watchpoints:\n");
  printf("NO    Expression  (Last) Value\n");
  printf("----  ----------  ----------\n");

  while (wp != NULL) {
    printf("%-4d  %-10s  %08u\n", wp->NO, wp->expression, wp->last_value);
    wp = wp->next;
    count++;  
  }

  return count;
}