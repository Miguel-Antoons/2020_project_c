//
// Created by miguel on 2/11/20.
//
#include "car.h"

struct Session current_session;

/**
 * Chance pour la voiture ait un crash
 * si le nombre aléatoire vaut 1 alors elle est out
 */
void crashProbality(struct Car *car, sem_t *prod_sema){
    if(rand() % 5000 == 1){
        car -> crashed = 1;
        sem_post(prod_sema);
        exit(0);
    }
}


/**
 * @return un nombre aléatoire entre 20 et 25
 */
int stand_time(){
    int min_time = 20;
    return min_time + rand() % 5;
}

/**
 * Chance pour que la voiture aille au stand
 * La résistance de pneu (5000 - 6000) - un nombre random entre 0 et 250 pour chaque tour
 * si la résistance des pneu est égal à 0, la voiture va au stand, remet des nouveaux pneus
 * on ajoute un nombre aléatoire (20-25) au s3
 */
void standProbality(struct Car *car){
    car -> tire_lifeTime = car -> tire_lifeTime - (200 + rand() % 50);
    if (car -> tire_lifeTime <= 0){
        car -> tire_lifeTime = 5000 + rand() % 1000;
        car -> pit++;
        car -> s3 += stand_time();
    }
}

/**
 * @return nombre random entre 35 et 50 seconde pour chaque secteur
 */
float timeSector(){
    int min = 35;
    int max = 49;
    float scale = rand() / (float)RAND_MAX;     // [0, 1.0]
    return (float) min + rand() % (max - min) + scale;  // [min, max]
}

/**
 * Point d'entrée du processus fils
 * @param car : une partie de la mémoire partagée
 * @param carNum : numéro unique de la voiture
 * @param prod_sema : sémaphore du producteur (processus fils)
 * @param cons_sema : sémaphore du consommateur (processus père)
 */
void drive_race_car(struct Car *car, const int *carNum, sem_t * cons_sema, sem_t * prod_sema){
    srand(getpid());
    car -> idCar = *carNum;
    car -> tire_lifeTime = 5000 + rand() % 1000;

    // on reagerde si la voiture peut participer à la course
    for (int i = 0 ; i < 20 ; i++){
        if (current_session.driving_cars[i] == *carNum){
            exit(0);
        }
    }

    while (car -> total_time < current_session.session_time || car -> lap <= current_session.maximum_tours){
        sem_wait(cons_sema);
        //secteur 1
        car -> s1 = timeSector();
        if (car -> bestS1 == 0 || car -> bestS1 > car -> s1){
            car -> bestS1 = car -> s1;
        }

        crashProbality(car, prod_sema);

        //secteur 2
        car -> s2 = timeSector();
        if (car -> bestS2 == 0 || car -> bestS1 > car -> s2){
            car -> bestS2 = car -> s2;
        }
        crashProbality(car, prod_sema);

        //secteur 3
        car -> s3 = timeSector();
        standProbality(car);
        if (car -> bestS3 == 0 || car -> bestS3 > car -> s3){
            car -> bestS3 = car -> s3;
        }

        // temps du tour
        car -> totalLap = car -> s1 + car -> s2 + car -> s3;

        // meilleur tour
        if(car -> totalLap < car -> bestLap || car -> bestLap == 0){
            car -> bestLap = car -> totalLap;
        }

        //temps total
        car -> total_time += car -> totalLap;

        //nombre de tours
        car -> lap ++;
        crashProbality(car, prod_sema);
        if (car -> total_time >= current_session.session_time || car -> lap == current_session.maximum_tours){
            car -> finished = 1;
            sem_post(prod_sema);
            exit(0);
        }
        sem_post(prod_sema);
    }

}

