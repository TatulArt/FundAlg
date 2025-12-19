#ifndef DEF_H
#define DEF_H
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum{
    OK_INPUT,
    INVALID_INPUT,
    OVERFLOW,
    MEMORY_ERROR,
    OPEN_FILE_ERROR
} MainStatus;

typedef enum{
    HEX_OVERFLOW,
    HEX_OK
} HexStatus;

typedef enum{
    REPLACE_ERROR,
    REPLACE_OK
} ReplaceStatus;

typedef enum{
    NUMBER_INT_OVERFLOW,
    NOT_POSITIVE_NUMBER,
    NOT_DIGITS_IN_NUMBER,
    DOUBLE_OVERFLOW,
    OK_NUMBER
} ParseNumberStatus;

typedef enum{
    UNKNOWN_FLAG,
    FLAG_PARSED,
    NOT_A_FLAG
} ParseFlagStatus;

void CountNonLettersNumbers(FILE* inpFile, FILE* outFile);
void RemoveNumbers(FILE* inpFile, FILE* outFile);
void CountLetters(FILE* inpFile, FILE* outFile);
ParseFlagStatus ParseFlag(const char *InputedFlag, char *flag, bool *nExist);
ReplaceStatus replaceWithHex(FILE *inpFile, FILE *outFile);
HexStatus ToHex(int number, char *HexDigits);
#endif