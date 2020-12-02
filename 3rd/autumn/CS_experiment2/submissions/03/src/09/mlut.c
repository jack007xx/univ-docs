#define EXTIO_SCAN_ASCII (*(volatile unsigned int *)0x0310)
#define EXTIO_SCAN_REQ (*(volatile unsigned int *)0x030c)
#define EXTIO_SCAN_STROKE (*(volatile unsigned int *)0x0308)

#define SCAN_STRORING (unsigned int)0xffffffff

#define EXTIO_PRINT_STROKE (*(volatile unsigned int *)0x0300)
#define EXTIO_PRINT_ASCII (*(volatile unsigned int *)0x0304)

#define TRUE 0x1
#define FALSE 0x0

unsigned int sosuu_check(unsigned int kouho);
unsigned int my_a2i();
void my_i2a();
void my_print();
void my_scan();

main() {
  unsigned int k;
  unsigned int str1[16];
  unsigned int str2[16];

  /* "HELLO" を print */
  str1[0] = 'H';
  str1[1] = 'E';
  str1[2] = 'L';
  str1[3] = 'L';
  str1[4] = 'O';
  str1[5] = '\n';
  str1[6] = '\0';
  my_print(str1);

  while (1) {
    /* "NUM=" を print */
    str1[0] = 'N';
    str1[1] = 'U';
    str1[2] = 'M';
    str1[3] = '=';
    str1[4] = '\0';
    my_print(str1);

    /* キーボードから入力された文字列（数字）を str2[] に記憶 */
    my_scan(str2);

    /* "ECHO " を print */
    str1[0] = 'E';
    str1[1] = 'C';
    str1[2] = 'H';
    str1[3] = 'O';
    str1[4] = ' ';
    str1[5] = '\0';
    my_print(str1);

    /* str2[] を print */
    my_print(str2);

    /* '\n' を print */
    str1[0] = '\n';
    str1[1] = '\0';
    my_print(str1);

    /* 文字列（数字） srt2[] を unsigned int に変換 */
    k = my_a2i(str2);

    /* k × k を計算 */
    k = k * k;

    /* unsigned int k を文字列（数字）に変換して print */
    my_i2a(k);

    /* '\n' を print */
    str1[0] = '\n';
    str1[1] = '\0';
    my_print(str1);
  }
}

/* 文字列（数字） srt[] を unsigned int に変換する関数 */
/* unsigned int result を返す */
unsigned int my_a2i(str) unsigned int *str;
{
  // 省略
}

/* unsigned int i を文字列（数字）に変換して print する関数 */
void my_i2a(unsigned int i) {
  // 省略
}

/* キーボードから入力された文字列を str[] に記憶する関数 */
void my_scan(str) unsigned int *str;
{
  // 省略
}

/* 文字列 str[] を表示する関数 */
void my_print(str) unsigned int *str;
{
  // 省略
}
