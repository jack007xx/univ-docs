/********************/
/* shifter32_32_l2.v */
/********************/

//             +----+
// sh_a[31:0]->|    |->sh_y[31:0]
//             +----+

module shifter32_32_l2 (sh_a, sh_y);  // 入出力ポート
  input  [31:0]  sh_a;          // 入力 32-bit
  output [31:0]  sh_y;          // 出力 32-bit

  //Body
  //2-bit 左シフト
  assign sh_y = {sh_a[29:0], 2'b00};
endmodule
