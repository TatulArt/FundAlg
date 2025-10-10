#ifndef MYLIB_H
#define MYLIB_H
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

static char *statusDescriptions[] = {
    "OK",
    "Ошибка освобождения памяти",
    "Использование программы: ./build <x> <флаг>",
    "Превышение ограничения памяти",
    "Порядковые номера простых чисел выше 500 запрещены для корректной работы программы",
    "Некорректный формат x. Число должно состоять только из арабских цифр и не содержать ведущих нулей",
    "Ожидалось натуральное значение x",
    "Ошибка поиска простых чисел",
    "Неизвестная ошибка, анлак :("
};

typedef enum StatusCode {
    OK,
    MEMORY_ALLOCATION_FAILED,
    WRONG_ARG_AMOUNT,
    OUT_OF_MEMORY,
    PRIME_OUT_OF_MEMORY,
    INVALID_VALUE,
    VALUE_NOT_NATURAL,
    PRIME_GEN_FAILURE,
    UNKNOWN_ERROR
} StatusCode;

StatusCode validateNumInStr(const char *str);
StatusCode validateNumOfPrime(const int number);
int convertStrToInt(const char *str);
int* bubbleSort(const int arr[],const int n);
int* getNPrimeNumbersSieve(const int n);
int getMaxNum(const int* numbers, const int n);

#endif
