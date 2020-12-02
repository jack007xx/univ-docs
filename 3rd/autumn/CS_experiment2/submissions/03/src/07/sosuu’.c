// 省略

main() {
  // 省略
}

/* unsigned int kouho の素数判定を行う関数 */
/* 素数なら TRUE を返す */
/* 素数でないなら FALSE を返す */
unsigned int sosuu_check(unsigned int kouho) {
  unsigned int t, tester;

  for (t = 2; t <= kouho; t += 2) {
    if (t == kouho) {
      return FALSE;
    }
  }

  for (t = 3; t < kouho; t += 2) {
    for (tester = t; tester <= kouho; tester += t) {
      if (tester == kouho) {
        return FALSE;
      }
    }
  }

  return TRUE;
}

// 省略
