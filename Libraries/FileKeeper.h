#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool checkBool(const char *str) {
    FILE *yml = fopen("config.yml", "r");
    if (!yml) {
        printf("Errore nell'apertura del file.");
        return false;
    }

    char key[100];
    char value[100];
    bool result = false;

    char line[256];
    while (fgets(line, sizeof(line), yml) != NULL) {
        char configKey[100];
        char value[100];
        if (sscanf(line, "%s = %s", configKey, value) == 2) {
            if(strcmp(str, configKey) == 0){
            if (strcmp(value, "true") == 0) {
                fclose(yml);
                return true;
            }else if(strcmp(value, "false")){
                    return false;
                }else if(strcmp(value, "false") != 0 && strcmp(value, "true") != 0){
                    printf("\nValore nel file yaml non valido: %s, %s", key, value);
            }
            }
        }
    }


    fclose(yml);
    return false;
}

int checkInt(char *str) {
    FILE *yml = fopen("config.yml", "r");
    char line[256];
    while (fgets(line, sizeof(line), yml) != NULL) {
        char configKey[100];
        int value;
        if (sscanf(line, "%99s = %d", configKey, &value) == 2) {
            if(strcmp(configKey, str) == 0){
            fclose(yml);
            return value;
            }
        }
    }
    fclose(yml);
    return 0;
}


bool findInFile(char *fName, char edString[]){
    FILE *passwords = fopen(fName, "r");
    char line[256];
    while (fgets(line, sizeof(line), passwords) != NULL) {
        char configKey[100];
        char value[255];
        if (sscanf(line, "Site: %[^\n]", value) == 1) {
            if (strcmp(value, edString) == 0) {
                fclose(passwords);
                return true;
            }
        }
    }
    fclose(passwords);
    printf("\n%s don't exists\n",edString);
    return false;
}

bool editPass(char edString[], char *newPass){
    FILE *passwords = fopen("password.txt", "r+");
    char line[256];
    long int position = -1;
    while (fgets(line, sizeof(line), passwords) != NULL) {
        position = ftell(passwords);
        char value[255];
        if (sscanf(line, "Site: %[^\n]", value) == 1) {
            if (strcmp(value, edString) == 0) {
                printf("\nPassword changed succesfully.\n");
                fseek(passwords, position, SEEK_SET);
                fprintf(passwords, "Password: %s\n", newPass);
                fclose(passwords);
                return true;
            }
        }
    }
    fclose(passwords);
    return false;
}