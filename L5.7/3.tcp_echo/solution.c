/**
Разработайте TCP сервер, предназначенный для сортировки символов в строке.
Сервер получает на вход строки, оканчивающиеся символом '\0',
сортирует в них символы в порядке убывания ASCII-кодов
и отсылает обратно на клиент, в виде строки заканчивающейся '\0'.
Завершение работы сервера происходит после получения строки,
содержащей только 'OFF'. 

При старте сервер получает на вход номер порта
в качестве параметра командной строки,
bind производится на адресе 127.0.0.1


Пример вызова

./solution 13555
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

void sort_str(char *str);
int cmp(const void *a, const void *b);

const int BUFFER = 5 << 10; // 5 KB

int main(int c, char **v)
{
  struct sockaddr_in local;
  
  if (c < 2) {
    return -1;
  }

  int port = atoi(v[1]);
  int s = socket(AF_INET, SOCK_STREAM, 0);
  
  inet_aton("127.0.0.1", &local.sin_addr);
  local.sin_port = htons(port);
  local.sin_family = AF_INET;

  bind(s, (struct sockaddr*)&local, sizeof(local));
  
  char buf[BUFFER + 1];
  
  listen(s, 5);
  int ss = accept(s, NULL, NULL);
  while (true) {
    int bytes = read(ss, buf, BUFFER);
    buf[bytes] = 0;
    if (!strcmp(buf, "OFF")) {
      break;
    }
    sort_str(buf);
    send(ss, buf, strlen(buf), 0);
  }

  return 0;
}


void sort_str(char *str)
{
  qsort(str, strlen(str), 1, cmp);
}

int cmp(const void* a, const void* b)
{
  return *(char*)b - *(char*)a;
}

