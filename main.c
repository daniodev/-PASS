#include "Libraries/ultPassGen.h"

int main(){

    printf("   __  __    _______    ______    ______    ______  \n");
    printf("  /  |/  |  /       \\  /      \\  /      \\  /      \\ \n");
    printf(" _$$ |$$ |_ $$$$$$$  |/$$$$$$  |/$$$$$$  |/$$$$$$  |\n");
    printf("/ $$  $$   |$$ |__$$ |$$ |__$$ |$$ \\__$$/ $$ \\__$$/ \n");
    printf("$$$$$$$$$$/ $$    $$// $$    $$ |$$      \\ $$      \\ \n");
    printf("/ $$  $$   |$$$$$$$/  $$$$$$$$ | $$$$$$  | $$$$$$  |\n");
    printf("$$$$$$$$$$/ $$ |      $$ |  $$ |/  \\__$$ |/  \\__$$ |\n");
    printf("  $$ |$$ |  $$ |      $$ |  $$ |$$    $$/ $$    $$/ \n");
    printf("  $$/ $$/   $$/       $$/   $$/  $$$$$$/   $$$$$$/  \n");

    char *pass;
    if(checkBool("file-crypting") == true){
    FILE *passwords = fopen("password.txt", "r");
    FILE *passwordsCrypted = fopen("CryptedPasswords.crypted", "r");

    if(passwords != NULL && passwordsCrypted == NULL){
        printForLen("config.yml", "lang", "noSafeExit");
        scanf("%s", pass);
    } 

    if (passwordsCrypted != NULL && passwords == NULL) {
        printForLen("config.yml", "lang", "InSertKey");
        scanf("%s", pass);
        FileDecrypter("CryptedPasswords.crypted", "password.txt", pass);
        fclose(passwordsCrypted);
        remove("CryptedPasswords.crypted");
    }

    if (passwords == NULL && passwordsCrypted == NULL) {
        printForLen("config.yml", "lang", "FirstStart");
        printForLen("config.yml", "lang", "AddItHere");
        scanf("%s", pass);

        passwords = fopen("password.txt", "w");
        fprintf(passwords, "# DECRYPT\n//DO NOT TOUCH THIS STRING FOR ANY REASON\n\n");
        fclose(passwords);



    }

    fclose(passwords);
    fclose(passwordsCrypted);

    }
    FILE *passwordsCrypted = fopen("CryptedPasswords.crypted", "r");
    if(checkBool("file-crypting") == false){
        remove("CryptedPasswords.crypted");
    }
    fclose(passwordsCrypted);


    while(1){
        printForLen("config.yml", "lang", "WhatToDo");
        printForLen("config.yml", "lang", "SeePasswords");
        printForLen("config.yml", "lang", "AddPassword");
        printForLen("config.yml", "lang", "EditPassword");
        printForLen("config.yml", "lang", "SafeExit");

        int option = 0;
        printForLen("config.yml", "lang", "ProvideNumber");
        scanf("%d", &option);

        if(option != 1 && option != 2 && option != 3 && option != 4){
            printForLen("config.yml", "lang", "OptionNotInList");
        }

        if(option == 0 || option == 4){
            break;
        }

        if(option == 1){
            printForLen("config.yml", "lang", "ListPasswords");
            FILE *passwords = fopen("password.txt", "a+");
            char allFile;
            while ((allFile = fgetc(passwords)) != EOF){
                printf("%c", allFile);
            }

            fclose(passwords); 
        }

        if(option == 2){
            char password[255];
            FILE *passwords = fopen("password.txt", "a+");

            char siteName[255];
            printForLen("config.yml", "lang", "SiteName");
            scanf("%s", siteName);

            char email[255];
            printForLen("config.yml", "lang", "RegisteredEmail");
            scanf("%s", email);

            while (!emailCheck(email)){
                printForLen("config.yml", "lang", "InvalidEmail");
                printForLen("config.yml", "lang", "RegisteredEmail");
                scanf("%s", email);
            }

            if (emailCheck(email)){

            int genPass = 0;
            printForLen("config.yml", "lang", "ManualOrGenerate");
            scanf("%d", &genPass);

            if(genPass == 2){
                int passLenght = 0;
                printForLen("config.yml", "lang", "InsertLength");
                scanf("%d", &passLenght);
                printForLen("config.yml", "lang", "GeneratingPassword");
                option = 0;
                while (option != 1){

                    if(passLenght != 0){
                        if(passLenght <= checkInt("Max-pass-len") && passLenght >= checkInt("Min-pass-len")){
                            passwordGenerator(password, passLenght);
                            printForLen("config.yml", "lang", "GeneratedPassword");
                            printf("%s", password);
                            printForLen("config.yml", "lang", "KeepOrChange");
                            scanf("%d", &option);
                        }else{
                            if(passLenght > checkInt("Max-pass-len")){
                            printForLen("config.yml", "lang", "MaxPasswordLength");
                            printf("%d", checkInt("Max-pass-len"));
                        }
                        if(passLenght < checkInt("Min-pass-len")){
                            printForLen("config.yml", "lang", "MinPasswordLength");
                            printf("%d", checkInt("Min-pass-len"));
                        }
                        printForLen("config.yml", "lang", "InsertLength");
                        scanf("%d", &passLenght);
                    }
                    }
                }
            }else{
                printForLen("config.yml", "lang", "InsertPassword");
                scanf("%s", password);
            }
        }

            fprintf(passwords, "Email: %s\n", email);
            fprintf(passwords, "Site: %s\n", siteName);
            fprintf(passwords, "Password: %s\n\n", password);

            fclose(passwords);
        }


        if(option == 3){
            FILE *passwords = fopen("password.txt", "r+");

            char edSite[255];
            printForLen("config.yml", "lang", "SiteToEdit");
            scanf("%s", edSite);
            char newPass[255];
            if(findInFile("password.txt", edSite)){
                printForLen("config.yml", "lang", "InsertNewPassword");
                scanf("%s", newPass);

                editPass(edSite, newPass);
            }

            fclose(passwords);
        }

        
    }
    if(checkBool("file-crypting") == true){
    fileEncrypter("password.txt", "CryptedPasswords.crypted", pass);
    remove("password.txt");
    }

}