 module shift_reg #(
    parameter DATA_WIDTH = 8
 ) (
    input clk,
    input rst_n,
    input [2:0] ctrl,
    input [DATA_WIDTH-1:0] data_in,
    //input data,
    output reg [DATA_WIDTH-1 : 0] Q
 );
    always @(posedge clk or negedge rst_n) begin
        if(!rst_n) Q <= {DATA_WIDTH{1'b0}};
        else begin
            case (ctrl)
                3'b000:begin
                    Q <=  {DATA_WIDTH{1'b0}};
                end
                3'b001:begin
                    Q <= data_in;
                end
                3'b010:begin
                    Q <= {1'b0,Q[(DATA_WIDTH-1):1]};
                end
                3'b011:begin
                    Q <= {Q[(DATA_WIDTH-2):0],1'b0};
                end
                3'b100:begin
                    Q <= {Q[DATA_WIDTH-1],Q[(DATA_WIDTH-1):1]};
                end
                3'b101:begin
                    Q <= {data_in[0],Q[(DATA_WIDTH-1):1]};
                end
                3'b110:begin
                    Q <= {Q[0],Q[(DATA_WIDTH-1):1]};
                end
                3'b111:begin
                    Q <= {Q[(DATA_WIDTH-2):0],Q[DATA_WIDTH-1]};
                end
                default: 
                    Q <= Q;
            endcase

        end
    end

 endmodule