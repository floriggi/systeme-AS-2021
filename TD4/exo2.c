#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int pid;

void lirePid() {
    printf("Saisir un PID\n");
    scanf("%d", &pid);
}

void envoyerSignal(const int signal) {
    printf("Envoi du signal %d\n", signal);
    kill(pid, signal);
}

int main(int argc, char const *argv[]) {
    lirePid();

    for (int signal = 0; signal < NSIG; signal++) {
        if (signal != 9) {
           envoyerSignal(signal);
        }
        sleep(1);
    }

    // ceci pour tuer l'exercice 1
    envoyerSignal(9);

    return EXIT_SUCCESS;
}
