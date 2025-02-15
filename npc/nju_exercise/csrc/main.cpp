#include <stdio.h>
#include <nvboard.h>
#include <Vtop.h>
// #include <Vmux41_2bit.h>

#include "verilated.h"
#include "verilated_fst_c.h"  // 包含FST波形跟踪头文件
#include <iostream>
#include <string.h>


static TOP_NAME dut;
VerilatedFstC* tfp;  // FST 波形文件指针

void nvboard_bind_all_pins(TOP_NAME* top);

static void single_cycle() {
  dut.clk = 0; dut.eval();

  // tfp->dump(Verilated::time());  // Dump wave
  // Verilated::timeInc(1);  // 时钟周期递增


  dut.clk = 1; dut.eval();

  // tfp->dump(Verilated::time());
  // Verilated::timeInc(1);
}

static void reset(int n) {
  dut.rst_n = 0;
  while (n -- > 0) single_cycle();
  dut.rst_n = 1;
}

int main() {
// int main(int argc, char** argv) {
//   Verilated::commandArgs(argc, argv);  // 传递命令行参数
//   bool trace_enable = false;

//   // 检查是否传入 "+trace" 参数
//     for (int i = 1; i < argc; i++) {
//         if (!strcmp(argv[i], "+trace")) {
//             trace_enable = true;
//             break;
//         }
//     }
//     // 如果启用了 trace 功能，初始化波形生成
//     if (trace_enable) {
//         Verilated::traceEverOn(true);  // 打开波形跟踪
//         tfp = new VerilatedFstC;
//         dut.trace(tfp, 99);  // 开启波形跟踪，深度为 99
//         tfp->open("dump.fst");  // 创建并打开 FST 波形文件
//     }


  nvboard_bind_all_pins(&dut);
  nvboard_init();

  reset(10);

  while(1) {
    nvboard_update();
    single_cycle();
  }

    // // 如果开启了波形跟踪，关闭波形文件
    // if (trace_enable) {
    //     tfp->close();
    //     delete tfp;
    // }

  nvboard_quit();
  return 0;
}
