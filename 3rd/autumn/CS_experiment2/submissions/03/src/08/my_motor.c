// 省略
main() {
  unsigned int output[32];
  unsigned int input[32];

  unsigned int steps, direction;

  while (1) {
    output[0] = 'S';
    output[1] = 'T';
    output[2] = 'E';
    output[3] = 'P';
    output[4] = '=';
    output[5] = '\0';
    my_print(output);

    my_scan(input);
    steps = my_a2i(input);

    output[0] = 'D';
    output[1] = 'I';
    output[2] = 'R';
    output[3] = '?';
    output[4] = '=';
    output[5] = '\0';
    my_print(output);

    my_scan(input);
    direction = my_a2i(input);

    if (direction == 0) {
      my_motor(0x1248, steps);
    } else {
      my_motor(0x8421, steps);
    }

    output[0] = 'D';
    output[1] = 'O';
    output[2] = 'N';
    output[3] = 'E';
    output[4] = '!';
    output[5] = '\n';
    output[6] = '\0';
    my_print(output);
  }
}

void my_motor(unsigned int table, unsigned int steps) {
  int cnt;
  int shifter = 0;
  for (cnt = 0; cnt < steps; cnt++) {
    shifter = (shifter == 12 ? 4 : shifter + 4);
    ext_out((table >> shifter) & 0b1111);
  }
}

void ext_out(unsigned int num) { GPIO0 = num; }

unsigned int my_a2i(str) unsigned int *str;
{
  // 省略
}

void my_scan(str) unsigned int *str;
{
  // 省略
}

void my_print(str) unsigned int *str;
{
  // 省略
}
