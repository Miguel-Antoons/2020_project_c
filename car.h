//
// Created by miguel on 2/11/20.
//
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#ifndef PROJET_2020_CAR_H
#define PROJET_2020_CAR_H

#endif //PROJET_2020_CAR_H

struct Car {
    int idCar;
    double s1;
    double s2;
    double s3;
    double totalLap;
    int lap;
    // best time
    double bestS1;
    double bestS2;
    double bestS3;
    double bestLap;
    double total_time;
    //stands, out
    int tire_lifeTime;
    int out;
};

struct Session{
    char[10] file_name;
    double session_time;
    int total_cars;
    int maximum_tours;
};

void drive_race_car(struct Car *car, const int *carNum, sem_t *prod_sema, sem_t *cons_sema);