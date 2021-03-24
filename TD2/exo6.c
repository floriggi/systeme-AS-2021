#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"

void afficherContenuDossier(char const *chemin) {
    DIR *d = opendir(chemin);
    if (d == NULL) {
        printf("Erreur ouverture dossier");
        exit(EXIT_FAILURE);
    }

    struct dirent *entree;

    while ((entree = readdir(d)) != NULL) {
        // si ce n'est pas un dossier
        if (entree->d_type != DT_DIR) {
            printf("%s%s\n", BLUE, entree->d_name);
        } else if (entree->d_type == DT_DIR
                   && strcmp(entree->d_name, ".") != 0
                   && strcmp(entree->d_name, "..") != 0) {
            printf("%s%s\n", GREEN, entree->d_name);

            char nouveauDossier[257];
            sprintf(nouveauDossier, "%s/%s", chemin, entree->d_name);
            afficherContenuDossier(nouveauDossier);
        }
    }

    closedir(d);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Le programme attend un argument !\n");
        return EXIT_FAILURE;
    }

    printf("Lecture du dossier : %s\n", argv[1]);
    printf("%s\n", NORMAL_COLOR);

    afficherContenuDossier(argv[1]);
    printf("%s\n", NORMAL_COLOR);

    return EXIT_SUCCESS;
}
