//
// Created by antoo on 11-Nov-20.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include "car.h"
#include "file_management.h"

#ifndef PROJET_2020_SHOW_SCORES_H
#define PROJET_2020_SHOW_SCORES_H

#endif //PROJET_2020_SHOW_SCORES_H

struct BestTimes{
    int best_s1;
    int best_s2;
    int best_s3;
    int best_lap;
};

void show_score_table(struct Car *race_cars, sem_t *prod_sema, sem_t *cons_sema);
