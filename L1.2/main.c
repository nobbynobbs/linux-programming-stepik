#include <stdio.h>

#include "solution.h"


int main() {

	int count = 8;
	int res = stringStat("five", 5, &count);
	printf("res=%d, count=%d", res, count);
	return 0;
}
