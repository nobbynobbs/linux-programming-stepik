/**
Разработайте UDP сервер для логирования (сбора и записи) сообщений.
Сервер при запуске принимает параметр -- номер порта,
на котором будут приниматься запросы.

Каждый запрос приходящий к серверу - строка, не превышающая размер 5K.
Задача сервера -- выводить приходящие строки в стандартный поток,
завершающиеся символом конца строки.

Сервер завершает работу, когда получает строку содержащую только текст 'OFF',
и заканчивающуюся символом перевода строки '\n'. 

Сервер использует локальный адрес 127.0.0.1

Пример вызова


./solution 22476
foo
bar 
foo bar baz
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>


const int BUFFER = 5 << 10; // 5 KB

int main(int c, char **v)
{
  struct sockaddr_in local;
  
  if (c < 2) {
    return -1;
  }

  int port = atoi(v[1]);
  int s = socket(AF_INET, SOCK_DGRAM, 0);
  
  inet_aton("127.0.0.1", &local.sin_addr);
  local.sin_port = htons(port);
  local.sin_family = AF_INET;

  bind(s, (struct sockaddr*)&local, sizeof(local));
  
  char buf[BUFFER + 1];
  
  while (true) {
    int bytes = read(s, buf, BUFFER);
    buf[bytes] = 0;
    if (!strcmp(buf, "OFF\n")) {
      break;
    }
    printf("%s\n", buf);
  }

  return 0;
}

