// module top(
//   input clk,
//   input rst,
//   input [7:0] data_in,
//   output reg [7:0] seg0,
//   output [15:0]led
// );

// // light u_light(
// //     .clk(clk),
// //     .rst(rst),
// //     .led(led)
// // );
// wire [2:0] u_digit;
// encoder_83 u_encoder_83(
//   .in(data_in),
//   .out(u_digit[2:0]),
//   .valid(led[0])
// );

// seven_seg_decoder u_seven_seg_decoder(
//   .digit({1'b0,u_digit}),
//   .segments(seg0[7:1])
// );

// assign seg0[0] = 1'b0;

// //assign seg0[7:0] = 8'b00000010;

module ps_keyboard(clk,resetn,ps2_clk,ps2_data);
    input clk,resetn,ps2_clk,ps2_data;

    reg [9:0] buffer;        // ps2_data bits
    reg [3:0] count;  // count ps2_data bits
    reg [2:0] ps2_clk_sync;

    always @(posedge clk) begin
        ps2_clk_sync <=  {ps2_clk_sync[1:0],ps2_clk};
    end

    wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1];

    always @(posedge clk) begin
        if (resetn == 0) begin // reset
            count <= 0;
        end
        else begin
            if (sampling) begin
              if (count == 4'd10) begin
                if ((buffer[0] == 0) &&  // start bit
                    (ps2_data)       &&  // stop bit
                    (^buffer[9:1])) begin      // odd  parity
                    $display("receive %x", buffer[8:1]);
                end
                count <= 0;     // for next
              end else begin
                buffer[count] <= ps2_data;  // store ps2_data
                count <= count + 3'b1;
              end
            end
        end
    end

endmodule

module top(
  input clk,
  input rst_n,
  input [7:0] data_in,
  //input [2:0] func,
  input ps2_clk,
  input ps2_data,


  output reg [7:0] seg5,
  output reg [7:0] seg4,
  output reg [7:0] seg3,
  output reg [7:0] seg2,
  output reg [7:0] seg1,
  output reg [7:0] seg0,
  output [15:0]led
);


  // ps_keyboard u_ps2_keyboard(
  //   .clk(clk),
  //   .resetn(rst_n),
  //   .ps2_clk(ps2_clk),
  //   .ps2_data(ps2_data)
   
  // );

  wire ready;
  wire [7:0] data;
  wire nextdata_n;
  wire [7:0] last_key;
  wire key_valid;
  wire key_pressed;
  wire [7:0] key_count;
  keyboard_processor u_keyboard_processor(
    .clk(clk),
    .clrn(rst_n),
    .ready(ready),
    .data(data),
    .nextdata_n(nextdata_n),
    .last_key(last_key),
    .key_valid(key_valid),
    .key_pressed(key_pressed),
    .key_count(key_count)
  );

  wire [7:0] ascii;
  scancode2ascii u_scancode2ascii(
    .scancode(last_key),
    .ascii(ascii)
  );
wire overflow;
  ps2_keyboard u_ps2_keyboard(
    .clk(clk),
    .clrn(rst_n),
    .ps2_clk(ps2_clk),
    .ps2_data(ps2_data),
    .data(data),
    .nextdata_n(nextdata_n),
    .ready(ready),
    .overflow(overflow)
  );

//led
assign led[0] = key_valid;
assign led[1] = ready;
assign led[2] = nextdata_n;

assign led[3] = data_in[3];
assign led[4] = ps2_data;
assign led[5] = overflow;
 


//display
seven_seg_decoder u_seven_seg_decoder5(
  .digit(key_count[7:4]),
  .enable(1'b1),
  .segments(seg5[7:1])
);

assign seg5[0] = 1'b1;

seven_seg_decoder u_seven_seg_decoder4(
  .digit(key_count[3:0]),
  .enable(1'b1),
  .segments(seg4[7:1])
);

assign seg4[0] = 1'b1;



seven_seg_decoder u_seven_seg_decoder3(
  .digit(ascii[7:4]),
  .enable(key_pressed),
  .segments(seg3[7:1])
);

assign seg3[0] = 1'b1;


seven_seg_decoder u_seven_seg_decoder2(
  .digit(ascii[3:0]),
  .enable(key_pressed),
  .segments(seg2[7:1])
);

assign seg2[0] = 1'b1;


seven_seg_decoder u_seven_seg_decoder1(
  .digit(last_key[7:4]),
  .enable(key_pressed),
  .segments(seg1[7:1])
);

assign seg1[0] = 1'b1;




seven_seg_decoder u_seven_seg_decoder0(
  .digit(last_key[3:0]),
  .enable(key_pressed),
  .segments(seg0[7:1])
);

assign seg0[0] = 1'b1;





// //exercise six
  // input clk,
  // input rst_n,
  // //input [7:0] data_in,
  // //input [2:0] func,
  // input [4:0] btn,
  // output reg [7:0] seg1,
  // output reg [7:0] seg0
  // //output [15:0]led
// wire [7:0] data_out;
// linear_feedback_shift_register u_lfsr(
//   .clk(|(btn)),
//   .rst_n(rst_n),
//   .data_out(data_out)
// );

// seven_seg_decoder u_seven_seg0(
//   .digit(data_out[3:0]),
//   .segments(seg0[7:1])
// );
// assign seg0[0] = 1'b0;
// seven_seg_decoder u_seven_seg1(
//   .digit({data_out[7:4]}),
//   .segments(seg1[7:1])
// );
// assign seg1[0] = 1'b0;

// light u_light(
//     .clk(clk),
//     .rst(rst),
//     .led(led)
// );


//exercise two
// wire [2:0] u_digit;
// encoder_83 u_encoder_83(
//   .in(data_in),
//   .out(u_digit[2:0]),
//   .valid(led[0])
// );

// seven_seg_decoder u_seven_seg_decoder(
//   .digit({1'b0,u_digit}),
//   .segments(seg0[7:1])
// );

// assign seg0[0] = 1'b0;


//exercise three
// Sim_ALU u_Sim_ALU(
//   .A(data_in[3:0]),
//   .B(data_in[7:4]),
//   .func(func),
//   .result(led[3:0]),
//   .overflow(led[5]),
//   .out(led[6]),
//   .carry(led[7]),
//   .zero(led[8])
// );




endmodule
