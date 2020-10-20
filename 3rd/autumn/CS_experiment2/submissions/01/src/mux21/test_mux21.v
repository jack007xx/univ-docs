`timescale 1ns / 1ns

`include "mux21.v"

module test_mux21;
  reg S1, D0, D1;
  wire Y;
  mux21 mux21a(S1, D0, D1, Y);

  initial begin
    S1=0; D0=0; D1=0;
    #20 S1=0; D0=1; D1=0;
    #20 S1=1; D0=1; D1=0;
    #20 S1=0; D0=0; D1=0;
    #80 $finish;
  end
endmodule
