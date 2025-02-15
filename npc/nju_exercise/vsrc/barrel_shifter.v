module BarrelShifter (
    input [7:0] din,        // 输入数据
    input [2:0] shamt,      // 移位位数
    input L_R,              // 左/右移
    input A_L,              // 算术/逻辑移位
    output reg [7:0] dout   // 输出数据
);
    reg [7:0] temp1, temp2, temp3;  // 中间寄存器

    always @(*) begin
        // 第一级：根据 shamt[0] 控制 1 位移位
        if (shamt[0]) begin
            if (L_R)  // 左移
                temp1 = din << 1;
            else      // 右移
                if (A_L)  // 算术右移
                    temp1 = { din[7], din[7:1] };  // 符号扩展
                else    // 逻辑右移
                    temp1 = din >> 1;
        end 
        else begin
            temp1 = din;  // 如果不移位，保持原值
        end

        // 第二级：根据 shamt[1] 控制 2 位移位
        if (shamt[1]) begin
            if (L_R)  // 左移
                temp2 = temp1 << 2;
            else      // 右移
                if (A_L)  // 算术右移
                    temp2 = { {2{temp1[7]}}, temp1[7:2] };  // 符号扩展
                else    // 逻辑右移
                    temp2 = temp1 >> 2;
        end 
        else begin
            temp2 = temp1;  // 如果不移位，保持原值
        end

        // 第三级：根据 shamt[2] 控制 4 位移位
        if (shamt[2]) begin
            if (L_R)  // 左移
                temp3 = temp2 << 4;
            else      // 右移
                if (A_L)  // 算术右移
                    temp3 = { {4{temp2[7]}}, temp2[7:4] };  // 符号扩展
                else    // 逻辑右移
                    temp3 = temp2 >> 4;
        end 
        else begin
            temp3 = temp2;  // 如果不移位，保持原值
        end

        // 最终输出
        dout = temp3;
    end
endmodule
