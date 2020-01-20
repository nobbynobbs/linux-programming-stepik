/**
В системе существуют 2 региона разделяемой памяти,
заполненной некоторыми числами (типа int).
Каждый из регионов имеет размер 1000 байт.

Вам требуется разработать приложение, которое попарно суммирует
первые 100 чисел в этих регионах и помещает суммы в новый
(созданный вашим приложением) регион памяти размером 1000 байт.

Таким образом, после завершения работы Вашего приложения в памяти
должен существовать регион разделяемой памяти размером 1000 байт,
содержащий в начале 100 сумм.

Перед завершением работы приложение выводит в стандартный поток
ключ созданного региона, завершающийся символом конца строки.
На вход ваше приложение принимает ключи существующих регионов памяти.


Пример вызова

./solution 456764 456768
512997
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <sys/shm.h>

const int NUMS_COUNT = 100;
const int SIZE = 1000;

int main(int argc, char *argv[]) {
  key_t reg1_key, reg2_key, my_key;
   
  // parse keys
  reg1_key = (key_t)atoi(argv[1]);
  reg2_key = (key_t)atoi(argv[2]);

  //printf("parsed keys:  %d, %d\n", reg1_key, reg2_key);

  // create new key.
  char proc[100];
  sprintf(proc, "/proc/%d", getpid());

  my_key = ftok(proc, 'q');
  if (my_key < 0) {
    perror("could not create the key");
    return -1;
  }
  
  // create new region
  int my_shmid, reg1_shmid, reg2_shmid;
  int *my_ints, *reg1_ints, *reg2_ints;
 
  my_shmid = shmget(my_key, SIZE, IPC_CREAT | 0666);
  my_ints = (int*)shmat(my_shmid, NULL, 0);

  // attach to existing regions
  reg1_shmid = shmget(reg1_key, SIZE, 0);
  reg1_ints = (int*)shmat(reg1_shmid, NULL, SHM_RDONLY);
  
  reg2_shmid = shmget(reg2_key, SIZE, 0);
  reg2_ints = (int*)shmat(reg2_shmid, NULL, SHM_RDONLY);

  // calc sums
  int i;
  for (i=0; i<NUMS_COUNT; i++) {
     my_ints[i] = reg1_ints[i] + reg2_ints[i];
  }

  // detach shmem
  shmdt(my_ints); shmdt(reg2_ints); shmdt(reg2_ints);

  // print new region key
  printf("%d\n", my_key);

  return 0;
}

