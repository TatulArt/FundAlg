#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void usage() {
    printf("<program name> input.txt output.txt\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3){
        usage();
        return 1;
    }

    if (strcmp(argv[1], argv[2]) == 0) {
        printf("Ошибка: Входной и выходный файлы имеют одинаковые имена\n");
        return 1;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Ошибка открытия входного файла\n");
        return 1;
    }
    
    FILE* outputFile = fopen(argv[2], "a");
    if (outputFile == NULL) {
        printf("Ошибка открытия выходного файла\n");
        fclose(inputFile);
        return 1;
    }

    char c;
    char number[1024];
    int numIndex = 0;
    while ((c = fgetc(inputFile)) != EOF) {
        if (isspace(c)) {
            if (numIndex > 0) {
                number[numIndex] = '\0';

                removeZeros(number);

                int minBase = findMinBase(number);
                
                if (minBase != -1) {
                    long long decimalValue = convertToDecimal(number, minBase);
                    int signValue = findSignValue(number);
                    
                    if (decimalValue != -1) {
                        if (signValue == 1) {
                        fprintf(outputFile, "%s %d %lld\n", number, minBase, decimalValue);
                        } else if (signValue == -1) {
                        fprintf(outputFile, "%s %d -%lld\n", number, minBase, decimalValue);
                        }
                    } else {
                        printf("Ошибка: переполнение при преобразовании числа '%s'\n", number);
                    }
                } else {
                    printf("Ошибка: недопустимые символы в числе '%s'\n", number);
                }
                
                numIndex = 0;
            }
        } else {
            if (numIndex == 0 && c == '-') {
                number[numIndex] = c;
                numIndex++;
            } else if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')) {
                number[numIndex] = toupper(c);
                numIndex++;
            } else if (numIndex == 0 && c == '+') {
            } else {
                numIndex = 0; 
                while ((c = fgetc(inputFile)) != EOF)
                    if (isspace(c)) break;
            }
            if (numIndex >= sizeof(number) - 1) {
                printf("Ошибка: слишком длинное число\n");
                numIndex = 0;
            }
        }
    }        

    if (numIndex > 0) {
        number[numIndex] = '\0';
        removeZeros(number);
        
        int minBase = findMinBase(number);
        if (minBase != -1) {
            long long decimalValue = convertToDecimal(number, minBase);
            if (decimalValue != -1) {
                fprintf(outputFile, "%s %d %lld\n", number, minBase, decimalValue);
            } else {
                printf("Ошибка: переполнение при преобразовании числа '%s'\n", number);
            }
        } else {
            printf("Ошибка: недопустимые символы в числе '%s'\n", number);
        }
    }
    
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}