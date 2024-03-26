#include "Libraries/ultPassGen.h"

int main(){
    printf(" /$$   /$$ /$$    /$$$$$$$$ /$$$$$$ /$$      /$$  /$$$$$$  /$$$$$$$$ /$$$$$$$$       /$$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$  /$$      /$$  /$$$$$$  /$$$$$$$  /$$$$$$$\n");
    printf("| $$  | $$| $$   |__  $$__/|_  $$_/| $$$    /$$$ /$$__  $$|__  $$__/| $$_____/      | $$__  $$ /$$__  $$ /$$__  $$ /$$__  $$| $$  /$ | $$ /$$__  $$| $$__  $$| $$__  $$\n");
    printf("| $$  | $$| $$      | $$     | $$  | $$$$  /$$$$| $$  \\ $$   | $$   | $$            | $$  \\ $$| $$  \\ $$| $$  \\__/| $$  \\__/| $$ /$$$| $$| $$  \\ $$| $$  \\ $$| $$  \\ $$\n");
    printf("| $$  | $$| $$      | $$     | $$  | $$ $$/$$ $$| $$$$$$$$   | $$   | $$$$$         | $$$$$$$/| $$$$$$$$|  $$$$$$ |  $$$$$$ | $$/$$ $$ $$| $$  | $$| $$$$$$$/| $$  | $$\n");
    printf("| $$  | $$| $$      | $$     | $$  | $$  $$$| $$| $$__  $$   | $$   | $$__/         | $$____/ | $$__  $$ \\____  $$ \\____  $$| $$$$_  $$$$| $$  | $$| $$__  $$| $$  | $$\n");
    printf("| $$  | $$| $$      | $$     | $$  | $$\\  $ | $$| $$  | $$   | $$   | $$            | $$      | $$  | $$ /$$  \\ $$ /$$  \\ $$| $$$/ \\  $$$| $$  | $$| $$  \\ $$| $$  | $$\n");
    printf("|  $$$$$$/| $$$$$$$$| $$    /$$$$$$| $$ \\/  | $$| $$  | $$   | $$   | $$$$$$$$      | $$      | $$  | $$|  $$$$$$/|  $$$$$$/| $$/   \\  $$|  $$$$$$/| $$  | $$| $$$$$$$/\n");
    printf(" \\______/ |________/|__/   |______/|__/     |__/|__/  |__/   |__/   |________/      |__/      |__/  |__/ \\______/  \\______/ |__/     \\__/ \\______/ |__/  |__/|_______/");

    while(1){

        printf("\nWhat would you like to do: ");
        printf("\n[1] See my passowrds");
        printf("\n[2] Add a password");
        printf("\n[3] Edit a passowrd");

        int option = 0;
        printf("\nPlease provide a number: ");
        scanf("%d", &option);

        if(option != 1 && option != 2 && option != 3){
            printf("Option not in list.");
        }

        if(option == 0){
            break;
        }

        if(option == 1){
            printf("Here's the list of your passowrds!\n");
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
            printf("Whats the name of the site you want to add a passowrd?: ");
            scanf("%s", siteName);

            char email[255];
            printf("Whats the email you registered with?: ");
            scanf("%s", email);

            while (!emailCheck(email)){
                printf("Invalid email...\n");
                printf("Whats the email you registered with?: ");
                scanf("%s", email);
            }

            if (emailCheck(email)){

            int genPass = 0;
            printf("Would you like to manually add the password [1] or generate one? [2]: ");
            scanf("%d", &genPass);

            if(genPass == 2){
                int passLenght = 0;
                printf("Please insert the lenght of the password: ");
                scanf("%d", &passLenght);
                printf("Generating a passowrd...");
                option = 0;
                while (option != 1){

                    if(passLenght != 0){
                        if(passLenght <= checkInt("Max-pass-len") && passLenght >= checkInt("Min-pass-len")){
                            passwordGenerator(password, passLenght);
                            printf("Here's the generated password: %s", password);
                            printf("\nWould you like to keep it [1] or to change it [2]: ");
                            scanf("%d", &option);
                        }else{
                            if(passLenght > checkInt("Max-pass-len")){
                            printf("\nFor security reasons the maximum lenght is %d", checkInt("Max-pass-len"));
                        }
                        if(passLenght < checkInt("Min-pass-len")){
                            printf("\nFor security reasons the minimum lenght is %d", checkInt("Min-pass-len"));
                        }
                        printf("\nPlease insert the lenght of the password: ");
                        scanf("%d", &passLenght);
                    }
                    }
                }
            }else{
                printf("Insert the passowrd: ");
                scanf("%s", password);
            }
        }

            fprintf(passwords, "Site: %s\n", siteName);
            fprintf(passwords, "Email: %s\n", email);
            fprintf(passwords, "Passowrd: %s\n\n", password);

            fclose(passwords);
        }
        
    }

}