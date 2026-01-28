#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <stdlib.h>
#include <string.h>

static char *status_descriptions[] = {
    "Успех",
    "Некорректный формат числа. Число должно быть положительным",
    "Некорректный формат r. По условию задачи, значение r должно находится на отрезке [1, 5]",
    "Ошибка: Указатель на NULL"
};

enum status_codes{
    SUCCESS,
    INVALID_NUMBER,
    INVALID_R,
    NULL_POINTER,
} status_codes ;

int translate_to_base(const int number, const int r, char *result);


#endif
