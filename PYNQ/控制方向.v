module chassis_control
#(parameter DIRECTION_WIDTH=3) (
    input  wire clk, rst_n,
    input  wire [DIRECTION_WIDTH-1:0] direction,
    output reg [7:0] DIR_output
);

always @ (posedge clk)
if(rst_n == 1'b0)begin
    DIR_output[0] <=1'b0;
    DIR_output[1] <=1'b0;
    DIR_output[2] <=1'b0;
    DIR_output[3] <=1'b0;
    DIR_output[4] <=1'b0;
    DIR_output[5] <=1'b0;
    DIR_output[6] <=1'b0;
    DIR_output[7] <=1'b0;
end
else
    begin
       case (direction) 
        3'd0 ://Stop
            begin
            DIR_output[0] <=1'b0;
            DIR_output[1] <=1'b0;
            DIR_output[2] <=1'b0;
            DIR_output[3] <=1'b0;
            DIR_output[4] <=1'b0;
            DIR_output[5] <=1'b0;
            DIR_output[6] <=1'b0;
            DIR_output[7] <=1'b0;
            end  

        3'd1 : //Forward
        begin
            DIR_output[0] <=1'b1;
            DIR_output[1] <=1'b0;
            DIR_output[2] <=1'b1;
            DIR_output[3] <=1'b0;
            DIR_output[4] <=1'b1;
            DIR_output[5] <=1'b0;
            DIR_output[6] <=1'b1;
            DIR_output[7] <=1'b0;
        end

        3'd2 : //Backward
        begin
            DIR_output[0] <=1'b0;
            DIR_output[1] <=1'b1;
            DIR_output[2] <=1'b0;
            DIR_output[3] <=1'b1;
            DIR_output[4] <=1'b0;
            DIR_output[5] <=1'b1;
            DIR_output[6] <=1'b0;
            DIR_output[7] <=1'b1;
        end

       3'd3 : //Left
        begin
            DIR_output[0] <=1'b0;
            DIR_output[1] <=1'b1;
            DIR_output[2] <=1'b0;
            DIR_output[3] <=1'b1;
            DIR_output[4] <=1'b1;
            DIR_output[5] <=1'b0;
            DIR_output[6] <=1'b1;
            DIR_output[7] <=1'b0;
        end

       3'd4: //Right
        begin
            DIR_output[0] <=1'b1;
            DIR_output[1] <=1'b0;
            DIR_output[2] <=1'b1;
            DIR_output[3] <=1'b0;
            DIR_output[4] <=1'b0;
            DIR_output[5] <=1'b1;
            DIR_output[6] <=1'b0;
            DIR_output[7] <=1'b1;
        end

        default: 
            begin
                DIR_output[0] <=1'b0;
                DIR_output[1] <=1'b0;
                DIR_output[2] <=1'b0;
                DIR_output[3] <=1'b0;
                DIR_output[4] <=1'b0;
                DIR_output[5] <=1'b0;
                DIR_output[6] <=1'b0;
                DIR_output[7] <=1'b0;
            end
     endcase
    end
endmodule