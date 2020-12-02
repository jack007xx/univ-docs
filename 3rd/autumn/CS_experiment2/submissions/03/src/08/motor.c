#define EXTIO_SCAN_ASCII (*(volatile unsigned int *)0x0310)
#define EXTIO_SCAN_REQ (*(volatile unsigned int *)0x030c)
#define EXTIO_SCAN_STROKE (*(volatile unsigned int *)0x0308)

#define SCAN_STRORING (unsigned int)0xffffffff

#define EXTIO_PRINT_STROKE (*(volatile unsigned int *)0x0300)
#define EXTIO_PRINT_ASCII (*(volatile unsigned int *)0x0304)

#define TRUE 0x1
#define FALSE 0x0

#define GPIO0 (*(volatile unsigned int *)0x0320)

void my_motor(unsigned int table, unsigned int steps);
void ext_out();
unsigned int my_a2i();
void my_print();
void my_scan();

main() {
  unsigned int output[32];
  unsigned int input[32];

  unsigned int table, steps;

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

    my_motor(0x8421, steps);

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
    ext_out((table >> shifter) & 0xf);
  }
}

void ext_out(unsigned int num) {
  unsigned int i;

  GPIO0 = num;
}
unsigned int my_a2i(str) unsigned int *str;
{
  unsigned int *str_tmp;
  unsigned int k;
  unsigned int result;

  str_tmp = str;
  for (k = 0; *str_tmp != '\0'; k++) {
    str_tmp++;
  }

  result = 0;
  str_tmp = str;

  if (k == 1) {
    result = *str_tmp - '0';
  } else if (k == 2) {
    for (k = 0; k < (*str_tmp - '0'); k++) {
      result = result + 10;
    }
    str_tmp++;
    result = result + (*str_tmp - '0');
  } else if (k == 3) {
    for (k = 0; k < (*str_tmp - '0'); k++) {
      result = result + 100;
    }
    str_tmp++;
    for (k = 0; k < (*str_tmp - '0'); k++) {
      result = result + 10;
    }
    str_tmp++;
    result = result + (*str_tmp - '0');
  }

  return result;
}

void my_scan(str) unsigned int *str;
{
  EXTIO_SCAN_STROKE = (unsigned int)0x00000000;
  EXTIO_SCAN_REQ = (unsigned int)0x00000001;
  EXTIO_SCAN_STROKE = (unsigned int)0x00000001;

  EXTIO_SCAN_STROKE = (unsigned int)0x00000000;
  EXTIO_SCAN_STROKE = (unsigned int)0x00000001;
  while (EXTIO_SCAN_ASCII == SCAN_STRORING) {
    EXTIO_SCAN_STROKE = (unsigned int)0x00000000;
    EXTIO_SCAN_STROKE = (unsigned int)0x00000001;
  }

  while ((*str = EXTIO_SCAN_ASCII) != (unsigned int)0x3e) {  // 0x3e=RETURN
    if ((*str >= 1) && (*str <= 26)) {
      *str = 'A' + *str - 1;
    } else if ((*str >= 48) && (*str <= 57)) {
      *str = '0' + *str - 48;
    } else {
      if (*str == 0) {
        *str = '@';
      } else if (*str == 27) {
        *str = '[';
      } else if (*str == 29) {
        *str = ']';
      } else if ((*str >= 32) && (*str <= 47)) {
        *str = ' ' + *str - 32;
      } else if (*str == 58) {
        *str = '?';
      } else if (*str == 59) {
        *str = '=';
      } else if (*str == 60) {
        *str = ';';
      } else if (*str == 61) {
        *str = ':';
      } else if (*str == 62) {
        *str = '\n';
      } else {
        *str = '@';
      }
    }
    EXTIO_SCAN_STROKE = (unsigned int)0x00000000;
    EXTIO_SCAN_STROKE = (unsigned int)0x00000001;
    str++;
  }
  *str = '\0';

  EXTIO_SCAN_STROKE = (unsigned int)0x00000000;
  EXTIO_SCAN_REQ = (unsigned int)0x00000000;
  EXTIO_SCAN_STROKE = (unsigned int)0x00000001;

  EXTIO_SCAN_STROKE = (unsigned int)0x00000000;
}

void my_print(str) unsigned int *str;
{
  while (*str != '\0') {
    EXTIO_PRINT_STROKE = (unsigned int)0x00000000;

    if ((*str >= 'A') && (*str <= 'Z')) {
      EXTIO_PRINT_ASCII = *str - 'A' + 1;
    } else if ((*str >= 'a') && (*str <= 'z')) {
      EXTIO_PRINT_ASCII = *str - 'a' + 1;
    } else if ((*str >= '0') && (*str <= '9')) {
      EXTIO_PRINT_ASCII = *str - '0' + 48;
    } else {
      if (*str == '@') {
        EXTIO_PRINT_ASCII = (unsigned int)0;
      } else if (*str == '[') {
        EXTIO_PRINT_ASCII = (unsigned int)27;
      } else if (*str == ']') {
        EXTIO_PRINT_ASCII = (unsigned int)29;
      } else if ((*str >= ' ') && (*str <= '/')) {
        EXTIO_PRINT_ASCII = *str - ' ' + 32;
      } else if (*str == '?') {
        EXTIO_PRINT_ASCII = (unsigned int)58;
      } else if (*str == '=') {
        EXTIO_PRINT_ASCII = (unsigned int)59;
      } else if (*str == ';') {
        EXTIO_PRINT_ASCII = (unsigned int)60;
      } else if (*str == ':') {
        EXTIO_PRINT_ASCII = (unsigned int)61;
      } else if (*str == '\n') {
        EXTIO_PRINT_ASCII = (unsigned int)62;
      } else {
        EXTIO_PRINT_ASCII = (unsigned int)0x00000000;
      }
    }

    EXTIO_PRINT_STROKE = (unsigned int)0x00000001;
    str++;
  }
}
