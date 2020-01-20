/**
Разработать программу solution, которая осуществляет
поиск родительского PID текущего процесса в файловой системе proc
и выводит найденное значение на консоль.

Результат, возвращаемый функций должен быть выведен отдельной строкой
(должен оканчиваться символом перевода строки \n) в stdout.

Пример вызова

./solution
13221
*/


#include <stdio.h>
#include <unistd.h>

int main() {
	pid_t pid = getpid();
	
	char path[100];
       	sprintf(path, "/proc/%d/stat", pid);
	
	FILE *fd = fopen(path, "r");
	
	pid_t ppid;
	fscanf(fd, "%*d %*s %*c %d", &ppid);
	
        fclose(fd);
	
	printf("%d\n", ppid);
        return 0;
}

