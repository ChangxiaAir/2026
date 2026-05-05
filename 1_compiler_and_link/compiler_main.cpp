//
// Created by marquezzz on 2026/5/2.
//

extern int gdata;  // *UND*
int sum(int, int);  // *UND*

int data = 10;  // .data

int main() {    // .text
    int a = gdata;
    int b = data;

    int ret = sum(a, b);

    return 0;
}