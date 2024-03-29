#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void fileEncrypter(char *inputFileName, char *outputFileName, char *key) {
    FILE *infile = fopen(inputFileName, "rb");
    FILE *outFile = fopen(outputFileName, "a");

    if (infile == NULL || outFile == NULL) {
        if (infile != NULL) fclose(infile);
        if (outFile != NULL) fclose(outFile);
        remove(outputFileName);
        exit(EXIT_FAILURE);
    }

    size_t keyLength = strlen(key);
    size_t keyIndex = 0;

    int ch;
    while ((ch = fgetc(infile)) != EOF) {
        fputc(ch ^ key[keyIndex], outFile);
        keyIndex = (keyIndex + 1) % keyLength;
    }

    fclose(infile);
    fclose(outFile);
    remove(inputFileName);
}

void FileDecrypter(char *inputFileName, char *outputFileName, char *key) {
    FILE *infile = fopen(inputFileName, "rb");
    FILE *outFile = fopen(outputFileName, "awb");

    if (infile == NULL || outFile == NULL) {
        if (infile != NULL) fclose(infile);
        if (outFile != NULL) fclose(outFile);
        remove(outputFileName);
        exit(EXIT_FAILURE);
    }

    size_t keyLength = strlen(key);
    size_t keyIndex = 0;

    int ch;
    while ((ch = fgetc(infile)) != EOF) {
        fputc(ch ^ key[keyIndex], outFile);
        keyIndex = (keyIndex + 1) % keyLength;
    }

    fclose(infile);
    fclose(outFile);

    outFile = fopen(outputFileName, "rb");

    char header[] = "# DECRYPT";
    char headerCheck[sizeof(header)];
    fgets(headerCheck, sizeof(headerCheck), outFile);

    fclose(outFile);

    if (strcmp(header, headerCheck) != 0) {
        printf("Wrong key.");

        remove(outputFileName);

        exit(EXIT_FAILURE);
    } else {
        remove(inputFileName);
    }
}