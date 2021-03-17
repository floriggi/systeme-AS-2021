#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

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

void initialiseEtAffichage(Coordonnees *c) {
    initialise(c);
    affichage(c);
}

void additionEtAffichage(Coordonnees *c) {
    addition(c);
    affichage(c);
}

void multiplicationEtAffichage(Coordonnees *c) {
    multiplication(c);
    affichage(c);
}


int main(int argc, char *argv[]) {
    Coordonnees ici;

    printf("initialisation\n");
    initialiseEtAffichage(&ici);

    printf("addition\n");
    additionEtAffichage(&ici);

    printf("multiplication\n");
    multiplicationEtAffichage(&ici);

    return 0;
}
