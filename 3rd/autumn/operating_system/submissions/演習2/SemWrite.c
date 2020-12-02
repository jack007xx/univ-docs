#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define THREADS 10

sem_t sem_data, sem_readers;
int readers = 0;
int data = 0;

void *writer(void *arg) {
  int f;
  f = ((int)arg);
  sem_wait(&sem_data);
  data = data + 2;
  printf("Data writen by the writer%d is %d\n", f, data);
  // sleep(2);
  sem_post(&sem_data);
}

void *reader(void *arg) {
  int f;
  f = ((int)arg);

  // readers アクセス部
  sem_wait(&sem_readers);
  if (readers == 0) {
    // reader の代表が書き込みロック
    sem_wait(&sem_data);
  }
  readers++;
  sem_post(&sem_readers);

  printf("Data read by the reader%d is %d\n", f, data);
  // sleep(2);

  // readers アクセス部
  sem_wait(&sem_readers);
  if (readers == 1) {
    // 最後にアクセスしたreaderがロック解除
    sem_post(&sem_data);
  }
  readers--;
  sem_post(&sem_readers);
}

main() {
  int i, b;
  pthread_t wtid[THREADS], rtid[THREADS];
  sem_init(&sem_data, 0, 1);
  sem_init(&sem_readers, 0, 1);
  for (i = 0; i <= THREADS - 1; i++) {
    pthread_create(&wtid[i], NULL, writer, (void *)i);
    pthread_create(&rtid[i], NULL, reader, (void *)i);
  }

  for (i = 0; i <= THREADS - 1; i++) {
    pthread_join(wtid[i], NULL);
    pthread_join(rtid[i], NULL);
  }
}
