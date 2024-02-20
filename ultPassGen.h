#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

void passwordGenerator(char password[], int lenght){

    time_t t;
    srand((unsigned) time(&t));
    char generatedPassword[lenght]; 
    char caratteriSpeciali[12] = {'#', '@', '*', ']', '[', '.', ',', '-', '|', '%', '$', '/'};

    for(int i = 0; i < lenght; i++){
        if(rand() % 4 == 1){
            int carattereDeciso = rand() % 12;
            generatedPassword[i] = caratteriSpeciali[carattereDeciso];
        }else{
        generatedPassword[i] =  rand() % ('z' - 'a' + 1) + 'a';
        }
    }

    generatedPassword[lenght] = '\0';
    strcpy(password, generatedPassword);
}
