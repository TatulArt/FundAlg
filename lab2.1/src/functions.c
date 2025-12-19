#include "../include/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stddef.h>
#include <math.h>

CheckRepresentationStatus CheckFiniteRepresentation(double fraction, int base, int* result){
    int count = 0;
    int cap = 128;
    double *remainders = malloc(cap * sizeof(double)); 
    if (!remainders)
        return REPR_MEMORY_ERROR;  
    
    while (fraction > 1e-9 && count < 500){
        fraction *= base;
        int digit = (int)fraction;

        fraction -= digit;
        if (fraction < 1e-9) {
            *result = 1;
            free(remainders);
            return REPR_OK;
        }
        for (int i = 0; i < count; i++) {
            if (fabs(fraction - remainders[i]) < 1e-9) {
                *result = 0;
                free(remainders);
                return REPR_OK; 
            }
        }
        if (count == cap) {
            cap *= 2;
            double *temp = realloc(remainders, cap * sizeof(double));
            if (!temp) {
                free(remainders);
                return REPR_MEMORY_ERROR;  
            }
            remainders = temp;
        }
        remainders[count++] = fraction;
    }
    free(remainders);   
    *result = fraction < 1e-9; 

    return REPR_OK;
}

CheckNumbersStatus check_numbers(int** ans, int count, int base, ...) {
    if (!ans) {
        return POINTER_ERROR;
    }
    if (!(base >= 2 && base <= 256)) {
        return BASE_ERROR;
    }

    *ans = (int*)malloc(count * sizeof(int));
    if (!(*ans)) {
        return CHECK_MEMORY_ERROR;
    }

    va_list args;
    va_start(args, base);
    for (int i = 0; i < count; ++i) {
        double number = va_arg(args, double);
        double fraction = number - floor(number);

        if (fraction < 0) fraction = -fraction; 

        if (number < 0 || number >= 1) {
            return BAD_NUMBER_ERROR;
        }

        int status = CheckFiniteRepresentation(fraction, base, &(*ans)[i]);
        if (status == REPR_MEMORY_ERROR) {
            return CHECK_MEMORY_ERROR;
        }
    }
    va_end(args);
    return CHECK_OK;
}

ProcessingStatus StatusProcessing(CheckNumbersStatus status){
    if (status == CHECK_OK){
        return OK_PROC;
    }
    if (status == POINTER_ERROR){
        printf("Getting massive data error\n");
        return ERROR_PROC;
    }
    if (status == BASE_ERROR){
        printf("Base must be from 2 to 256\n");
        return ERROR_PROC;
    }
    if (status == CHECK_MEMORY_ERROR){
        printf("Allocation memory error\n");
        return ERROR_PROC;
    }
    if (status == BAD_NUMBER_ERROR){
        printf("Number must be in interval (0, 1)\n");
        return ERROR_PROC;
    }

}