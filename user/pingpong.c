#include "user/user.h"

int main(int argc, char *argv[]) {
    int tubo1[2], tubo2[2];
    char buffer;

    if (pipe(tubo1) < 0 || pipe(tubo2) < 0) {
        printf(2, "Erro: falha ao criar tubo\n");
        exit(1);
    }

    int pid = fork();
    if (pid < 0) {
        printf(2, "Erro: falha ao criar processo filho\n");
        exit(1);
    }

    if (pid == 0) {
        close(tubo1[1]);
        close(tubo2[0]);

        read(tubo1[0], &buffer, 1);
        printf(1, "%d: recebeu ping\n", getpid());

        write(tubo2[1], &buffer, 1);

        close(tubo1[0]);
        close(tubo2[1]);
        exit(0);
    } else {
        close(tubo1[0]);
        close(tubo2[1]);

        write(tubo1[1], "x", 1);
        read(tubo2[0], &buffer, 1);
        printf(1, "%d: recebeu pong\n", getpid());

        close(tubo1[1]);
        close(tubo2[0]);
        wait(0);
        exit(0);
    }
}