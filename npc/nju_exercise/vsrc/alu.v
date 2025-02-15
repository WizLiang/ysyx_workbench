module adder #(parameter n = 4)(
    input signed [3:0]A,
    input signed [3:0]B,
    input c_in,
    output reg carry,
    output reg zero,
    output reg overflow,
    output reg signed [3:0]result
);
    wire [3:0] t_no_Cin;
    // always@(*)begin
    //     if(sub_or_add)begin
    //         result[3:0] = A[3:0] + ~B[3:0] + ~c_in;
    //         carry = (A < B) ? 1'b0; 1'b1;


    //     end
    //     else begin
    //         {carry , result[3:0]} = A[3:0] + B[3:0] + c_in;
    //         overflow = ((A[3]==B[3]) && (A[3]!= result[3]));
    //     end
    // end
    assign t_no_Cin = {n{ c_in }}^B;  // 将 B 逐位与 Cin 进行异或操作
    /* verilator lint_off WIDTHEXPAND */
    assign {carry, result} = A + t_no_Cin + c_in;
    /* verilator lint_on WIDTHEXPAND */
    assign overflow = (A[n-1] == t_no_Cin[n-1]) && (result [n-1] != A[n-1]);  // 溢出判断


    assign zero = ~(| result);


endmodule


module Sim_ALU(
    input signed [3:0]A,
    input signed [3:0]B,
    input [2:0]func,
    output reg signed [3:0]result,
    output reg overflow,
    output reg out,
    output reg carry,
    output reg zero
);

    //reg flag;
    wire [3:0] u_result;
/* verilator lint_off LATCH */
    always@(*)begin
        case(func)
        3'b000:begin
            //flag = 1'b0;
            result = u_result;
        end
        3'b001:begin
            //flag = 1'b1;
            result = u_result;
        end
        3'b010:begin
            result[3:0] = ~A[3:0];
            end
        3'b011:begin
            result[3:0] = A & B;
        end
        3'b100:begin
            result[3:0] = A | B;
        end
        3'b101:begin
            result[3:0] = A ^ B;
        end
        3'b110:begin
            if(A[3] == 1'b0 && B[3] == 1'b0)begin
                if(A[2:0] < B[2:0]) out = 1'b1;
                else out =1'b0;
            end
            else if(A[3] == 1'b1 && B[3] == 1'b0)begin
                out = 1'b1;
            end
            else if(A[3] == 1'b1 && B[3] == 1'b1)begin
                if(A[2:0] > B[2:0]) out = 1'b1;
                else out =1'b0;
            end
            else out = 1'b0;
        end
        3'b111:begin
            out = (A == B) ? 1'b1 : 1'b0;
        end
        endcase
/* verilator lint_off LATCH */

    end

    adder u_adder (
        .A(A),
        .B(B),
        .c_in(func[0]),
        .result(u_result),
        .zero(zero),
        .carry(carry),
        .overflow(overflow)
    );

    // assign zero = ~(| result);

endmodule

