#include "extern.h"

int sum(int a, int b) {
    return a + b;
}

// gcc -c extern.c => 컴파일만 수행. object 파일이 생성됨.
// object파일은 실행파일이 아니다. 실행파일을 만들기 위한 중간파일 
// object파일은 기계어로 되어있어요.

// 컴파일러, 링커의 역할
// 컴파일러: 소스코드를 기계어로 만들어줌. 외부의 코드를 찾아오지 않는다.
// 링커: object파일을 실행파일로 만들어줌. 외부의 코드를 찾아온다. 이름 매칭을 해줍니다.

// main.o[main함수가 존재, sum함수를 사용, printf함수를 사용.]  , extern.o [sum함수가 존재]
// 링커가 이걸 딱 봤을때. main.o에서 sum함수를 찾아야 한다. => extern.o에서 찾아야 한다. => 찾아서 링크해준다.

// 1. extern.o main.o파일 생성. -> link하면 실행파일나옴.
// 2. 순서는 상관없다. 모두 만들어야한다.
