#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int x = 0, n, t_buffer, t_buffer_c;
int *buffer;
sem_t cheio;
sem_t vazio;
sem_t mutex;

void *produtor(void*);
void *consumidor(void*);

int main (){
        int p, c;
        scanf("%d %d %d %d", &p, &c, &n, &t_buffer);
        int id_produtor[p], id_consumidor[c];

        pthread_t produtores[p], consumidores[c];

        buffer = (int *)malloc(t_buffer* sizeof(int));
        for (int i = 0; i < t_buffer; i++){
                buffer[i] = 0;
        }

        sem_init(&cheio, 0, t_buffer);
        sem_init(&vazio, 0, 0);
        sem_init(&mutex, 0, 1);

        for (int i = 0; i < p; i++){
                id_produtor[i] = i;
                pthread_create(&produtores[i], NULL, produtor, &id_produtor[i]);
        }

        for (int i = 0; i < c; i++){
                id_consumidor[i] = i;
                pthread_create(&consumidores[i], NULL, consumidor, &id_consumidor[i]);
        }

        for (int i = 0; i < p; i++){
                pthread_join(produtores[i], NULL);
        }

        for (int i = 0; i < c; i++){
                pthread_join(consumidores[i], NULL);
        }

        return 0;
}

void *produtor(void* args){
        int *id_produtor = (int *) args;

        while (1){
                sem_wait(&vazio);
                sem_wait(&mutex);

                if (buffer[t_buffer] == 0){
                        buffer[t_buffer] = 2 * x + 1;
                        printf("Produtor %d produzindo %d na posição %d", *id_produtor, buffer[t_buffer], t_buffer);
                        x++;
                        t_buffer++;
                }

                if (x > n){
                        x = 0;
                }

                sem_post(&mutex);
                sem_post(&cheio);
        }

}

void *consumidor(void* args){
        int *id_consumidor = (int *) args;

        while (1){
                sem_wait(&cheio);
                sem_wait(&mutex);

                if (buffer[t_buffer] != 0){
                        printf("Consumidor %d consumindo %d da posição %d", *id_consumidor, buffer[t_buffer], t_buffer_c);
                        buffer[t_buffer] = 0;
                }

                sem_post(&mutex);
                sem_post(&vazio);

        }

}
