#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5
#define PENSANDO 2
#define HAMBRIENTO 1
#define COMIENDO 0
#define IZQUIERDA (num_filosofo + 4) % NUM_FILOSOFOS
#define DERECHA (num_filosofo + 1) % NUM_FILOSOFOS

int estado[NUM_FILOSOFOS];
int filosofos[NUM_FILOSOFOS];
sem_t mutex;
sem_t S[NUM_FILOSOFOS];

void test(int num_filosofo) {
    if (estado[num_filosofo] == HAMBRIENTO && estado[IZQUIERDA] != COMIENDO && estado[DERECHA] != COMIENDO) {
        estado[num_filosofo] = COMIENDO;
        sleep(2);
        printf("El filosofo %d toma tenedor %d y %d\n", num_filosofo + 1, IZQUIERDA + 1, num_filosofo + 1);
        printf("El filosofo %d esta comiendo\n", num_filosofo + 1);
        sem_post(&S[num_filosofo]);
    }
}

void toma_tenedor(int num_filosofo) {
    sem_wait(&mutex);
    estado[num_filosofo] = HAMBRIENTO;
    printf("El filosofo %d tiene hambre\n", num_filosofo + 1);
    test(num_filosofo);
    sem_post(&mutex);
    sem_wait(&S[num_filosofo]);
    sleep(1);
}

void deja_tenedor(int num_filosofo) {
    sem_wait(&mutex);
    estado[num_filosofo] = PENSANDO;
    printf("El filosofo %d deja tenedor %d y %d\n", num_filosofo + 1, IZQUIERDA + 1, num_filosofo + 1);
    printf("El filosofo %d esta pensando\n", num_filosofo + 1);
    test(IZQUIERDA);
    test(DERECHA);
    sem_post(&mutex);
}

void* filosofo(void* num) {
    while (1) {
        int* i = num;
        sleep(1);
        toma_tenedor(*i);
        sleep(0);
        deja_tenedor(*i);
    }
}

int main() {
    int i;
    pthread_t thread_id[NUM_FILOSOFOS];
    sem_init(&mutex, 0, 1);
    for (i = 0; i < NUM_FILOSOFOS; i++)
        sem_init(&S[i], 0, 0);
    for (i = 0; i < NUM_FILOSOFOS; i++) {
        filosofos[i] = i;
        pthread_create(&thread_id[i], NULL, filosofo, &filosofos[i]);
        printf("El filosofo %d esta pensando\n", i + 1);
    }
    for (i = 0; i < NUM_FILOSOFOS; i++)
        pthread_join(thread_id[i], NULL);
}