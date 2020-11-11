//
// Created by miguel on 2/11/20.
//

#ifndef PROJET_2020_CAR_H
#define PROJET_2020_CAR_H

#endif //PROJET_2020_CAR_H

struct Car {
    int idCar;
    double s1;
    double s2;
    double s3;
    double totalLap;
    // best time
    double bestS1;
    double bestS2;
    double bestS3;
    double BestLap;
    //stands, out
    int stand;
    int out;
};

struct Session{
    char[10] file_name;
    double session_time;
    int total_cars;
    int maximum_tours;
};