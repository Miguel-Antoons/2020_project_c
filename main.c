#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "car.h"

int carNumber[20] = {44, 77, 16, 5, 33, 23, 55, 4, 3, 31, 10, 26, 11, 18, 7, 99, 20, 8, 63, 6};

int main(int argc, char *argv[]){
    struct Session session = {.name = "P1", .tempsSession = 5400, .numberCars = 20};
    int i;
    int pid;
    printf(session.numberCars);
    /**
    for(i = 0;  i < session.numberCars; i++){
        pid = fork();
        if(pid == 0){
            printf("enfant");
        }
    }
     **/
}