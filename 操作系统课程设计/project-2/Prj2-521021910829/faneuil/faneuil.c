#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// semaphore
sem_t nojudgeIN;
sem_t confirmed;
sem_t allsigned;
sem_t mutex;

// counter
int judgein = 0;
int immigrantcount = 0;
int judgecount = 0;
int spectatorcount = 0;

int entered = 0;
int checked = 0;

void* immigrant(){
    while (1)
    {
        sem_wait(&nojudgeIN);// before judge to get in
        immigrantcount++;    
        sleep(rand()%3+1);
        printf("Immigrant #%d enter\n", immigrantcount);
        entered++;
        sem_post(&nojudgeIN);

        sem_wait(&mutex);// wait for mutex to check
        sleep(rand()%3+1);
        printf("Immigrant #%d checkIn\n", immigrantcount);
        // sitdown
        sleep(rand()%3+1);
        printf("Immigrant #%d sitDown\n", immigrantcount);
        checked++;
        // if all ready, signal allsigned, else release mutex
        if(judgein == 1 && entered == checked){
            sem_post(&allsigned);
        }
        else{
            sem_post(&mutex);
        }
    
        sem_wait(&confirmed);// wait to be confirmed
        sleep(rand()%3+1);
        printf("Immigrant #%d getCertificate\n", immigrantcount);

        sem_wait(&nojudgeIN);// wait for judge to get out
        sleep(rand()%3+1);
        printf("Immigrant #%d leave\n", immigrantcount);
        sem_post(&nojudgeIN);
    }
}

void* judge(){
    while (1)
    {
        sem_wait(&nojudgeIN);// prevent starvation
        sem_wait(&mutex);
        judgein = 1;
        judgecount++;
        sleep(rand()%3+1);
        printf("Judge #%d enter\n", judgecount);
        if(entered > checked){
            sem_post(&mutex);
            sem_wait(&allsigned);// all checked, began confirmation
        }

        if(checked != 0){
            sleep(rand()%3+1);
            printf("Judge #%d confirm the immigrant #%d\n", judgecount, immigrantcount);
            checked--;
            entered--;
            sem_post(&confirmed);
        }
        sleep(rand()%3+1);
        printf("Judge #%d leave\n", judgecount);
        judgein = 0;

        sem_post(&mutex);
        sem_post(&nojudgeIN);
    }
}

void* spectator(){
    while (1)
    {
        sem_wait(&nojudgeIN);
        spectatorcount++;
        sleep(rand()%3+1);
        printf("Spectator #%d enter\n", spectatorcount);
        sem_post(&nojudgeIN);

        sleep(rand()%3+1);
        printf("Spectator #%d spectate\n", spectatorcount);
        sleep(rand()%3+1);
        printf("Spectator #%d leave\n", spectatorcount);
    }
    
}

int main(int argc, char *argv[]){
    pthread_t itid;// immigrant
    pthread_t jtid;// judge
    pthread_t stid;// spectator

    // nitializing the semaphores
    sem_init(&nojudgeIN, 0, 1);
    sem_init(&confirmed, 0, 0);
    sem_init(&allsigned, 0, 0);
    sem_init(&mutex, 0, 1);

    printf("Begin run\n");
    pthread_create(&itid, NULL, immigrant, NULL);
    pthread_create(&jtid, NULL, judge, NULL);
    pthread_create(&stid, NULL, spectator, NULL);

    pthread_join(itid,NULL);
    pthread_join(jtid,NULL);
    pthread_join(stid,NULL);

    sem_destroy(&nojudgeIN);
    sem_destroy(&confirmed);
    sem_destroy(&allsigned);
    sem_destroy(&mutex);

    printf("End run\n");
    return 0;
}