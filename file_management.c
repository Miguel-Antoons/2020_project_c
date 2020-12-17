//
// Created by antoo on 11-Nov-20.
//

#include "file_management.h"

void writeClassement(struct Car *race_copy, struct Session current_session){
	FILE* file = fopen(current_session.file_name, "w");
	
	if (file != NULL){
		for(int i = 0; i < current_session.total_cars; i++){
			printf("%d", race_copy[i].idCar);
			fprintf(file, "%d\n", race_copy[i].idCar);
		}
		fclose(file);
	}
}


void print_previous_ranking(struct Car *race_copy, struct Session current_session){
	char *string_to_read;
	int size;

	FILE* file = fopen(current_session.file_name, "r");
	size = 11;
	
	if (file == NULL){	
		printf("Erreur d'ouverture du fichier");
	}
	
	else {
		printf("Le fichier est ouvert\n");
	}
	int i;
	/* verification si le fichier est bien ouvert */
	while(string_to_read = fgets(string_to_read, size, file)  != EOF){
		tab[i]=string_to_read;
		i++;
	}
	fclose(file);
	/* Fermeture du fichier */

}