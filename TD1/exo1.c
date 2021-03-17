#include <stdio.h>
#include <stdlib.h>

void plus(int *a, int *b, int *c) {
    *c = *a + *b;
}

void moins(int *a, int *b, int *c) {
    *c = *a - *b;
}

void fois(int *a, int *b, int *c) {
    *c = *a * *b;
}

int main(int argc, char *argv[]) {
    int x = 50;
    int y = 20;
    int z = 0;

    plus(&x, &y, &z);
    printf("plus \t: x=%d y=%d z=%d\n", x, y, z);
    moins(&x, &y, &z);
    printf("moins \t: x=%d y=%d z=%d\n", x, y, z);
    fois(&x, &y, &z);
    printf("fois \t: x=%d y=%d z=%d\n", x, y, z);

    return 0;
}
