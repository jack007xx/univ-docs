#include <stdio.h>
#include <stdlib.h>

typedef struct que {
  int remain;
  int index;
  struct que *next;
  struct que *prev;
} Que;

Que *Top = NULL;
Que *End = NULL;

void push(int remain, int index) {
  Que *t = malloc(sizeof(Que));
  t->remain = remain;
  t->index = index;

  if (Top == NULL) {
    Top = t;
    End = t;
  } else {
    t->next = Top;
    Top->prev = t;
    Top = t;
  }
}

Que *pop() {
  Que *t = End;
  if (End == Top) {
    Top = NULL;
    End = NULL;
  } else {
    End = End->prev;
  }

  return t;
}

int main(int argc, char const *argv[]) {
  int n;
  scanf("%d", &n);

  int *process_time = malloc(sizeof(int) * n);
  int *arrival = malloc(sizeof(int) * n);
  int *result = malloc(sizeof(int) * n);

  for (int i = 0; i < n; i++) {
    scanf("%d %d", &process_time[i], &arrival[i]);
  }

  printf("process start\n");

  Que *prosessing = NULL;
  int finished = 0;
  int time = -1;

  while (finished < n) {
    time++;
    printf("%d : ", time);
    for (int i = 0; i < n; i++)
      if (arrival[i] == time) push(process_time[i], i);

    if (prosessing == NULL) prosessing = pop();

    if (prosessing != NULL) {
      prosessing->remain--;
      printf("processing %d, remain %d\n", prosessing->index,
             prosessing->remain);

      if (prosessing->remain == 0) {
        // プロセスが完了したら応答時間を計測
        finished++;
        result[prosessing->index] = time + 1 - arrival[prosessing->index];
        prosessing = pop();
      }
    }
  }

  printf("\n");
  for (int i = 0; i < n; i++) printf("process %d : %d\n", i, result[i]);
  printf("\ntotal : %d\n", time + 1);

  return 0;
}
