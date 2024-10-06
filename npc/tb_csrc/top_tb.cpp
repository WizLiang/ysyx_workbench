#include <stdio.h>
#include <Vtop.h>  // 更改为你的 Verilog 顶层模块的名称
#include "verilated.h"
#include "verilated_fst_c.h"  // 包含FST波形跟踪头文件
#include <iostream>
#include <string.h>

static Vtop dut;  // 顶层模块实例化
VerilatedFstC* tfp;  // FST 波形文件指针

static void single_cycle() {
  dut.clk = 0;
  dut.eval();
  tfp->dump(Verilated::time());  // Dump wave
  Verilated::timeInc(1);  // 时钟周期递增

  dut.clk = 1;
  dut.eval();
  tfp->dump(Verilated::time());
  Verilated::timeInc(1);
}

static void reset(int n) {
  dut.rst_n = 0;
  while (n-- > 0) single_cycle();
  dut.rst_n = 1;
  single_cycle();
}

static void send_ps2_frame(uint8_t code) {
  // PS/2 数据帧：起始位(0) + 8位数据 + 奇校验位 + 停止位(1)
  uint8_t parity = 1;  // 奇校验位
  for (int i = 0; i < 8; ++i) {
    parity ^= (code >> i) & 1;
  }

  uint16_t frame = (1 << 10) | (parity << 9) | (code << 1) | 0;  // 生成11位数据帧

  // 逐位发送帧数据
  for (int i = 0; i < 11; ++i) {
    dut.ps2_data = (frame >> i) & 1;
    // 模拟 PS/2 时钟信号（每位持续多个时钟周期，模拟 60ns 时钟周期）
    for (int j = 0; j < 4; ++j) {
      dut.ps2_clk = (j < 2) ? 0 : 1;  // 模拟下降沿和上升沿
      single_cycle();
    }
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


  for (int j = 0; j < 4; ++j) {
    dut.ps2_clk = (j < 2) ? 0 : 1;  // 模拟下降沿和上升沿
    single_cycle();
  }
  // 模拟按下 'A' 键（扫描码 1Ch）
  send_ps2_frame(0x1C);
  single_cycle();
  //dut.nextdata_n = 0;
  single_cycle();
  //dut.nextdata_n = 1;
  single_cycle();

  // 模拟断码 F0h，表示释放 'A' 键
  send_ps2_frame(0xF0);
  single_cycle();
  //dut.nextdata_n = 0;
  single_cycle();
  //dut.nextdata_n = 1;
  single_cycle();

  // 发送 'A' 键的释放扫描码
  send_ps2_frame(0x1C);
  single_cycle();
  //dut.nextdata_n = 0;
  single_cycle();
  //dut.nextdata_n = 1;
  single_cycle();

  // 模拟按下 'S' 键（扫描码 1Bh）
  send_ps2_frame(0x1B);
  single_cycle();
  send_ps2_frame(0x1B);  // 持续按下 'S'
  single_cycle();
  send_ps2_frame(0x1B);  // 持续按下 'S'
  single_cycle();

  // 模拟释放 'S' 键（断码 F0h + 通码 1Bh）
  send_ps2_frame(0xF0);
  send_ps2_frame(0x1B);
  single_cycle();

  tfp->close();  // 关闭波形文件
  delete tfp;
  return 0;
}