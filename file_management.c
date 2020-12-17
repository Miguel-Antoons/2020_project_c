//
// Created by antoo on 11-Nov-20.
//

#include "file_management.h"

void writeClassement(struct Car *race_copy, struct Session current_session){
	FILE* file = fopen(current_session.file_name, "w");
	
	if (file != NULL){
	    for(int i = 0; i < current_session.total_cars; i++){
	        fprintf(file, "%d\n", race_copy[i].idCar);
	    }
            fclose(file);
	}
}


void print_previous_ranking(struct Car *race_copy, struct Session current_session){
	char *string_to_read;
	
	int numeroCar[current_session.total_cars]; //On vide le tableau
    char chaine[5] = "";
    int i;
	FILE* file;


	if(!strcmp(current_session.file_name, "Q2.txt")){
		file = fopen("Q1.txt", "r");
	}
	else if(!strcmp(current_session.file_name, "Q3.txt")){
		file = fopen("Q2.txt", "r");
	}
	else if(!strcmp(current_session.file_name, "RACE.txt")){
		file = fopen("Q3.txt", "r");
	}
	else{file = NULL;}
	
	if(file != NULL){
        i=0;

        while(fgets(chaine, 5, file)){
			numeroCar[i] = atoi(chaine);
            i++;
		}

        if(!strcmp(current_session.file_name, "RACE.txt")) {
            printf("|\tPos.\t|%5s\t|%10s\t|%10s\t|%10s\t|%10s\t|%7s\t|%5s\t|%5s\t|%10s\t|\n\n", "Nr", "S1", "S2", "S3",
                   "Lap Time", "Lap Nr", "Pit", "CRASH", "FINISHED");

            int u;
            int position;
            position = 0;
            for (u = 0; u < current_session.total_cars - 10; u++) {
                printf("|\t%d\t|%5d\t|%10.3f\t|%10.3f\t|%10.3f\t|%10.3f\t|%7d\t|%5d\t|%5d\t|%10d\t|\n", position + 1,
                       numeroCar[u], 0.000, 0.000, 0.000, 0.000, 0, 0, 0, 0);
                position++;
            }
            printf("\n Best Sector 1 : %d [%.3f]\t", 0, 0.000);
            printf("Best Sector 2 : %d [%.3f]\t", 0, 0.000);
            printf("Best Sector 3 : %d [%.3f]\t", 0, 0.000);
            printf("Best Lap : %d [%.3f]\t\n", 0, 0.000);
            sleep(5);
        }
        else {
            printf("|\tPos.\t|%5s\t|%10s\t|%10s\t|%10s\t|%10s\t|%7s\t|%5s\t|%5s\t|%10s\t|\n\n", "Nr", "S1", "S2", "S3", "Lap Time", "Lap Nr", "Pit", "CRASH", "FINISHED");

            int u;
            int position;
            position = 0;
            for(u = 0; u < current_session.total_cars; u++){
                printf("|\t%d\t|%5d\t|%10.3f\t|%10.3f\t|%10.3f\t|%10.3f\t|%7d\t|%5d\t|%5d\t|%10d\t|\n", position + 1, numeroCar[u], 0.000, 0.000, 0.000, 0.000, 0, 0, 0, 0);
                position++;
            }
            printf("\n Best Sector 1 : %d [%.3f]\t", 0, 0.000);
            printf("Best Sector 2 : %d [%.3f]\t", 0, 0.000);
            printf("Best Sector 3 : %d [%.3f]\t", 0, 0.000);
            printf("Best Lap : %d [%.3f]\t\n", 0, 0.000);
            sleep(5);
        }
	}

}