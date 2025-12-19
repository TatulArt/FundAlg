#include "functions.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, const char* argv[]){
    if (argc < 2) {
        printf("Not enough args\n");
        return INVALID_INPUT;
    }
    ReplaceStatus repStatus;
    bool nExist = false;
    char flag = '\0';
    char * outputFile;
    ParseFlagStatus flagStatus = ParseFlag(argv[1], &flag, &nExist);

    switch (flagStatus) {
    case FLAG_PARSED:
        break;
    case UNKNOWN_FLAG:
        printf("Unknown flag: %s\n", argv[1]);
        return INVALID_INPUT;
    case NOT_A_FLAG:
    printf("Second argument is not a flag: %s\n", argv[1]);
        return INVALID_INPUT;
    }

    if (nExist == true){
        if (argc != 4){
            printf("Must be 3 args with 'n' in flag\n");
            return INVALID_INPUT;
        }
        outputFile = malloc(sizeof(char) * (strlen(argv[3]) + 1));
        if (!outputFile){
            printf("Memory allocation error\n");
            return MEMORY_ERROR;
        }
        outputFile[0] = '\0';
        strcat(outputFile, argv[3]);
    } else {
        if (argc != 3){
            printf("Must be 2 args without 'n' in flag\n");
            return INVALID_INPUT;
        }
        outputFile = malloc(sizeof(char) * (strlen(argv[2]) + 5));
        if (!outputFile){
            printf("Memory allocation error\n");
            return MEMORY_ERROR;
        }
        outputFile[0] = '\0';
        strcat(outputFile, "out_");
        strcat(outputFile, argv[2]);
    }
    FILE *inpFile;
    if ((inpFile = fopen(argv[2], "r")) == NULL) {
        printf("There is an error opening input file |%s|\n", argv[2]);
        return OPEN_FILE_ERROR;
    }
    FILE *outFile;
    if ((outFile = fopen(outputFile, "w")) == NULL) {
        printf("There is an error opening or creating output file |%s|\n", outputFile);
        fclose(inpFile);
    return OPEN_FILE_ERROR;
    }

    switch (flag){
        case 'd':
            RemoveNumbers(inpFile, outFile);
            break;
        case 'i':
            CountLetters(inpFile, outFile);
            break;
        case 's':
            CountNonLettersNumbers(inpFile, outFile);
            break;
        case 'a':
            repStatus = replaceWithHex(inpFile, outFile);
            if (repStatus == REPLACE_ERROR){
                printf("An error during replacing: hex overflow\n");
                return OVERFLOW; 
            }
            break;
        default:
            printf("Unknown flag\n");
            return INVALID_INPUT;
    }
    fclose(inpFile);
    fclose(outFile);
    free(outputFile);
    return 0;
}
