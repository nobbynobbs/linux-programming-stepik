/**
Разработать приложение, умеющее обрабатывать сигналы
SIGUSR1 ,SIGUSR2, SIGTERM

 После старта Ваше приложение должно по приходу одного из сигналов
SIGUSR1,  SIGUSR2 выполнять подсчет количества срабатываний
каждого из сигналов, а после прихода сигнала SIGTERM,
требуется вывести в стандартный поток вывода 2 числа,
разделенных пробелом, соответствующих количеству обработанных
сигналов SIGUSR1, SIGUSR2, и завершить программу.
Вывод оканчивается символом конца строки.

Пример вызова

./solution 
79 38
*/

#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

int sigusr1_counter = 0;
int sigusr2_counter = 0;
bool run = true;

void signal_handler(int signum) {
  switch (signum) {
  case SIGUSR1:
    sigusr1_counter++;
    break;
  case SIGUSR2:
    sigusr2_counter++;
    break;
  case SIGTERM:
    run = false;
    break;
  }
}

int main() {
  signal(SIGUSR1, signal_handler);
  signal(SIGUSR2, signal_handler);
  signal(SIGTERM, signal_handler); 
  
  while (run) {
    sleep(1);
  }
  
  printf("%d %d\n", sigusr1_counter, sigusr2_counter);

  return 0;
}

