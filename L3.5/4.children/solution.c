/**
Разработать программу solution, которая по заданному pid
осуществляет поиск всех потомков процесса с этим идентификатором
и выводит их количество (включая процесс с заданным pid).

Пример вызова

./solution 1233
76
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <dirent.h>
#include <string.h>


pid_t my_getppid(pid_t);

// walk through all the processes, check if ppid == our pid,
// increase the counter and recursively run next walk through
// using new pid  
int count_children(pid_t target_ppid) {
  DIR *proc_d = opendir("/proc");
  struct dirent * dir;
  int count = 1; 
  pid_t pid, ppid;
  while ((dir = readdir(proc_d)) != NULL) {
    pid = 0;
    sscanf(dir->d_name, "%d", &pid);
    
    if (!pid) {
      continue;
    }
    
    ppid = my_getppid(pid);
    if (ppid == target_ppid) {
      count += count_children(pid);
    }
  }
  
  closedir(proc_d);
  return count;
}


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
  int c = count_children(pid);
  printf("%d\n", c);
  return 0;
}

