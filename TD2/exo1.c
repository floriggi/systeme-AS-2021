#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define TAILLE 10

int main(int argc, char const *argv[]) {
    int fichier1;
    int fichier2;
    char buffer[TAILLE];

    if ((fichier1 = open("test1.txt", O_RDONLY)) < 0) {
        printf("Erreur ouverture fichier 1\n");
        return EXIT_FAILURE;
    }

    if ((fichier2 = open("test2.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR)) < 0) {
        printf("Erreur ouverture fichier 2\n");
        return EXIT_FAILURE;
    }

    if (read(fichier1, buffer, TAILLE) != TAILLE) {
        printf("Erreur lecture fichier 1\n");
        close(fichier1);
        close(fichier2);

        return EXIT_FAILURE;
    }

    if (write(fichier2, buffer, TAILLE) != TAILLE) {
        printf("Erreur écriture fichier 2\n");
        close(fichier1);
        close(fichier2);

        return EXIT_FAILURE;
    }

    close(fichier1);
    close(fichier2);
    rename("test2.txt", "test3.txt");

    if (unlink("test1.txt") != 0) {
        printf("Erreur suppression fichier");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
