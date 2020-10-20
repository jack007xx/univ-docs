module mux21 (S1, D0, D1, Y);
  input S1, D0, D1;
  output Y;
  assign Y = (~S1 & D0) | (S1 & D1);
endmodule
