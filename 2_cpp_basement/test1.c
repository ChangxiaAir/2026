//
// Created by marquezzz on 2026/5/2.
//
#include <stdio.h>
int add_int(int a, int b);

int sum(int a, int b) {
    return a + b;
}

int main() {
    int ret = add_int(1, 2);
    printf("c_file_add_int:%d\n", ret);
    return 0;
}

