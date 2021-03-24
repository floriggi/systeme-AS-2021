#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX 1000

char buffer[MAX];
struct stat statut = {0};

void saisirNomDossier();
void creerDossier();
int sontEgaux(const char* mot1, const char* mot2);


int main(int argc, char const *argv[]) {
    while (1) {
        saisirNomDossier();
        if (sontEgaux(buffer, "exit")) { // si le mot saisie égale "exit", on sort de la boucle
            break;
        }
        creerDossier();
    }
    return EXIT_SUCCESS;
}

void saisirNomDossier() {
    printf("Saisir le nom d'un dossier\n");
    scanf("%s", buffer);
}

void creerDossier() {
    // on test si le dossier n'existe pas
    if (stat(buffer, &statut) == -1) {
        printf("Création du dossier : %s\n", buffer);
        if (mkdir(buffer, 0777) < 0) {
            printf("Erreur création dossier\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Le dossier %s existe déjà.\n", buffer);
    }
}

int sontEgaux(const char* mot1, const char* mot2) {
    return strcmp(mot1, mot2) == 0;
}
