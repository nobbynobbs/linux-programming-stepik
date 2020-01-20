/**
Разработать программу solution, которая осуществляет
поиск и подсчет числа процессов с именем genenv в системе Linux
на которой выполняется программа. 

Пример вызова

./solution
13
*/

#include <stdio.h>
#include <stddef.h>
#include <dirent.h>
#include <string.h>

char *MATCH = "genenv";

int main() {
  DIR *procDir = opendir("/proc");
  struct dirent *dir;
  int pid;
  int count = 0;
  while ((dir = readdir(procDir)) != NULL) {
    pid = 0;
    sscanf(dir->d_name, "%d", &pid);
    if (pid > 0) {
      char commFilePath[50];
      sprintf(commFilePath, "/proc/%d/comm", pid);
 
      FILE *fd = fopen(commFilePath, "r");
      char procName[50];
      fscanf(fd, "%s", procName);
      fclose(fd);
      if (strcmp(procName, MATCH) == 0) {
        count++;
      }
    }
  }
  closedir(procDir);
  printf("%d\n", count);
  return 0;
}

