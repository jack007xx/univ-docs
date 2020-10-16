
`timescale 1ns / 1ns

`include "adder16s.v"

module test ;
        reg reset, clk, cin;
        reg [15:0] x, y;
 
        wire [15:0] sum;
        wire cout;
 
        adder16s  adder16s(clk, reset, x, y, cin, sum, cout);
 
        always begin
                #5      clk = ~clk;
        end
 
        always begin
                #8      x = x + 100;
                        y = y + 200;
        end
 
        initial begin
 
           reset = 1; clk = 0; x = 0; y = 0; cin = 0 ;
           #20 reset = 0;
           #20 reset = 1;
        end
 
endmodule
