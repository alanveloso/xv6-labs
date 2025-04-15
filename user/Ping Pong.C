include <stdio.h>
include <stdlib.h>
include <unistd.h>
include <string.h>

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    char ball[] = "ping";

    pipe(pipe1); // Pai para filho
    pipe(pipe2); // Filho para pai

    pid = fork();

    if (pid == 0) {
        close(pipe1[1]);
        close(pipe2[0]);

        while (1) {
            read(pipe1[0], ball, sizeof(ball));
            printf("Filho recebeu: %s\n", ball);
            sleep(1);
            strcpy(ball, "pong");
            write(pipe2[1], ball, sizeof(ball));
        }
    } else {
        close(pipe1[0]);
        close(pipe2[1]);

        write(pipe1[1], ball, sizeof(ball));

        while (1) {
            read(pipe2[0], ball, sizeof(ball));
            printf("Pai recebeu: %s\n", ball);
            sleep(1);
            strcpy(ball, "ping");
            write(pipe1[1], ball, sizeof(ball));
        }
    }

    return 0;
}

