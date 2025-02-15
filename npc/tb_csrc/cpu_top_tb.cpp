#include <stdio.h>

#include "Vcpu_top.h"  // 由Verilator生成的头文件
#include "memory.h"  // 我们的Memory类


#include <iostream>
#include <fstream>
#include <vector>

class Memory {
public:
    // 存储器的大小，可以根据需要调整
    std::vector<uint32_t> memory;

    // 构造函数，初始化存储器
    Memory(size_t size) : memory(size, 0) {}

    // 从存储器读取指令
    uint32_t read(uint32_t address) {
        if (address < memory.size()) {
            return memory[address / 4];  // 假设每条指令占4字节
        } else {
            std::cerr << "Address out of bounds!" << std::endl;
            return 0;
        }
    }

    // 用于加载一个程序到存储器中（可以模拟加载程序）
    void load_program(const std::vector<uint32_t>& program, uint32_t start_address) {
        for (size_t i = 0; i < program.size(); ++i) {
            memory[(start_address / 4) + i] = program[i];
        }
    }
};
// 创建一个存储器实例
Memory memory(1024); // 假设存储器大小为1024个32位字

// 通过Verilator的接口读取指令
void fetch_instruction(Vcpu_top* top) {
    uint32_t pc = top->pc;  // 获取当前的PC值
    uint32_t instruction = memory.read(pc);  // 从存储器读取指令
    top->inst = instruction;  // 将指令传递给Verilator的top模块
}

int main(int argc, char** argv) {
    // 创建Verilator模型实例
    Vcpu_top* top = new Vcpu_top;

    // 加载程序到存储器
    std::vector<uint32_t> program = {0x00000093, 0x00100093}; // 示例程序
    memory.load_program(program, 0x80000000); // 假设程序从0x80000000开始加载

    // 模拟仿真
    while (!Verilated::gotFinish()) {
        fetch_instruction(top);  // 获取指令
        top->eval();  // 执行仿真周期
    }

    delete top;
    return 0;
}
