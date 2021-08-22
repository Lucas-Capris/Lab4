#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 4

// Variáveis globais
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

// Thread 1
void *thread1 (void *t) {
    pthread_mutex_lock(&x_mutex);
    
    if (x == 0) {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    x++;
    printf("Fique a vontade.\n");
    pthread_cond_signal(&x_cond);

    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

// Thread 2
void *thread2 (void *t) {
    pthread_mutex_lock(&x_mutex);

    x++;
    printf("Seja bem-vindo!\n");
    pthread_cond_broadcast(&x_cond);
  
    pthread_mutex_unlock(&x_mutex); 
    pthread_exit(NULL);
}

// Thread 3
void *thread3 (void *t) {
    pthread_mutex_lock(&x_mutex);

    while (x < 3) {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf("Volte sempre!\n");
    
    pthread_mutex_unlock(&x_mutex); 
    pthread_exit(NULL);
}

// Thread 4
void *thread4 (void *t) {
    pthread_mutex_lock(&x_mutex);
    
    if (x == 0) {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    x++;
    printf("Sente-se por favor.\n");
    pthread_cond_signal(&x_cond);

    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[NTHREADS];

  // Inicialização do mutex e da variável de condição
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);

  // Criação das threads
  pthread_create(&threads[0], NULL, thread1, NULL);
  pthread_create(&threads[1], NULL, thread2, NULL);
  pthread_create(&threads[2], NULL, thread3, NULL);
  pthread_create(&threads[3], NULL, thread4, NULL);

  // Espera todas as threads completarem
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  // Desalocação de variáveis
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);
}
