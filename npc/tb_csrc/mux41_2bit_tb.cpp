#include <verilated.h>
#include "Vmux41_2bit.h" // Verilator 会生成这个头文件
// #define HEADER_FILE "Vmux41_2bit.h"
// #include HEADER_FILE


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include "verilated_fst_c.h"  // 如果使用 VCD，则改为 verilated_vcd_c.h


int main(int argc, char **argv) {
    // printf("TOP_NAME: %s\n", TOP_NAME );
    Verilated::commandArgs(argc, argv);
    Vmux41_2bit* top = new Vmux41_2bit;

    // 初始化随机数生成器
    std::srand(std::time(0));


    // 启用 Verilator 的波形追踪功能
    Verilated::traceEverOn(true);

    // 创建波形追踪对象
    VerilatedFstC* tfp = new VerilatedFstC;

    // 与顶层模块关联，指定追踪层级（99 表示所有层级）
    top->trace(tfp, 99);

    // 打开波形文件
    tfp->open("waveform.fst");


    int sim_time = 0;  // 定义仿真时间变量
    int sim_count = 1024;  // 设置仿真次数

    
    for (int i = 0; i < sim_count; ++i) {
         // 提取输入信号
        top->X0 = (i >> 0) & 0x3;  // 提取第 0-1 位
        top->X1 = (i >> 2) & 0x3;  // 提取第 2-3 位
        top->X2 = (i >> 4) & 0x3;  // 提取第 4-5 位
        top->X3 = (i >> 6) & 0x3;  // 提取第 6-7 位
        top->Y  = (i >> 8) & 0x3;  // 提取第 8-9 位

        // 评估模型
        top->eval();
           // 将当前时刻的波形数据写入文件
        tfp->dump(sim_time);

        sim_time +=1;

 
    }

    // 清理
    top->final();
    tfp->close();
    delete top;
    delete tfp;
    return 0;
}
