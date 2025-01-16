#include <am.h>
#include <nemu.h>
#include <stdio.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint32_t key_data = inl(KBD_ADDR); // 读取键盘数据寄存器的值
  
  kbd->keydown = (key_data & KEYDOWN_MASK) != 0; // 判断按键是否按下
  kbd->keycode = key_data & ~KEYDOWN_MASK;      // 提取键码（去掉按下标志位）
  
}
