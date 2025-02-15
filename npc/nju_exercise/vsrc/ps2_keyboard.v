module ps2_keyboard(clk,clrn,ps2_clk,ps2_data,data,
                    ready,nextdata_n,overflow);
    input clk,clrn,ps2_clk,ps2_data;
    input nextdata_n;
    output [7:0] data;
    output reg ready;       //fifo is not empty
    output reg overflow;     // fifo overflow

    // internal signal, for test
    reg [9:0] buffer;        // ps2_data bits ignoring the end bit
    reg [7:0] fifo[7:0];     // data fifo
    reg [2:0] w_ptr,r_ptr;   // fifo write and read pointers
    reg [3:0] count;  // count ps2_data bits
    // detect falling edge of ps2_clk
    reg [2:0] ps2_clk_sync;

    always @(posedge clk) begin
        ps2_clk_sync <=  {ps2_clk_sync[1:0],ps2_clk};
    end

    wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1];

    always @(posedge clk) begin
        if (clrn == 0) begin // reset
            count <= 0; w_ptr <= 0; r_ptr <= 0; overflow <= 0; ready<= 0;
        end
        else begin
            if ( ready ) begin // read to output next data
                if(nextdata_n == 1'b0) //read next data
                begin
                    r_ptr <= r_ptr + 3'b1;
                    if(w_ptr==(r_ptr+1'b1)) //empty
                        ready <= 1'b0;
                end
            end 
            if (sampling) begin
                if (count == 4'd10) begin
                    if ((buffer[0] == 0) &&  // start bit
                        (ps2_data)       &&  // stop bit
                        (^buffer[9:1])) begin      // odd  parity
                            fifo[w_ptr] <= buffer[8:1];  // kbd scan code
                            w_ptr <= w_ptr+3'b1;
                            ready <= 1'b1;
                            overflow <= overflow | (r_ptr == (w_ptr + 3'b1));
                        end
                    count <= 0;     // for next
                    //$display("receive %x", buffer[8:1]);
                end 
              else begin
                buffer[count] <= ps2_data;  // store ps2_data
                count <= count + 3'b1;
              end
            end
        end
    end
    assign data = fifo[r_ptr]; //always set output data

endmodule


module scancode2ascii(
    input [7:0] scancode, // 8位输入，表示键盘的扫描码
    output reg [7:0] ascii // 8位输出，表示对应的ASCII码
);

    always @(*) begin
        case (scancode)
            8'h1C: ascii = 8'h61; // 'A' 键 -> ASCII 'a'
            8'h32: ascii = 8'h62; // 'B' 键 -> ASCII 'b'
            8'h21: ascii = 8'h63; // 'C' 键 -> ASCII 'c'
            8'h23: ascii = 8'h64; // 'D' 键 -> ASCII 'd'
            8'h24: ascii = 8'h65; // 'E' 键 -> ASCII 'e'
            8'h2B: ascii = 8'h66; // 'F' 键 -> ASCII 'f'
            8'h34: ascii = 8'h67; // 'G' 键 -> ASCII 'g'
            8'h33: ascii = 8'h68; // 'H' 键 -> ASCII 'h'
            8'h43: ascii = 8'h69; // 'I' 键 -> ASCII 'i'
            8'h3B: ascii = 8'h6A; // 'J' 键 -> ASCII 'j'
            8'h42: ascii = 8'h6B; // 'K' 键 -> ASCII 'k'
            8'h4B: ascii = 8'h6C; // 'L' 键 -> ASCII 'l'
            8'h3A: ascii = 8'h6D; // 'M' 键 -> ASCII 'm'
            8'h31: ascii = 8'h6E; // 'N' 键 -> ASCII 'n'
            8'h44: ascii = 8'h6F; // 'O' 键 -> ASCII 'o'
            8'h4D: ascii = 8'h70; // 'P' 键 -> ASCII 'p'
            8'h15: ascii = 8'h71; // 'Q' 键 -> ASCII 'q'
            8'h2D: ascii = 8'h72; // 'R' 键 -> ASCII 'r'
            8'h1B: ascii = 8'h73; // 'S' 键 -> ASCII 's'
            8'h2C: ascii = 8'h74; // 'T' 键 -> ASCII 't'
            8'h3C: ascii = 8'h75; // 'U' 键 -> ASCII 'u'
            8'h2A: ascii = 8'h76; // 'V' 键 -> ASCII 'v'
            8'h1D: ascii = 8'h77; // 'W' 键 -> ASCII 'w'
            8'h22: ascii = 8'h78; // 'X' 键 -> ASCII 'x'
            8'h35: ascii = 8'h79; // 'Y' 键 -> ASCII 'y'
            8'h1A: ascii = 8'h7A; // 'Z' 键 -> ASCII 'z'

            8'h16: ascii = 8'h31; // '1' 键 -> ASCII '1'
            8'h1E: ascii = 8'h32; // '2' 键 -> ASCII '2'
            8'h26: ascii = 8'h33; // '3' 键 -> ASCII '3'
            8'h25: ascii = 8'h34; // '4' 键 -> ASCII '4'
            8'h2E: ascii = 8'h35; // '5' 键 -> ASCII '5'
            8'h36: ascii = 8'h36; // '6' 键 -> ASCII '6'
            8'h3D: ascii = 8'h37; // '7' 键 -> ASCII '7'
            8'h3E: ascii = 8'h38; // '8' 键 -> ASCII '8'
            8'h46: ascii = 8'h39; // '9' 键 -> ASCII '9'
            8'h45: ascii = 8'h30; // '0' 键 -> ASCII '0'

            8'h29: ascii = 8'h20; // 'SPACE' 键 -> ASCII 空格符
            8'h0D: ascii = 8'h09; // 'TAB' 键 -> ASCII TAB

            // 其他按键可以根据需求补充

            default: ascii = 8'h00; // 默认值
        endcase
    end
endmodule


module keyboard_processor(
    input clk,
    input clrn,
    input ready,
    input [7:0] data,
    output reg nextdata_n,
    output reg [7:0] last_key,
    output reg key_valid,
    output reg key_pressed,
    output reg [7:0] key_count
);
    
    // 状态寄存器，用于保存键盘的上一个按键值
    reg [7:0] key_buffer;
    reg read_state;
    //reg key_pressed;

    // 初始化处理模块的状态
    always @(posedge clk or negedge clrn) begin
        if (!clrn) begin
            nextdata_n <= 1'b1;
            key_buffer <= 8'b0;
            last_key <= 8'b0;
            key_valid <= 1'b0;
            read_state <= 1'b0;
            key_count <= 8'b0;
            key_pressed <= 1'b0;
        end else begin
            if (ready && !read_state) begin
                // ready信号有效且未读取过数据
                key_buffer <= data; // 保存当前的键值
                nextdata_n <= 1'b0; // 准备读取下一个数据
                read_state <= 1'b1; // 标记已经读取
            end else if (read_state) begin
                // 完成数据读取后的处理
                nextdata_n <= 1'b1; // 恢复nextdata_n为高电平
                last_key <= key_buffer; // 输出读取到的键值
                key_valid <= 1'b1; // 标记键值有效
                read_state <= 1'b0; // 准备读取下一次数据

                if(last_key == 8'hF0)begin
                    key_pressed <= 1'b0;
                end
                else key_pressed <= 1'b1;

                // 检测按键事件
                if (key_buffer == 8'hF0) begin
                    //key_pressed <= 1'b0; // 断码表示按键释放
                    key_count <= key_count + 1'b1; // 增加按键计数
                end else begin
                    //key_pressed <= 1'b1; // 通码表示按键按下
                    //key_count <= key_count + 1'b1; // 增加按键计数
                end
            end else begin
                // 没有新的数据可以读取时保持
                key_valid <= 1'b0;
            end
        end
    end

endmodule