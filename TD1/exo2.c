#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
    int z;
} Coordonnees;

void affichage(Coordonnees *c) {
    printf("x=%d y=%d z=%d\n", c->x, c->y, c->z);
}

void initialise(Coordonnees *c) {
    c->x = 10;
    c->y = 5;
    c->z = 2;
}

void addition(Coordonnees *c) {
    c->z = c->x + c->y;
}

void multiplication(Coordonnees *c) {
    c->z = c->x * c->y;
}


int main(int argc, char *argv[]) {
    Coordonnees ici;

    printf("initialisation\n");
    initialise(&ici);
    affichage(&ici);

    printf("addition\n");
    addition(&ici);
    affichage(&ici);

    printf("multiplication\n");
    multiplication(&ici);
    affichage(&ici);

    return 0;
}
