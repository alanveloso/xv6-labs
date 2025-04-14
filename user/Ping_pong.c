ping pong

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


volatile int turno = 0;


pthread_mutex_t mutex;


pthread_cond_t cond_ping;
pthread_cond_t cond_pong;


void *ping(void *arg) {
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);
        while (turno != 0) {
            pthread_cond_wait(&cond_ping, &mutex);
        }
        printf("PING\n");
        turno = 1;
        pthread_cond_signal(&cond_pong);
        pthread_mutex_unlock(&mutex);
        usleep(500000);
    }
    return NULL;
}


void *pong(void *arg) {
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);
        while (turno != 1) {
            pthread_cond_wait(&cond_pong, &mutex);
        }
        printf("  PONG\n");
        turno = 0;
        pthread_cond_signal(&cond_ping);
        pthread_mutex_unlock(&mutex);
        usleep(500000);
    }
    return NULL;
}

int main() {
    pthread_t thread_ping, thread_pong;


    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Erro ao inicializar o mutex");
        return 1;
    }
    if (pthread_cond_init(&cond_ping, NULL) != 0) {
        perror("Erro ao inicializar a condição cond_ping");
        pthread_mutex_destroy(&mutex);
        return 1;
    }
    if (pthread_cond_init(&cond_pong, NULL) != 0) {
        perror("Erro ao inicializar a condição cond_pong");
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond_ping);
        return 1;
    }


    if (pthread_create(&thread_ping, NULL, ping, NULL) != 0) {
        perror("Erro ao criar a thread PING");
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond_ping);
        pthread_cond_destroy(&cond_pong);
        return 1;
    }

    if (pthread_create(&thread_pong, NULL, pong, NULL) != 0) {
        perror("Erro ao criar a thread PONG");
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond_ping);
        pthread_cond_destroy(&cond_pong);
        pthread_cancel(thread_ping);
        return 1;
    }


    if (pthread_join(thread_ping, NULL) != 0) {
        perror("Erro ao esperar pela thread PING");
    }
    if (pthread_join(thread_pong, NULL) != 0) {
        perror("Erro ao esperar pela thread PONG");
    }


    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_ping);
    pthread_cond_destroy(&cond_pong);

    return 0;
}
