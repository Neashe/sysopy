//
// Created by Natii on 15.05.2023.
//

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define ELF_NUMBER 10
#define REINDEER_NUMBER 9
#define MAX_QUEUE_SIZE_ELF 3
#define PRESENTS_TO_DELIVER 3

//threads, cond, mutex
static pthread_t santa;
static pthread_t elves[ELF_NUMBER];
static pthread_t reindeers[REINDEER_NUMBER];
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t santa_cond = PTHREAD_COND_INITIALIZER;
static pthread_cond_t elves_cond = PTHREAD_COND_INITIALIZER;
static pthread_cond_t reindeers_cond = PTHREAD_COND_INITIALIZER;

int waiting_elves = 0;
int waiting_reindeers = 0;
int elves_id[MAX_QUEUE_SIZE_ELF];

int random_number(int lower, int upper){
    int num = (rand() % (upper - lower+1)) + lower;
    return num;

}

void *elf_routine(void *args){

    int elf_id = (int)(intptr_t)(args);
    while(1){
        sleep(random_number(2, 5));
        pthread_mutex_lock(&mutex);
        if (waiting_elves<3){
            elves_id[waiting_elves] = elf_id;
            waiting_elves++;
            printf("Elf: czeka %d elfów na Mikołaja, ID: %d\n",waiting_elves,elf_id);
            if (waiting_elves == 3){
                printf("Elf: wybudzam Mikołaja, ID: %d\n",elf_id);
                pthread_cond_signal(&santa_cond);
            }
            pthread_cond_wait(&elves_cond,&mutex);
        }
        else{
            printf("Elf: samodzielnie rozwiązuję swój problem, ID: %d\n",elf_id);

        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *santa_routine(void *arg) {
    int presents_delivered = 0;
    while (presents_delivered < PRESENTS_TO_DELIVER) {
        pthread_mutex_lock(&mutex);
        while (1) {
            pthread_cond_wait(&santa_cond, &mutex);
            if (waiting_elves == 3 || waiting_reindeers == 9) {
                printf("Mikołaj: budzę się\n");
                break;
            } else {
                perror("Mikołaj: zostaje błędnie wybudzony\n");
            }
        }
        if (waiting_elves == 3) {
            printf("Mikołaj: rozwiązuję problemy elfów %d %d %d\n",
                   elves_id[0],
                   elves_id[1],
                   elves_id[2]
            );
            sleep(random_number(1, 2));
            waiting_elves = 0;
            pthread_cond_broadcast(&elves_cond);
        }
        if (waiting_reindeers == 9) {
            printf("Mikołaj: dostarczam zabawki\n");
            sleep(rand() % 3 + 2);
            ++presents_delivered;
            waiting_reindeers = 0;
            pthread_cond_broadcast(&reindeers_cond);
        }
        printf("Mikołaj: zasypiam\n");
        pthread_mutex_unlock(&mutex);
    }

    for (int i = 0; i < ELF_NUMBER; i++) {
        pthread_cancel(elves[i]);
    }
    for (int i = 0; i < REINDEER_NUMBER; i++) {
        pthread_cancel(reindeers[i]);
    }
    exit(EXIT_SUCCESS);

}
void *reindeer_routine(void * args){

    int reindeer_id = (int)(intptr_t)(args);
    while (1){
        sleep(random_number(5, 10));
        pthread_mutex_lock(&mutex);
        waiting_reindeers++;
        printf("Renifer: czeka %d reniferów na Mikołaja, ID: %d\n",waiting_reindeers,reindeer_id);

        if (waiting_reindeers == 9){
            printf("Renifer: wybudzam Mikołaja, ID: %d\n",reindeer_id);
            pthread_cond_signal(&santa_cond);
        }
        pthread_cond_wait(&reindeers_cond,&mutex);
        pthread_mutex_unlock(&mutex);

    }
}

int main(){
    srand(time(NULL));
    if (pthread_create(&santa,NULL, &santa_routine,NULL) != 0){
        perror("Failed to create santa thread\n");
    }
    for (intptr_t i = 0;i<ELF_NUMBER;i++){
        if (pthread_create(&elves[i], NULL, &elf_routine, (void*)i) != 0){
            perror("Failed to create elf threads\n");
        }
    }
    for (intptr_t i = 0; i<REINDEER_NUMBER;i++){
        if (pthread_create(&reindeers[i],NULL, &reindeer_routine,(void*)i) != 0){
            perror("Failed to create reindeer threads\n");
        }
    }
    if (pthread_join(santa,NULL) != 0){
        perror("Failed to join santa thread\n");
    }

    return 0;
}



