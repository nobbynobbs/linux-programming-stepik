/**
В текущем каталоге есть 2 канала in1 in2,
в которые в случайном порядке поступают числа,
которые необходимо просуммировать и вывести окончательную сумму на экран.

Сумма выводится в отдельной строке, завершающейся символом конца строки.
Признаком окончания подачи символов в каналы является
закрытие этих каналов посылающей стороной.

Подсказка: для неблокирующего чтения использовать select.
Замечание: протокол обмена по каналу текстовый,
то есть числа представлены строками

Пример вызова

./solution 
795
*/

#include <stdio.h>
#include <errno.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>

bool any_fd_isset(fd_set *watchset, int fds[], int count);
int read_int(int fd, fd_set *watchset);
int max(int[], int);


const int BUFFER = 100;
const int PIPES = 2;

int main() {
  int res = 0;
  int fds[PIPES];
  int max_fd;
  
  /** open named pipes */
  char pipe_name[10];
  int pipe_name_len;
  for (int i=0; i < PIPES; i++) {
    pipe_name_len = sprintf(pipe_name, "./in%d", i+1);
    pipe_name[pipe_name_len] = 0;
    int fd = open(pipe_name, O_RDONLY);
    if (fd < 0) {
      return 1;
    }
    fds[i] = fd;
  }

  /** do multiplexing */
  fd_set read_set, inset;
  max_fd = max(fds, PIPES);  

  FD_ZERO(&read_set);
  for (int i=0; i<PIPES; i++) {
    FD_SET(fds[i], &read_set);
  }

  while(any_fd_isset(&read_set, fds, PIPES)) {
    inset = read_set;    

    int result =  select(max_fd + 1, &inset, NULL, NULL, NULL);
    if (!result) {
      continue;
    }
 
   for (int i=0; i<PIPES; i++) {
     if ( FD_ISSET(fds[i], &inset) ) {
       res += read_int(fds[i], &read_set);
     }
   } 
  }
  
  // explicitly close descriptors
  for (int i=0; i<PIPES; i++) {
    close(fds[i]);
  }
  
  printf("%d\n", res);
  return 0;
}

bool any_fd_isset(fd_set *watchset, int fds[], int count) {
  for (int i=0; i<count; i++) {
    if ( FD_ISSET(fds[i], watchset)) {
      return true;
    }
  }
  return false;
}

// read value from channel and convert it to integer
int read_int(int fd, fd_set *watchset) {
  char buf[BUFFER];
  
  int bytes = read(fd, buf, BUFFER - 1);
  if (bytes == 0) {
    FD_CLR(fd, watchset);
    return 0;
  }

  buf[bytes] = 0;
  return atoi(buf);
}

int max(int arr[], int len) {
  int res = -1;
  for(int i=0; i<=len; i++) {
    if (arr[i] > res) {
      res = arr[i];
    }
  }
  return res;
}

