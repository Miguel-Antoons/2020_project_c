//
// Created by antoo on 11-Nov-20.
//

#include "show_scores.h"

struct Session current_session;
struct BestTimes best_times;

int sort_cars_by_time(const void *a, const void *b){
    const struct Car *position_1 = (struct Car *) a;
    const struct Car *position_2 = (struct Car *) b;

    if (position_1->bestLap > position_2->bestLap){
        return 1;
    }
    else if (position_1->bestLap < position_2->bestLap){
        return -1;
    }
    else {
        return 0;
    }
}

int set_best_times(struct Car *race_cars){
    for(int i = 0 ; i < current_session.total_cars ; i++){
        if (best_times.best_lap == 0 || best_times.best_lap > race_cars[i].bestLap){
            best_times.best_lap = i;
        }
        if (best_times.best_s1 == 0 || best_times.best_s1 > race_cars[i].bestS1){
            best_times.best_s1 = i;
        }
        if (best_times.best_s2 == 0 || best_times.best_s2 > race_cars[i].bestS2){
            best_times.best_s2 = i;
        }
        if (best_times.best_s3 == 0 || best_times.best_s3 > race_cars[i].bestS3){
            best_times.best_s3 = i;
        }
    }

}

void build_table(struct Car *race_copy[20]){
    set_best_times(*race_copy);
    system("clear");
    printf("|\tPos.\t|%10s\t|%10s\t|%10s\t|%10s\t|%10s\t|%10s\t|%10s\t|10%s\t|\n\n", "Nr", "S1", "S2", "S3", "Lap Time", "Lab Nr", "Pit", "OUT");

    for(int i = 0 ; i < current_session.total_cars ; i++){
        struct Car single_car = *race_copy[i];

        printf("|\t%d\t|%10d\t|%10.3f\t|%10.3f\t|%10.3f\t|%10.3f\t|%10d\t|%10d\t|%10d\t|\n", i + 1, single_car.idCar, single_car.s1, single_car.s2, single_car.s3, single_car.totalLap, single_car.lap, single_car.pit, single_car.out);
    }
    printf("\n Best Sector 1 : %d [%.3f]\t", race_copy[best_times.best_s1]->idCar, race_copy[best_times.best_s1]->bestS1);
    printf("\n Best Sector 2 : %d [%.3f]\t", race_copy[best_times.best_s2]->idCar, race_copy[best_times.best_s2]->bestS2);
    printf("\n Best Sector 3 : %d [%.3f]\t", race_copy[best_times.best_s3]->idCar, race_copy[best_times.best_s3]->bestS3);
    printf("\n Best Lap : %d [%.3f]\t", race_copy[best_times.best_lap]->idCar, race_copy[best_times.best_lap]->bestLap);

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