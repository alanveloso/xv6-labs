#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int turn = 0; // 0 = Ping, 1 = Pong

void* ping(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);
        while (turn != 0)
            pthread_cond_wait(&cond, &lock);
        printf("Ping\n");
        turn = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

void* pong(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);
        while (turn != 1)
            pthread_cond_wait(&cond, &lock);
        printf("Pong\n");
        turn = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, ping, NULL);
    pthread_create(&t2, NULL, pong, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
