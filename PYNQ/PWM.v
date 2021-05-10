module pwm
#(
        parameter N = 32 //pwm bit width 
)(
    input clk,
    input rst,
    input [N-1:0]period,
    input [N-1:0]duty,
    output pwm_out
);
reg [31:0]fre_cnt;
always @(posedge clk)begin
    if(rst==1'b0)begin
        fre_cnt <=32'd0;
    end
    else begin
        if(fre_cnt<period) begin
            fre_cnt <= fre_cnt+1'b1;
        end
        else begin
            fre_cnt<=32'd0;
        end
    end
end
assign pwm_out = (duty>fre_cnt);
endmodule