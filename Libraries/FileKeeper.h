#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char *printForLen(char *config, char *LangStr, char *toPrintSTR);

bool checkBool(const char *str) {
    FILE *yml = fopen("config.yml", "r");
    if (!yml) {
        printForLen("config.yml", "lang", "ErrorOpeningFile");
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
                    printForLen("config.yml", "lang", "InvalidValueInYamlFile");
                    printf("%s, %s", key, value);
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
    printForLen("config.yml", "lang", "ElementDoesNotExist");
    printf("\n%s\n",edString);
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
                printf("\n");
                printForLen("config.yml", "lang", "PasswordChangedSuccessfully");
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

char* strLangFinder(const char *fileName, char findableElement[]) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printForLen("config.yml", "lang", "ErrorOpeningFile");
        return NULL;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        char configKey[100];
        char value[255];
        if (sscanf(line, "%s = %[^\n]", configKey, value) == 2) {
            if(strcmp(configKey, findableElement) == 0) {
                fclose(file);
                char *language = malloc(strlen(value) + 1);
                if (language == NULL) {
                    printForLen("config.yml", "lang", "ErrorOpeningFile");
                    return NULL;
                }
                strcpy(language, value);
                return language;
            }
        }
    }
    fclose(file);
    return NULL;
}

struct en{
    char *toPrintStr;
};

struct it{
    char *toPrintStr;
};

struct fr{
    char *toPrintStr;
};

struct de{
    char *toPrintStr;
};

char *printForLen(char *config, char *LangStr, char *toPrintSTR){
    char *lang = strLangFinder(config, LangStr);

    if(strcmp(lang, "en") == 0){
        struct en Lang;
        Lang.toPrintStr = strLangFinder("lang/en.yml", toPrintSTR);
        printf("\n%s", Lang.toPrintStr);
    }

    if(strcmp(lang, "it") == 0){
        struct it Lang;
        Lang.toPrintStr = strLangFinder("lang/it.yml", toPrintSTR);
        printf("\n%s", Lang.toPrintStr);
    }

    if(strcmp(lang, "fr") == 0){
        struct fr Lang;
        Lang.toPrintStr = strLangFinder("lang/fr.yml", toPrintSTR);
        printf("\n%s", Lang.toPrintStr);
    }

    if(strcmp(lang, "de") == 0){
        struct de Lang;
        Lang.toPrintStr = strLangFinder("lang/de.yml", toPrintSTR);
        printf("\n%s", Lang.toPrintStr);
    }

}

/*bool editString(char edString[], char *newString, char *fileName){
    FILE *passwords = fopen(fileName, "r+");
    char line[256];
    long int position = -1;
    while (fgets(line, sizeof(line), passwords) != NULL) {
        position = ftell(passwords);
        char value[255];
        char configKey[255];
        if (sscanf(line, "%s = %[^\n]", configKey, value) == 2) {
            if (strcmp(configKey, edString) == 0) {
                fseek(passwords, position, SEEK_SET);
                fprintf(passwords, "%s = %s\n", editString, newString);
                fclose(passwords);
                return true;
        }
    }
    fclose(passwords);
    return false;
    }
}*/