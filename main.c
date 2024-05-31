#include "stdio.h"

#include "extern.h"

int main() {
    // sum함수는 다른곳에 있다. extern.h에 있다.
    int a = sum(1, 2);
    printf("result: %d\n", a);
    return 0;
}