/**

Разработать программу solution, обеспечивающую загрузку
динамической библиотеки в режиме исполнения. При запуске,
программе передается имя динамической библиотеки,
имя функции которая должна быть вызвана, и ее аргумент.

Функция в библиотеке принимает на вход int и возвращает int.
Результат, возвращаемый функцией должен быть выведен отдельной строкой
(оканчиваться символом новой строки \n) в stdout.

Пример вызова


./solution libShared.so someSecretFunctionPrototype 8
16

В примере, должна быть загружена библиотека libShared.so,
в которой вызвана функция someSecretFunctionPrototype с аргументом 8.
Результат (16) выведен в stdout.
*/


#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dlfcn.h>


typedef int (*secretFunction)(const int);  // define type
secretFunction func;  // define function

bool init(char *libName, char *funcName) {
	void *libPtr = dlopen(libName, RTLD_LAZY); // load lib
	if (libPtr == NULL) {
		printf("unable to load library\n");
		return false;
	}
	func = (secretFunction)dlsym(libPtr, funcName);  // load func
	if (func == NULL) {
		printf("unable to load function\n");
		return false;
	}
	return true;
}


int main(int argc, char *argv[]) {
  if (argc != 4) {
    return 1;
  }

  char *libName = argv[1];
  char *funcName = argv[2];
  int num = atoi(argv[3]);

  if (!init(libName, funcName)) {
    return 1;	
  }

  int res = func(num);
  printf("%d\n", res);

  return 0;
}

