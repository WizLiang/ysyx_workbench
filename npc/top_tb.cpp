#include <verilated.h>
#include "Vtop.h" // Verilator 会生成这个头文件
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include "verilated_fst_c.h"  // 如果使用 VCD，则改为 verilated_vcd_c.h


int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Vtop* top = new Vtop;

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


    vluint64_t sim_time = 0;  // 定义仿真时间变量
    int sim_count = 1000;  // 设置仿真次数

    
    for (int i = 0; i < sim_count; ++i) {
        // 随机生成a和b的值
        int a = std::rand() & 1;
        int b = std::rand() & 1;
        
        // 设置输入信号
        top->a = a;
        top->b = b;
        
        // 评估模块的输出
        top->eval();

        // 记录波形数据
        tfp->dump(sim_time);
        sim_time += 1;  // 增加仿真时间
        
        // 打印输出结果
        std::cout << "a = " << a << ", b = " << b << ", f = " << (int)top->f << std::endl;
        
        // 断言确保输出结果正确
        assert(top->f == (a ^ b));
    }

    // 清理
    top->final();
    tfp->close();
    delete top;
    delete tfp;
    return 0;
}

