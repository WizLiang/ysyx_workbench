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

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include <memory/paddr.h>

enum {
  TK_NOTYPE = 256, TK_EQ,TK_DECIMAL,
  TK_HEX,  // For hexadecimal numbers
  TK_NEQ,   // For '!='
  TK_AND,   // For '&&'
  TK_NEG,   // For  negetive
  TK_REG,  // for register names
  TK_DEREF,  // pointer dereferencing

  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.

   '+' 的 ASCII 值是 43，'-' 是 45，'*' 是 42，'/' 是 47，括号的 ASCII 值分别为 40 和 41
   */

  {" +", TK_NOTYPE},    // spaces
  //hexadecimal first
  {"0x[0-9a-fA-F]+", TK_HEX},  // Match hexadecimal numbers starting with "0x"
  {"[0-9]+", TK_DECIMAL},     // decimal number

  {"\\$[a-zA-Z0-9$]+", TK_REG},  // Match register names starting with "$"

  
  {"\\+", '+'},               // add
  {"-", '-'},                 // minus
  {"\\*", '*'},               // multiple
  {"/", '/'},                 // divide
  {"\\(", '('},               // left branket
  {"\\)", ')'},               // right branket

  {"==", TK_EQ},              // equal
  {"!=", TK_NEQ},             // not equal
  {"&&", TK_AND},             // logical and
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

/*
 __attribute__((used)) informs the compiler not to optimize the value or fuction away
 even if it is not used.

 tokens数组用于按顺序存放已经被识别出的token信息, nr_token指示已经被识别出的token数目.
 */
//static Token tokens[32] __attribute__((used)) = {};
 Token tokens[65536] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          //only record
          //case '+': case '-' : case '*': case '/' : case '(' : case ')':
          case '+': case '/' : case '(' : case ')':
          tokens[nr_token].type = rules[i].token_type;
          nr_token++;
          break;

          case '-':
          // Check if it is a unary minus (negative) or binary subtraction
          if (nr_token == 0 || tokens[nr_token - 1].type == '(' || tokens[nr_token - 1].type == '+' ||
              tokens[nr_token - 1].type == '-'  || tokens[nr_token - 1].type == '*' ||
              tokens[nr_token - 1].type == TK_NEG || 
              tokens[nr_token - 1].type == '/'
               ) {
              tokens[nr_token].type = TK_NEG;  // a unary minus (negative)
            } 
          else {
            tokens[nr_token].type = '-';  // binary subtraction
          }
          nr_token++;
          break;

          case '*':
          if (nr_token == 0 || tokens[nr_token - 1].type == '(' ||
          tokens[nr_token - 1].type == '+' || tokens[nr_token - 1].type == '-' ||
          tokens[nr_token - 1].type == '*' || tokens[nr_token - 1].type == '/' ||
          tokens[nr_token - 1].type == TK_EQ || tokens[nr_token - 1].type == TK_NEQ ||
          tokens[nr_token - 1].type == TK_AND || tokens[nr_token - 1].type == TK_NEG) {
          tokens[nr_token].type = TK_DEREF;  
          } else {
          tokens[nr_token].type = '*';  
          }
          nr_token++;
          break;

          case TK_EQ:  // Handling == operator
          tokens[nr_token].type = TK_EQ;
          nr_token++;
          break;

          case TK_NEQ:  // Handling != operator
          tokens[nr_token].type = TK_NEQ;
          nr_token++;
          break;

          case TK_AND:  // Handling && operator
          tokens[nr_token].type = TK_AND;
          nr_token++;
          break;
          
          

          case TK_DECIMAL:
          int len;
          if(substr_len < sizeof(tokens[nr_token].str) - 1){
            len = substr_len;
          }
          else{
            len = sizeof(tokens[nr_token].str) - 1;
            printf("the number has been cut off!/n");
          }
          strncpy(tokens[nr_token].str, substr_start, len);
          tokens[nr_token].str[len] = '\0';  // Null-terminate the string
          tokens[nr_token].type = TK_DECIMAL;
          nr_token++;

          break;

          case TK_HEX:
          // Copy the hexadecimal number string to the token array
          int hex_len ;
          if(substr_len < sizeof(tokens[nr_token].str) - 1){
            hex_len = substr_len;
          }
          else{
              hex_len = sizeof(tokens[nr_token].str) - 1;
              printf("the hex number is too long!/n");
          }
          
          strncpy(tokens[nr_token].str, substr_start, hex_len);
          tokens[nr_token].str[hex_len] = '\0';  // Null-terminate the string
          tokens[nr_token].type = TK_HEX;
          nr_token++;
          break;

          case TK_REG:
          // Copy the register name string to the token array
          int reg_len;
          if(substr_len < sizeof(tokens[nr_token].str) - 1){
            reg_len = substr_len;
          }
          else {
            printf("Error reg format!\n");
            assert(0);
          }
          strncpy(tokens[nr_token].str, substr_start, reg_len);
          tokens[nr_token].str[reg_len] = '\0';  // Null-terminate the string
          tokens[nr_token].type = TK_REG;
          nr_token++;
          break;

