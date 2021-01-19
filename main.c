#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "show_scores.h"

#define PRODUCER_SEM_FNAME "/prod_sema"
#define CONSUMER_SEM_FNAME "/cons_sema"

int calculate_max_tours(double total_km);       // Signature de la fonction
void define_session(int argc, char *argv[]);    // Signature de la fonction

int car_number[20] = {44, 77, 16, 5, 33, 23, 55, 4, 3, 31, 10, 26, 11, 18, 7, 99, 20, 8, 63, 6}; //Ensmeble des numéros des voitures dans la course
struct Session current_session;     // Contiendra les paramètres de la session courante

int main(int argc, char *argv[]){
    struct Car *race_car;               //Pointeur vers la structure Car
    int shared_mem_id;                  //ID de la mémoire partagée
    pid_t process_id;                   //ID du processus

    define_session(argc, argv);


    //Création du segment de mémoire patagé
    shared_mem_id = shmget(IPC_PRIVATE, sizeof(struct Car) * 20, IPC_CREAT | 0660);
    if(shared_mem_id == -1){
        write(1, "Error while creating the shared memory segment", sizeof("Error while creating the shared memory segment"));
        exit(-1);
    }


    //On attache la mémoire partagée à la structure Car
    race_car = shmat(shared_mem_id, NULL, 0);
    if(race_car == (void *) (-1)){
        write(1, "Error while attaching the memory segment", sizeof("Eror while attaching the memory segment"));
        exit(-1);
    }

    // On suppimme les sémaphores si ils existent
    sem_unlink(PRODUCER_SEM_FNAME);
    sem_unlink(CONSUMER_SEM_FNAME);

    // On crées et initialise les sémaphores
    sem_t * cons_sema = sem_open(CONSUMER_SEM_FNAME, O_CREAT, 0660, 0);
    if (cons_sema == SEM_FAILED) {
        perror("sem_open/cons_sema");
        exit(EXIT_FAILURE);
    }

    sem_t * prod_sema = sem_open(PRODUCER_SEM_FNAME, O_CREAT, 0660, 1);
    if (prod_sema == SEM_FAILED){
        perror("sem_open/prod_sema");
        exit(EXIT_FAILURE);
    }

    print_previous_ranking(&current_session);

    //Création des processus fils
    int i;
    for( i = 0 ;  i < 20 ; i++ ){
        process_id = fork();
        if(process_id == 0){
            break;
        }
    }

    // Gestion des fonctions en fonction de l'id du processus
    if(process_id == -1){
        //En cas d'erreur du fork
        write(1, "Error while forking", sizeof("Error while forking"));
        exit(-1);
    }
    else if(process_id == 0){
        //Processus enfant
        drive_race_car(&race_car[i], &car_number[i], cons_sema, prod_sema);
        exit(0);
    }
    else{
        //Processus parent
        show_score_table(race_car, cons_sema, prod_sema);

        //Cette boucle permet au programme d'attendre que tous les processus enfants se ferment avant de continuer le programme
        for(int j = 0 ; j < 20 ; j++){
            wait(NULL);
        }

        // On ferme et détruit les sémaphores
        sem_close(cons_sema);
        sem_close(prod_sema);
    }


    //détachement du segment de mémoire partagée
    shmdt(race_car);


    //Déstruction du segment de mémoire partagée
    shmctl(shared_mem_id, IPC_RMID, NULL);

    return 0;
}

/**
 * Paramètrage de la session courante en fonction des arguments entrées en paramètre
 * @param argc : nombre d'arguments entrées par l'utilisateur
 * @param argv : tableau avec les arguments entrées en paramètres
 */
void define_session(int argc, char *argv[]){
    double total_km;    // Variable qui contiendra le total de kilomètres par tour

    // On vérifie si le nombre de paramètres entrées est correcte
    if (argc < 2 || argc > 4){
        write(1, "error: incorrect numbers of arguments, enter [P1, P2, P3, Q1, Q2, Q3, RACE]", sizeof("error: incorrect numbers of arguments, enter [P1, P2, P3, Q1, Q2, Q3, RACE]"));
        exit(-1);
    }
    else if (!strcmp(argv[1], "RACE") && argc == 2){
        write(1, "error: an additional argument is required with 'RACE'", sizeof("error: an additional argument is required with 'RACE'"));
        exit(-1);
    }
    else if (strcmp(argv[1], "RACE") && argc == 3){
        write(1, "error: too many arguments", sizeof("error: too many arguments"));
        exit(-1);
    }

    sprintf(current_session.file_name, "%s.txt", argv[1]);  // On définiti le nom du fichier à enregistrer

    // Paramètreage de la session en fonction des arguments
    if (!strcmp(argv[1], "P1") || !strcmp(argv[1], "P2")) {
        current_session.session_time = 5400;
        current_session.total_cars = 20;
        current_session.maximum_tours = 1000;
		current_session.first_lap = 1;
    }
    else if (!strcmp(argv[1], "P3")){
        current_session.session_time = 3600;
        current_session.total_cars = 20;
        current_session.maximum_tours = 1000;
    }
    else if (!strcmp(argv[1], "Q1")){
        current_session.session_time = 1080;
        current_session.total_cars = 20;
        current_session.maximum_tours = 1000;
    }
    else if (!strcmp(argv[1], "Q2")){
        current_session.session_time = 900;
        current_session.total_cars = 15;
        current_session.maximum_tours = 1000;
    }
    else if (!strcmp(argv[1], "Q3")){
        current_session.session_time = 720;
        current_session.total_cars = 10;
        current_session.maximum_tours = 1000;
    }
    else if (!strcmp(argv[1], "RACE")){
        total_km = atoi(argv[2]);

        if (!total_km){
            write(1, "error: second argument must be an integer", sizeof("error: second argument must be an integer"));
            exit(-1);
        }
        else if (total_km > 7.1 && total_km < 3.2){
            write(1, "error: length of a circuit must be between 3.2 and 7.1 km", sizeof("error: length of a circuit must be between 3.2 and 7.1 km"));
            exit(-1);
        }

        current_session.session_time = 7200;
        current_session.total_cars = 20;
        current_session.maximum_tours = calculate_max_tours(total_km);
    }
    else{
        write(1, "error: invalid first argument, first argument must be in [P1, P2, P3, Q1, Q2, Q3, RACE]", sizeof("error: invalid first argument, first argument must be in [P1, P2, P3, Q1, Q2, Q3, RACE]"));
        exit(-1);
    }
}

/**
 * On caculle le nombre de tours de la course en fonction des nombres de kilomètres par tour.
 * Une course comptera entre 300 et 350 km
 * @param total_km : kilomètres par tour
 * @return : nombre de tours de la course
 */
int calculate_max_tours(double total_km){
    srand(getpid());
    double random_circuit_length = 300 + rand() % 50;

    return (int) round(random_circuit_length / total_km);
}