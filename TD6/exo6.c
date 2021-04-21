#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TAILLE_MAX 40

typedef struct {
    int *tableau;
    int taille;
    int k;
} Variables;


pthread_mutex_t mutex;
int compteur = 1;

int randomNumber();
void *fonctionPourThread(void *arg);
void trierBulle(int *pdeb, int *pfin);
void saisirTailleTableau(Variables *structure);
void verifierTaille(const int taille);
void creerTableau(Variables *structure);
void afficherTableau(Variables *structure);
void saisirNombreThread(int *nb);
void verifierNombreThread(const int nbThread, const int tailleTableau);


int main(int argc, char const *argv[]) {
    srand(time(NULL));
    Variables structure;

    saisirTailleTableau(&structure);
    verifierTaille(structure.taille);

    printf("Construction d'un tableau de taille %d\n", structure.taille);
    creerTableau(&structure);

    printf("Tableau avant le tri\n");
    afficherTableau(&structure);

    //initialisation du mutex
    pthread_mutex_init(&mutex, NULL);

    int k;
    saisirNombreThread(&k);
    verifierNombreThread(k, structure.taille);

    structure.k = k;
    pthread_t *monThread = malloc(k * sizeof(pthread_t));

    for (int i = 0; i < k; i++) {
        if (pthread_create(&(monThread[i]), NULL, fonctionPourThread, (void *) &structure) < 0) {
            printf("erreur creation thread\n");
            exit(EXIT_FAILURE);
        }
    }

    // on attend tous les threads
    for (int i = 0; i < k; i++) {
        pthread_join(monThread[i], NULL);
    }

    printf("Tableau après le tri\n");
    afficherTableau(&structure);

    return EXIT_SUCCESS;
}

void *fonctionPourThread(void *arg) {
    Variables *temp = (Variables *) arg;

    pthread_mutex_lock(&mutex);
    int numeroDeThread = compteur++;
    pthread_mutex_unlock(&mutex);

    int nbATrier = temp->taille / temp->k;
    int ind_inf = (numeroDeThread - 1) * nbATrier;
    int ind_sup = ind_inf + nbATrier;
    int i;

    if (ind_sup > (temp->taille)) {
        ind_sup = temp->taille - 1;
    }

    printf("Thread %d - taille : %d, trie de %d à %d\n", numeroDeThread, nbATrier, ind_inf, ind_sup);
    trierBulle((temp->tableau) + ind_inf, (temp->tableau) + (ind_sup - 1));

    for (i = ind_inf; i < ind_sup; i++) {
        printf("Thread %d - %d\n", numeroDeThread, *((temp->tableau) + i));
    }

    pthread_exit(NULL);
}

void trierBulle(int *posDebut, int *posFin) {
    printf("%d - %d\n", *posDebut, *posFin);
    int nb = posFin - posDebut;
    int *position;
    int temp;
    int i;

    for (i = 0; i < nb; i++) {
        position = posDebut;

        while (position < (posFin)) {
            if ((*position) > (*(position + 1))) {
                temp = *position;
                *position = *(position + 1);
                *(position + 1) = temp;
            }
            position++;
        }
    }
}

int randomNumber() {
    return (rand() % (100 - 1)) + 1;
}

void saisirTailleTableau(Variables *structure) {
    printf("Saisir la taille du tableau :\n");
    scanf("%d", &(structure->taille));
}

void verifierTaille(const int taille) {
    if (taille > TAILLE_MAX) {
        printf("La taille du tableau ne doit pas dépasser %d\n", TAILLE_MAX);
        printf("Fin du programme\n");
        exit(EXIT_FAILURE);
    }
}

void creerTableau(Variables *structure) {
    structure->tableau = (int *) malloc(structure->taille * sizeof(int));

    if (structure->tableau == NULL) {
        printf("Allocation echouée\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < structure->taille; i++) {
        structure->tableau[i] = randomNumber();
    }
}

void afficherTableau(Variables *structure) {
    for (int i = 0; i < structure->taille; i++) {
        printf("%d ", structure->tableau[i]);
    }
    printf("\n");
}

void saisirNombreThread(int *nb) {
    printf("Saisir le nombre de threads :\n");
    scanf("%d", nb);
}

void verifierNombreThread(const int nbThread, const int tailleTableau) {
    if (nbThread >= tailleTableau) {
        printf("Le nombre de threads doit être inférieur à la taille du tableau\n");
        exit(EXIT_FAILURE);
    }
}
