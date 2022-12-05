#include <stdio.h>
#include <string.h>

int main(void) {
    char ch = 'A';
    ch = ch + 65;
    putchar(ch);
    ch = ch + 'A';
    printf("done");
}
