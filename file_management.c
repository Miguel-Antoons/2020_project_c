//
// Created by antoo on 11-Nov-20.
//

#include "file_management.h"

struct Session current_session;

/**
 * Va écrire le classement de la course dans un fichier
 * @param race_copy : copie de la course
 */
void writeClassement(struct Car *race_copy){
	FILE* file = fopen(current_session.file_name, "w");
	
	if (file != NULL){
		for(int i = 0; i < 20; i++){
			fprintf(file, "%d\n", race_copy[i].idCar);
		}
		fclose(file);
	}
}

/**
 * Va imprimer à l'écran la position de début de chaque voiture lors de Q2, Q3, et la course finale
 */
void print_previous_ranking(){
	int numeroCar[20]; //On vide le tableau
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
	else{
	    file = NULL;
	}
	
	if(file != NULL){
	    system("clear");
        i=0;

        while(fgets(chaine, 5, file)){
			numeroCar[i] = atoi(chaine);
            i++;
		}
		
		printf("|\tPos.\t|%5s\t|%10s\t|%10s\t|%10s\t|%10s\t|%7s\t|%5s\t|%5s\t|%10s\t|\n\n", "Nr", "S1", "S2", "S3", "Lap Time", "Lap Nr", "Pit", "CRASH", "FINISHED");
		
		int u;
		for(u = 0; u < 20; u++){
		    if (u < current_session.total_cars) {
                printf("|\t%d\t|%5d\t|%10.3f\t|%10.3f\t|%10.3f\t|%10.3f\t|%7d\t|%5d\t|%5d\t|%10d\t|\n", u + 1,
                       numeroCar[u], 0.000, 0.000, 0.000, 0.000, 0, 0, 0, 0);
            }
		    else {
                current_session . driving_cars[u - current_session . total_cars] = numeroCar[u];
            }
		}
		printf("\n Best Sector 1 : %d [%.3f]\t", 0, 0.000);
		printf("Best Sector 2 : %d [%.3f]\t", 0, 0.000);
		printf("Best Sector 3 : %d [%.3f]\t", 0, 0.000);
		printf("Best Lap : %d [%.3f]\t\n", 0, 0.000);
        sleep(5);
	}
}