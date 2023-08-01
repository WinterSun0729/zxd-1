#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int process_need = 100;//the num of seeds we have

//semaphore
sem_t shovel;
sem_t empty;
sem_t seeded;
sem_t unfilled;

//counter
int MAX;
int dignum = 1;
int seednum = 1;
int fillnum = 1;

void *larry(){
    while(dignum <= process_need){
        sem_wait(&unfilled);
        sem_wait(&shovel);
        printf("Larry digs another hole #%i.\n",dignum++);
        sem_post(&shovel);
        sem_post(&empty);
    }
}
void *moe(){
    while(seednum <= process_need){
        sem_wait(&empty);
        printf("Moe plants a seed in a hole #%i.\n",seednum++);
        sem_post(&seeded);
    }
}
void *curly(){
    while(fillnum <= process_need){
        sem_wait(&seeded);
        sem_wait(&shovel);
        printf("Curly fills a planted hole #%i.\n",fillnum++);
        sem_post(&shovel);
        sem_post(&unfilled);
    }
}

int main(int argc, char *argv[]){
    if(argc < 2){//parameters detection
        printf("Command Error\nCommand:./LCM <num_of_unfilled_holes> <(num_of_max_seeds)>\n");
        return -1;
    }
    MAX = atoi(argv[1]);
    process_need = atoi(argv[2]);
    printf("Maximum number of unfilled holes: %d\n",MAX);

    pthread_t ltid;//Larry
    pthread_t mtid;//Moe
    pthread_t ctid;//Curly

    //initializing the semaphores
    sem_init(&shovel, 0, 1);
    sem_init(&empty, 0, 0);
    sem_init(&seeded, 0, 0);
    sem_init(&unfilled, 0, MAX);

    printf("Begin run\n");
    pthread_create(&ltid, NULL, larry, NULL);  //create the larry thread
    pthread_create(&mtid, NULL, moe, NULL);  //create the moe thread
    pthread_create(&ctid, NULL, curly, NULL);  //create the curly thread

    pthread_join(ltid,NULL);
    pthread_join(mtid,NULL);
    pthread_join(ctid,NULL);

    sem_destroy(&shovel);
    sem_destroy(&empty);
    sem_destroy(&seeded);
    sem_destroy(&unfilled);

    printf("End run\n");
    return 0;
}