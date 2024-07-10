#include <stdio.h>
#include <stdlib.h>

int* fun() {
    int* a = (int*)malloc(sizeof(int)); // 동적 메모리 할당
    *a = 2;
    return a;
}

int main() {
    int* p = fun();
    *p = 20;
    printf("%d\n", *p); // p가 가리키는 값을 출력
    free(p); // 동적 메모리 해제
    return 0;
}


// int* func(){
//     int a =2;
//     return &a;
// }//  이 로컬 변수는 함수가 종료되면 메모리가 해제되므로, 이를 참조하면 예기치 않은 동작이나 프로그램 충돌을 유발할 수 있음.


// void main(){
//     int* p = func();
//     *p = 20;
// }