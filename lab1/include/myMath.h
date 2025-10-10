//
// Created by Артем Маевский on 18.09.2025.
//

#ifndef MYMATH_H
#define MYMATH_H

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static char *statusDescriptions[] = {
    "OK",
    "Использование программы: ./build <x> <флаг>",
    "Превышение ограничения памяти",
    "Неизвестный флаг",
    "Некорректный формат флага. Пример корректного ввода: \"-<флаг>\" либо\"/<флаг>\"",
    "Некорректный формат флага. Флаг должен состоять из одного символа латинского алфавита в нижнем регистре",
    "Некорректный формат x. Число должно состоять только из арабских цифр и не содержать ведущих нулей",
    "Ожидалось натуральное значение x",
    "Некорректный ввод: Для вывода таблицы степеней, введите значение x в диапазоне [1, 10]",
    "Неизвестная ошибка, анлак :("
};

enum StatusCodes {
    OK,
    WRONG_ARG_AMOUNT,
    OUT_OF_MEMORY,
    UNKNOWN_FLAG,
    INVALID_FLAG_START,
    INVALID_FLAG_VALUE,
    INVALID_VALUE,
    VALUE_NOT_NATURAL,
    POWER_TABLE_OUT_OF_RANGE,
    UNKNOWN_ERROR
};

long convertStrToLong(const char *str);
int validateNumInStr(const char *str);
int validateFlag(const char *flag);
int printNumsDivisibleByX(long x);
int isPrime(long x);
void printNumInHex(long x);
void printPowerTableXRow(long x);
unsigned long long getSumFromOneToX(const long x);
unsigned long long getFactorial(const long x);

#endif //MYMATH_H
