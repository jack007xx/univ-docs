module bcd1 (
    clk, reset, x, bcd1_out
);
input clk, reset, x;
output [3:0] bcd1_out;

reg [3:0] r0;

assign bcd1_out=r0;

always @(posedge clk or negedge reset) begin
    if (reset == 1'b0) begin
        r0<=4'b0000;
    end else begin
        if (x == 1'b1) begin
            if (r0 < 9) begin
                r0<=r0+1'b1;
            end else begin
                r0<=4'b0000;
            end
        end
    end
end

endmodule
