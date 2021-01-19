//
// Created by antoo on 11-Nov-20.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include "file_management.h"

#ifndef PROJET_2020_SHOW_SCORES_H
#define PROJET_2020_SHOW_SCORES_H

#endif //PROJET_2020_SHOW_SCORES_H

struct BestTimes{
    double best_s1;
    double best_s2;
    double best_s3;
    double best_lap;
    int best_s1_index;
    int best_s2_index;
    int best_s3_index;
    int best_lap_index;
};

void show_score_table(struct Car *race_cars, sem_t * cons_sema, sem_t * prod_sema);
