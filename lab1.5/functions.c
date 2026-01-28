#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>



ParseFlagStatus ParseFlag(const char *InputedFlag, char *flag, bool *nExist) {
    if (InputedFlag[0] != '-' && InputedFlag[0] != '/'){
        return NOT_A_FLAG;
    }

    if (strlen(InputedFlag) == 3){
        if(InputedFlag[1] != 'n'){
            return UNKNOWN_FLAG;
        }
        *flag = InputedFlag[2];
        *nExist = true;
        return FLAG_PARSED;
    }
    *flag = InputedFlag[1];
    return FLAG_PARSED;
}

void RemoveNumbers(FILE* inpFile, FILE* outFile){
    char c;
    while ((c = fgetc(inpFile)) != EOF){
        if (isdigit(c)) {
            continue;
        }
        fputc(c, outFile);
    }
}

void CountLetters(FILE* inpFile, FILE* outFile){
    char c;

    long countedLetters = 0;
      while (!feof(inpFile)) {
        c = fgetc(inpFile);
        if (isalpha(c)){
            ++countedLetters;
        }
        if (c == '\n' || c == EOF) {
            fprintf(outFile, "%ld\n", countedLetters);
            countedLetters = 0;
        }
    }
}

void CountNonLettersNumbers(FILE* inpFile, FILE* outFile){
    char c;
    long counted = 0;
    while (!feof(inpFile)) {
        c = fgetc(inpFile);
        if (!isalpha(c) && !isdigit(c) && c != ' ' && c != '\n' && c != EOF) {
            ++counted;
        }
        if (c == '\n' || c == EOF) {
            fprintf(outFile, "%ld\n", counted);
            counted = 0;
        }
    }
}

ReplaceStatus replaceWithHex(FILE *inpFile, FILE *outFile){
    char c;
    char HexDigits[3];
    while ((c = getc(inpFile)) != EOF) {
        if ((c != ' ' && c != '\n' && c != '\t') && !isdigit(c)) {
            int ASCIIchar = (int)c;
            HexStatus toHexStatus = ToHex(ASCIIchar, HexDigits);
            if (toHexStatus == HEX_OVERFLOW) {
                return REPLACE_ERROR;
            }
        } else{
            HexDigits[0] = c;
            HexDigits[1] = '\0';
        }
        HexDigits[2] = '\0';
        fputs(HexDigits, outFile);
    }
    return REPLACE_OK;
}

HexStatus ToHex(int number, char *HexDigits) {
    if (number < 0 || number > 255) {
        return HEX_OVERFLOW;
    }

    // Для числа 0
    if (number == 0) {
        HexDigits[0] = '0';
        HexDigits[1] = '0';
        HexDigits[2] = '\0';
        return HEX_OK;
    }

    int i = 1;  // Начинаем с младшего разряда
    char hex_chars[] = "0123456789ABCDEF";

    while (number > 0 && i >= 0) {
        int digit = number % 16;
        HexDigits[i--] = hex_chars[digit];
        number /= 16;
    }

    // Если остался старший разряд (число было < 16)
    if (i == 0) {
        HexDigits[0] = '0';
    }

    HexDigits[2] = '\0';
    return HEX_OK;
}



