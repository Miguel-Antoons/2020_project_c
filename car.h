//
// Created by miguel on 2/11/20.
//
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
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
    char name;
    double tempsSession;
    int numberCars;
};