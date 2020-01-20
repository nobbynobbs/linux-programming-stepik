/**
Разработать программу solution, которая по заданному pid
осуществляет поиск пути в дереве процессов до процесса
с идентификатором 1 (init).

Для каждого найденного процесса печатается его идентификатор.

Пример вызова

./solution 1766
1766
1299
465
1
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// returns process parent pid
pid_t my_getppid(pid_t pid) {

  char path[100];
  sprintf(path, "/proc/%d/stat", pid);
  
  FILE *fd = fopen(path, "r");
	
  pid_t ppid;
  fscanf(fd, "%*d %*s %*c %d", &ppid);
  fclose(fd);

  return ppid;
}


int main(int argc, char *argv[]) {
  pid_t pid = atoi(argv[1]);
  pid_t ppid = 0;
  printf("%d\n", pid);
  while (pid != 1) {
    ppid = my_getppid(pid);
    printf("%d\n", ppid);
    pid = ppid;
  }

  return 0;
}

