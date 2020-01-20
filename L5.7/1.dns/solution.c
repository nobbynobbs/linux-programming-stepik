/**
Разработайте утилиту командной строки, принимающую на вход
имя хоста и печатающую в стандартный поток вывода список IP-адресов,
ассоциированных с данным именем.

Пример вызова

./solution yandex.ru
213.180.204.3
93.158.134.3
213.180.193.3
*/

#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>


int main(int c, char **v)
{ 
  if (c < 2) {
    return -1;
  }
  
  struct hostent *h;
  h = gethostbyname(v[1]);

  int i=0;
  while (h->h_addr_list[i] != NULL) {
    struct in_addr *a = (struct in_addr*)h->h_addr_list[i];
    printf("%s\n", inet_ntoa(*a));
    i++;
  }
}

