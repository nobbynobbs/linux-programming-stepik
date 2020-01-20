/**
Разработать программу solution, которая при запуске себя "демонизирует"
и остается в  памяти.

Перед закрытием стандартного потока вывода stdout
унаследованного от родителя, программа должна вывести
в него Pid процесса-демона.

Пример вызова

./solution
13221
*/

#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
  pid_t pid = fork();
  if (pid == 0) {
    chdir("/");
    setsid();

    fclose(stdin);
    fclose(stderr);
    printf("%d\n", getpid());
    fclose(stdout);

    while (1) {
      sleep(5);
    }
  } 

  return 0;
}

