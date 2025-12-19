#ifndef DEF_H
#define DEF_H
#include <stddef.h>

typedef enum{
    OK_INPUT,
    INVALID_INPUT,
    OVERFLOW,
    MEMORY_ERROR
} MainStatus;

typedef enum{
    NUMBER_INT_OVERFLOW,
    NOT_POSITIVE_NUMBER,
    NOT_DIGITS_IN_NUMBER,
    DOUBLE_OVERFLOW,
    OK_NUMBER
} ParseNumberStatus;

typedef enum{
    OK_PROC,
    ERROR_PROC
} ProcessingStatus;

typedef enum{
    PRIME,
    NOT_PRIME,
    NON_PRIME_COMP
} IsNumberPrime;

typedef enum{
    CALC_ERROR,
    CALC_OK
} CalculatingStatus;

typedef enum{
    POINTER_ERROR,
    BASE_ERROR,
    CHECK_MEMORY_ERROR,
    BAD_NUMBER_ERROR,
    CHECK_OK
} CheckNumbersStatus;

typedef enum{
    REPR_MEMORY_ERROR,
    REPR_OK
} CheckRepresentationStatus;

ProcessingStatus StatusProcessing(CheckNumbersStatus status);
CheckNumbersStatus check_numbers(int** ans, int count, int base, ...);
CheckRepresentationStatus CheckFiniteRepresentation(double fraction, int base, int* result);

#endif