#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"  // Corrigido para user/user.h

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(2, "Usage: sleep <ticks>\n");  // fd=2 (stderr)
        exit(1);
    }

    int ticks = atoi(argv[1]);
    if (ticks <= 0) {
        printf(2, "Error: ticks must be a positive integer.\n");
        exit(1);
    }

    sleep(ticks);
    exit(0);
}