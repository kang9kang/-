#include <iostream>
#include "LA.h"

using namespace std;

/*
<1,变量类型>
<2,变量名>
<3,整数数字>
<4,运算符>
<5,分隔符>
<6,界符>
<7,语句>
<8,函数>
<9,数组名>
*/

int main() {
     const char* fn = "test.cpp";
    LA l(fn);
    l.show();
    l.scan();
    system("pause");
    return 0;
}