          //ignore
          case TK_NOTYPE:
          break;

          default: TODO();
        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

// use the stack ideologic and refine it use a balance flag
bool check_parentheses(int p, int q) {
  // check the begin and the end
  if (tokens[p].type != '(' || tokens[q].type != ')') {
    return false;
  }

  int balance = 0;  // balance flag
  for (int i = p; i <= q; i++) {
    if (tokens[i].type == '(') {
      balance++;
    } else if (tokens[i].type == ')') {
      balance--;
      if (balance < 0) {
        return false;
        printf("A strange right parenthesis\n");
      }
      else if (balance == 0 && i!=q){
        printf("Pairs of parenthesese in it!\n");
        return false;
      }
    }
  }

  return (balance == 0);
}

// out of parentheses and * and +
// comparison operators have lower precedence than arithmetic
int find_main_operator(int p, int q) {
  int op = -1;
  int min_priority = 100;  
  int balance = 0; //check whether in the parentheses

  for (int i = p; i <= q; i++) {
    if (tokens[i].type == '(') {
      balance++;
    } else if (tokens[i].type == ')') {
      balance--;
    }

    if (balance == 0) {
      int priority = 0;
      if (tokens[i].type == TK_EQ || tokens[i].type == TK_NEQ) {
      priority = 1;  
      } else if (tokens[i].type == TK_AND) {
      priority = 0;  // logical AND has the lowest precedence
      } 
      else if (tokens[i].type == '+' ||
        //the minus sign should be ensure as a binary operator.
       (tokens[i].type == '-' && i > p && tokens[i - 1].type != '(')) {
        priority = 2; 
      } else if (tokens[i].type == '*' || tokens[i].type == '/') {
        priority = 3;  
      } else if (tokens[i].type == TK_NEG || tokens[i].type == TK_DEREF) {
        priority = 4; 
      }

      if (priority > 0 && priority <= min_priority) {//use <=   83*495   + 57  - 509 + 140   40773 40
        min_priority = priority;
        op = i;
      }
    }
  }

  // if (op == -1) {
  //   // minus 
  //   for (int i = p; i <= q; i++) {
  //     if (tokens[i].type == '-' && (i == p || tokens[i - 1].type == '(')) {

  //       return i;
  //     }
  //   }
  // }

  assert(op != -1);  // 确保在表达式中找到运算符
  return op;
}


// use the frame code
//use sword_t instead 
sword_t eval(int p, int q) {
  if (p > q) {
    
    printf("Bad expression!\n");
    assert(0);
  }
    else if (tokens[p].type == TK_REG) {
    //read reg
    bool success = false;
    word_t reg_val = isa_reg_str2val(tokens[p].str, &success);
    if (!success) {
      printf("Failed to get the value of register %s\n", tokens[p].str);
      assert(0);
    }
    return reg_val;
    }
  else if (tokens[p].type == TK_NEG) {
    //negetive
    return -eval(p + 1, q);
  }
  else if (tokens[p].type == TK_DEREF) {
    // dereferencing
    word_t addr = eval(p + 1, q);  // Evaluate the address after '*'
    word_t value = paddr_read(addr, sizeof(word_t));  // Read the value from memory
    return value;
  }
  else if (p == q) {
    /* Single token.
     * For now this token should be a number.
     * Return the value of the number.
     */
    if (tokens[p].type == TK_DECIMAL) {
      return strtoul(tokens[p].str, NULL, 10);
      //return strtol(tokens[p].str, NULL, 10);
    } 
    else if (tokens[p].type == TK_HEX) {
    // Convert the hexadecimal string to an unsigned integer
    return strtoul(tokens[p].str, NULL, 16);
    }
    else {
      printf("Invalid token type!\n");
      assert(0);
    }
  }
  else if (check_parentheses(p, q)) {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */
    return eval(p + 1, q - 1);
  }

  else {
    //find the main operator and caculate
    int op = find_main_operator(p, q);  
    printf(" position %d , operation %c \n",op,tokens[op].type);

    // should not split the equation --1 ->result -1 
    // if (tokens[op].type == TK_NEG) {
    //   //if (op == p) {
    //     //ignore the --1
    //     return -eval(op + 1, q);
    //   //}
    // }
    sword_t val1 = eval(p, op - 1);
    sword_t val2 = eval(op + 1, q);
    
    //printf(" %u %c %u\n", val1, tokens[op].type, val2);
    switch (tokens[op].type) {
      case '+': return val1 + val2;
      case '-': return val1 - val2;
      case '*': return val1 * val2;
      case '/': return val1 / val2;
      case TK_EQ: return val1 == val2;
      case TK_NEQ: return val1 != val2;
      case TK_AND: return val1 && val2;
      default: 
        printf("Unknown operator!\n");
        assert(0);
    }
    
  }

  return 0;
}

sword_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  *success = true;
  /* TODO: Implement expression evaluation */
  return eval(0, nr_token - 1);  
}




