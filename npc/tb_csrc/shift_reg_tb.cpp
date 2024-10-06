#include <stdio.h>
#include <Vtop.h>  // 更改为你的 Verilog 顶层模块的名称
#include "verilated.h"
#include "verilated_fst_c.h"  // 包含FST波形跟踪头文件
#include <iostream>
#include <string.h>

static Vtop dut;  // 顶层模块实例化
VerilatedFstC* tfp;  // FST 波形文件指针
int clk_counter = 0;  // 用于生成 ps2_clk 的四分频

static void single_cycle() {
  dut.clk = 0;
  dut.eval();
  tfp->dump(Verilated::time());  // Dump wave
  Verilated::timeInc(1);  // 时钟周期递增

  dut.clk = 1;
  dut.eval();
  tfp->dump(Verilated::time());
  Verilated::timeInc(1);

  // 生成 ps2_clk 的四分频信号
  clk_counter++;
  if (clk_counter >= 8) {  // 每 8 个时钟周期反转一次 ps2_clk
    dut.ps2_clk = !dut.ps2_clk;
    clk_counter = 0;
  }
}

static void reset(int n) {
  dut.rst_n = 0;
  while (n-- > 0) single_cycle();
  dut.rst_n = 1;
}

static void send_ps2_frame(uint8_t data) {
  // PS/2 数据帧：起始位(0) + 8位数据 + 奇校验位 + 停止位(1)
  uint8_t parity = 1;  // 奇校验位
  for (int i = 0; i < 8; ++i) {
    parity ^= (data >> i) & 1;
  }

  // 发送起始位 (0)
  dut.ps2_data = 0;
  for (int i = 0; i < 8; ++i) {  // 八个时钟周期表示一个完整的下降沿和上升沿
    single_cycle();
  }

  // 发送8位数据 (低位在前)
  for (int i = 0; i < 8; ++i) {
    dut.ps2_data = (data >> i) & 1;
    for (int j = 0; j < 8; ++j) {
      single_cycle();
    }
  }

  // 发送奇校验位
  dut.ps2_data = parity;
  for (int i = 0; i < 8; ++i) {
    single_cycle();
  }

  // 发送停止位 (1)
  dut.ps2_data = 1;
  for (int i = 0; i < 8; ++i) {
    single_cycle();
  }
}

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);  // 传递命令行参数

  // 启用波形跟踪
  Verilated::traceEverOn(true);  // 打开波形跟踪
  tfp = new VerilatedFstC;
  dut.trace(tfp, 99);  // 开启波形跟踪，深度为 99
  tfp->open("Vtop_dump.fst");  // 创建并打开 FST 波形文件

  // 复位
  reset(10);

  // 模拟按下 W 键（扫描码 1Dh）
  send_ps2_frame(0x1D);

  // 模拟按住 W 键（重复发送扫描码 1Dh）
  for (int i = 0; i < 3; ++i) {
    send_ps2_frame(0x1D);
  }

  // 模拟松开 W 键（断码 F0h + 通码 1Dh）
  send_ps2_frame(0xF0);
  send_ps2_frame(0x1D);

  // 模拟按下左 Shift 键（扫描码 12h），然后按下 W 键，松开 W 键，再松开左 Shift 键
  send_ps2_frame(0x12);  // 左 Shift 键按下
  send_ps2_frame(0x1D);  // W 键按下
  send_ps2_frame(0xF0);  // W 键松开
  send_ps2_frame(0x1D);
  send_ps2_frame(0xF0);  // 左 Shift 键松开
  send_ps2_frame(0x12);

  tfp->close();  // 关闭波形文件
  delete tfp;
  return 0;
}