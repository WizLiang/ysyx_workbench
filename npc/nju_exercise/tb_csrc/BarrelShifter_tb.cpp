#include <stdio.h>
#include <VBarrelShifter.h>  // 更改为你的 Verilog 模块的名称
#include "verilated.h"
#include "verilated_fst_c.h"  // 包含FST波形跟踪头文件
#include <iostream>

// 实例化 Verilog 模块
static VBarrelShifter dut;  // 更改为你的 Verilog 模块名称
VerilatedFstC* tfp;          // FST 波形文件指针

// 测试组合逻辑：设置输入，观察输出
static void apply_input() {
    dut.eval();  // 直接评估组合逻辑输出
    tfp->dump(Verilated::time());  // Dump wave
    Verilated::timeInc(1);         // 模拟时间推进
}

// 测试桶形移位器
int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);  // 传递命令行参数

    // 启用波形跟踪
    Verilated::traceEverOn(true);  // 打开波形跟踪
    tfp = new VerilatedFstC;
    dut.trace(tfp, 99);  // 开启波形跟踪，深度为 99
    tfp->open("Vbarrel_shifter_dump.fst");  // 创建并打开 FST 波形文件

    // 设置输入信号，并进行仿真
    dut.din = 0xAA;  // 输入数据 0xAA（10101010）
    
    // 基本测试：右移 3 位，逻辑右移
    dut.shamt = 3;  // 右移 3 位
    dut.L_R = 0;    // 0 表示右移
    dut.A_L = 0;    // 0 表示逻辑右移
    apply_input();  // 直接评估组合逻辑
    std::cout << "Right Logical Shift by 3: " << std::hex << (int)dut.dout << std::endl;

    // 左移 2 位
    dut.shamt = 2;  // 左移 2 位
    dut.L_R = 1;    // 1 表示左移
    apply_input();
    std::cout << "Left Logical Shift by 2: " << std::hex << (int)dut.dout << std::endl;

    // 算术右移 1 位
    dut.shamt = 1;  // 右移 1 位
    dut.L_R = 0;    // 0 表示右移
    dut.A_L = 1;    // 1 表示算术右移
    apply_input();
    std::cout << "Arithmetic Right Shift by 1: " << std::hex << (int)dut.dout << std::endl;

    // 逻辑左移 1 位
    dut.shamt = 1;  // 左移 1 位
    dut.L_R = 1;    // 1 表示左移
    dut.A_L = 0;    // 0 表示逻辑左移
    apply_input();
    std::cout << "Left Logical Shift by 1: " << std::hex << (int)dut.dout << std::endl;

    // 完成所有测试后，关闭波形文件
    tfp->close();
    delete tfp;
    return 0;
}
