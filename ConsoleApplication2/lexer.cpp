#include <iostream>
#include "LA.h"

using namespace std;

int main() {
     const char* fn = "test.cpp";
    LA l(fn);
    l.show();
    l.scan();
    return 0;
}