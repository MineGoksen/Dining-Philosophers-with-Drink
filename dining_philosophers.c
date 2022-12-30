#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <sched.h>
#include <dispatch/dispatch.h>


int filozof_sayisi;
int *stick;
int *kacTaneYedi;
int surahi = 0;
int surahi_bu_tur=0;
int value;

sem_t mutex;
sem_t mutex2;

void *filozofThread(void *);
void *garsonThread();


int main(int argc, char *argv[]) {
	filozof_sayisi = atoi(argv[1]);

	sem_init(&mutex, 0, 1);
   	sem_init(&mutex2, 0, 1);

	int chops[filozof_sayisi];
    stick = chops;
	int porsiyonYedi[filozof_sayisi];
	kacTaneYedi=porsiyonYedi;
    int toplamNeKadarYedi[filozof_sayisi];
    for (int i = 0; i < filozof_sayisi; i++) {
        kacTaneYedi[i] = 0;
        stick[i] = 0;
    }

	if (filozof_sayisi == 0) {
        printf("Please give a valid philosopher number or more than zero as integer ");
        exit(1);
    }
	srand(time(NULL));

    pthread_t filozof[filozof_sayisi];
    pthread_t garson;
    int n1[filozof_sayisi]; 

    for (int i = 0; i < filozof_sayisi; i++) {
            n1[i] = i;
            pthread_create(&filozof[i], NULL, filozofThread, &n1[i]);
    }
    //START GARSON THREADS
    pthread_create(&garson, NULL, garsonThread, NULL);
	while(1){
		sleep(10);
	}
}


void *filozofThread(void *n){
	int tas = 1;
	int me = *(int *) n;
	while(1){


		//do{ // stick kontrolu
			if(tas == 0 && surahi != 0){
				sem_wait(&mutex2);
				tas = 1;
				surahi --;
				sem_post(&mutex2);
			}

			if (stick[me] == 0 && stick[(me + 1) % filozof_sayisi] == 0) {
	            sem_wait(&mutex);
	            stick[me] = 1;
	            stick[(me + 1) % filozof_sayisi] = 1;

	            kacTaneYedi[*(int *) n] += 1;

	            stick[me] = 0;
	            stick[(me + 1) % filozof_sayisi] = 0;
	            tas = 0;
	            sem_post(&mutex);
	        }
		//}while(1);
	}

}

void fonk(){
	printf("O turdaki sürahide ayran sayisi: %d \n", surahi_bu_tur);
	for (int i = 0; i < filozof_sayisi; i++) {
          printf("%d. filozof %d kadar pilav yedi.\n", i, kacTaneYedi[i]);
    }
    printf("\n");
    sleep(5);
}

void *garsonThread() {
    do {
    	if (surahi == 0) {
        	sem_wait(&mutex2);
    		fonk();
            surahi = (rand() % (filozof_sayisi*5)) + 1;
            surahi_bu_tur = surahi;      
        	sem_post(&mutex2);
        }
    } while (1);
}