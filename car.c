//
// Created by miguel on 2/11/20.
//
#include "car.h"

struct Session current_session;

/**
 * Chance pour la voiture ait un crash
 * si le nombre aléatoire vaut 1 alors elle est out
 */
void crashProbality(struct Car *car){
    if(rand() % 500 == 1){
        car -> out = 1;
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
 * on ajoute un noombre aléatoire (20-25) au s3
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
int timeSector(){
    int min = 35;
    int max = 50;
    return min + rand() % (max - min);
}


void drive_race_car(struct Car *car, const int *carNum, sem_t *prod_sema, sem_t *cons_sema){
    /**
     * défini le pid comme la "graine" du random
     */
    srand(getpid());
    car -> idCar = *carNum;
    car -> tire_lifeTime = 5000 + rand() % 1000;


    while (car -> total_time < current_session.session_time || car -> lap < current_session.maximum_tours){
        sem_wait(cons_sema);
        //secteur 1
        car -> s1 = timeSector();
        if (car -> bestS1 == 0 || car -> bestS1 > car -> s1){
            car -> bestS1 = car -> s1;
        }
        crashProbality(car);

        //secteur 2
        car -> s2 = timeSector();
        if (car -> bestS2 == 0 || car -> bestS1 > car -> s2){
            car -> bestS2 = car -> s2;
        }
        crashProbality(car);

        //secteur 3
        car -> s3 = timeSector();
        standProbality(car);
        if (car -> bestS3 == 0 || car -> bestS3 > car -> s3){
            car -> bestS3 = car -> s3;
        }
        crashProbality(car);

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
        sem_post(prod_sema);
    }

}

