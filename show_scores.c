//
// Created by antoo on 11-Nov-20.
//

#include "show_scores.h"

struct Session current_session;

int sort_cars_by_time(const void *a, const void *b){
    const struct Car *position_1 = (struct Car *) a;
    const struct Car *position_2 = (struct Car *) b;

    if (position_1->bestLap > position_2->bestLap){
        return 1;
    }
    else if (position_1->bestLap > position_2->bestLap){
        return -1;
    }
    else {
        return 0;
    }
}

void build_table(struct Car *race_copy[20]){

}

void show_score_table(struct Car *race_cars, sem_t *prod_sema, sem_t *cons_sema){
    struct Car *race_copy[20];
    while (1){
        sem_wait(prod_sema);
        memcpy(race_copy, race_cars, sizeof(struct Car) * current_session.total_cars);
        sem_post(cons_sema);

        qsort(race_copy, current_session.total_cars, sizeof(struct Car), sort_cars_by_time);

        build_table(race_copy);

        if (race_copy[current_session.total_cars - 1]->out){
            break;
        }
    }
}