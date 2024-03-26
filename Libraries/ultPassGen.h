#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "yamlWatcher.h"

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

bool emailCheck(char *email){

    if(checkBool("accurate-email-checker")){

    bool FoundC = false, FoundP = false;
    int i;

    for(i = 0; email[i] != '\0'; i++){
        if(email[i] == '@'){
            FoundC = true;
            break;
        }
    }

    for(; email[i] != '\0'; i++){
        if(email[i] == '.'){
            FoundP = true;
            break;
        }
    }

    return FoundC && FoundP && email[i + 1] != '\0';
    }else{
        return true;
}
}