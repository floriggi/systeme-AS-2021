#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void erreur(const char *message) {
    printf("Erreur durant : %s\n", message);
    exit(EXIT_FAILURE);
}

void lireMessage(char tampon[]) {
    printf("Saisir un message à envoyer :\n");
    fgets(tampon, 99, stdin);
}

void ouvrirTube(int tube[]) {
    if (pipe(tube) == -1) {
        erreur("ouverture tube");
    }
}

int main(int argc, char const *argv[]) {
    int pid;
    int tubeVersFils[2];
    int tubeVersPere[2];
    char tampon[100];

    ouvrirTube(tubeVersFils);
    ouvrirTube(tubeVersPere);

    pid = fork();

    if (pid == -1) {
        erreur("fork");
    } else if (pid == 0) {
        //fils
        close(tubeVersFils[1]);
        close(tubeVersPere[0]);
        printf("Je le fils, mon pid = %d\n", getpid());

        read(tubeVersFils[0], tampon, 100);
        printf("Je suis le fils, j'ai recu : %s\n", tampon);

        sleep(1);

        printf("Je suis le fils, j'envoie %s\n", tampon);
        write(tubeVersPere[1], tampon, strlen(tampon) + 1);

        close(tubeVersFils[0]);
        close(tubeVersPere[1]);

        exit(EXIT_SUCCESS);
    } else {
        //père
        sleep(1);

        close(tubeVersFils[0]);
        close(tubeVersPere[1]);

        lireMessage(tampon);
        //tampon[99] = 0; // inutile ?

        write(tubeVersFils[1], tampon, strlen(tampon) + 1);

        read(tubeVersPere[0], tampon, 100);
        printf("Je suis le père, j'ai recu : %s\n", tampon);

        wait(NULL);

        close(tubeVersFils[1]);
        close(tubeVersPere[0]);
    }

    return EXIT_SUCCESS;
}
