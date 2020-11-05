#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include "car.h"

#define PRODUCER_FNAME "/display"
#define CONSUMER_FNAME "/car"

int car_number[20] = {44, 77, 16, 5, 33, 23, 55, 4, 3, 31, 10, 26, 11, 18, 7, 99, 20, 8, 63, 6}; //Ensemble des nombres utilisés pour les voitures formule 1

int main(int argc, char *argv[]){
    struct Car *race_car;               //Pointeur vers la structure Car
    struct Session session = {          //Paramétrage de la session actuelle
            .name = "P1",
            .tempsSession = 5400,
            .numberCars = 20
    };
    int shared_mem_id;                  //ID de la mémoire partagée
    pid_t process_id;                   //ID du processus
    sem_t prod_sema;                    //Sémaphore pour le producteur  (voiture)
    sem_t cons_sema;                    //Sémaphore pour le consomateur (afficheur)



    //Création du segment de mémoire patagé
    shared_mem_id = shmget(IPC_PRIVATE, sizeof(struct Car) * session.numberCars, 0666 | IPC_CREAT);
    if(shared_mem_id == -1){
        write(stdout, "Error while creating the shared memory segment", sizeof("Error while creating the shared memory segment"));
        exit(-1)
    }


    //On attache la mémoire partagée à la structure Car
    race_car = shmat(shared_mem_id, NULL, 0);
    if(race_car == -1){
        write(stdout, "Error while attaching the memory segment", sizeof("Eror while attaching the memory segment"));
        exit(-1);
    }


    //Création du sémaphore pour le producteur
    sem_unlink(PRODUCER_FNAME);
    prod_sema = sem_open(PRODUCER_FNAME, IPC_CREAT, 0660, 0);
    if(prod_sema == SEM_FAILED){
        write(stdout, "Error while creating the producer semaphore", sizeof("Error while creating the producer semaphore"));
        exit(-1);
    }


    //Création du sémaphore pour le consomatteur
    sem_unlink(CONSUMER_FNAME);
    cons_sema = sem_open(CONSUMER_FNAME, IPC_CREAT, 0660, 1);
    if(cons_sema == SEM_FAILED){
        write(stdout, "Error while creating the consumer semaphore", sizeof("Error while creating the consumer semaphore"));
        exit(-1);
    }


    //Création des processus fils
    int i = 0;
    for( i = 0 ;  i < session.numberCars ; i++ ){
        process_id = fork();
        if(process_id = fork() == 0){
            break;
        }
    }


    if(process_id == -1){
        //En cas d'erreur du fork
        write(stdout, "Error while forking", sizeof("Error while forking"));
        exit(-1);
    }
    else if(process_id == 0){
        //Processus enfant
        drive_race_car(&race_car[i], &car_number[i], prod_sema, cons_sema);
        exit(0);
    }
    else{
        //Processus parent
        show_score_table(car, prod_sema, cons_sema);

        //Cette boucle permet au programme d'attendre que tous les processus enfants se ferment avant de conrinuer le programme
        for(int j = 0 ; j < session.numberCars ; j++){
            wait(NULL);
        }
    }


    //détachement du segment de mémoire partagée
    shmdt(race_car);


    //Déstruction du segment de mémoire partagée
    shmctl(shared_mem_id, IPC_RMID, NULL);

    return 0;
}