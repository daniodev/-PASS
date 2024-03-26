#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void fileEncrypter(char *inputFileName, char *outputFileName, int key){
    FILE *infile = fopen(inputFileName, "rb");
    FILE *outFile = fopen(outputFileName, "a");

    if(infile == NULL || outFile == NULL){
            fclose(outFile);
            remove(outputFileName);
            exit(EXIT_FAILURE);
    }

    int ch;
    while ((ch = fgetc(infile)) != EOF){
        fputc(ch ^ key, outFile);
    }

    fclose(infile);
    remove(inputFileName);
    
}


void FileDecrypter(char *inputFileName, char *outputFileName, int key){
    FILE *infile = fopen(inputFileName, "rb");
    FILE *outFile = fopen(outputFileName, "awb");

    if(infile == NULL || outFile == NULL){
            fclose(outFile);
            remove(outputFileName);
            exit(EXIT_FAILURE);
    }

    int ch;
    while ((ch = fgetc(infile)) != EOF){
        fputc(ch ^ key, outFile);
    }

    fclose(infile);
    fclose(outFile);

    outFile = fopen(outputFileName, "rb");

    char header[] = "# DECRYPT";
    char headerCheck[sizeof(header)];
    fgets(headerCheck, sizeof(headerCheck), outFile);

    fclose(outFile);

    if (strcmp(header, headerCheck) != 0) {
        printf("La key inserita non corrisponde alla key ufficiale.");

        remove(outputFileName);

        exit(EXIT_FAILURE);
    } else {
        remove(inputFileName);
    }
}