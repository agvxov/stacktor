// @BAKE g++ $@ -o stacktor.out -ggdb -O0

#include <stdio.h>

#include "stacktor.hpp"

void print_stractor(stacktor<int> &s) {
    fputs("[ ", stdout);
    /*
    for (auto i : s) {
        printf("%d ", i);
    }
    */
    for (int i = 0; i < s.size(); i++) {
        printf("%d ", s.get(i));
    }
    fputc(']', stdout);
}

signed main() {
    // It MUST be on the heap
    stacktor<int> * s = new stacktor<int>();

    puts("");
    s->push_back(10);
    puts("");
    s->push_back(12);
    puts("");
    s->push_back(6);
    puts("");
    print_stractor(*s);

    return 0;
}
