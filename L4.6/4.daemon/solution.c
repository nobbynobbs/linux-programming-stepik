/**
В задании требуется доработать демон,
разработанный ранее в задании 6 модуля 3.5.

Задача -- снабдить демон обработчиком сигнала SIGURG,
по приходу которого демон должен завершать свою работу.

Пример вызова

./solution
13336
*/

#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int signum);

bool run = true;

int main()
{
  pid_t pid = fork();
  if (pid == 0) {
    chdir("/");
    setsid();

    fclose(stdin);
    fclose(stderr);
    printf("%d\n", getpid());
    fclose(stdout);

    signal(SIGURG, handler);

    while (run) {
      sleep(1);
    }
  } 

  return 0;
}

void handler(int signum)
{
  run = false;
}


