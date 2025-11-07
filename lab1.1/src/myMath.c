#include "../include/myMath.h"

#define ULL_T unsigned long long

int validateNumInStr(const char *str) {
    short int strLen = 0;

    for (short int i = 0; str[i] != '\0'; i++) {
        strLen++;

        if (!(str[i] >= '0' && str[i] <= '9') && str[0] != '-') {
            return INVALID_VALUE;
        }
    }

    if (strLen > 10) {
        return OUT_OF_MEMORY;
    }

    if (str[0] == '0') {
        return INVALID_VALUE;
    }

    return OK;
}

// Перевод x в long из строкового представления
long convertStrToLong(const char *str) {
    char *p;
    const long conv = strtol(str, &p, 10);

    // Ловим ошибки при переводе
    if (*p != '\0' || conv > INT_MAX || conv < INT_MIN) {
        return INT_MAX;
    }

    return conv;
}

int validateFlag(const char *flag) {
    if (flag[0] != '-' && flag[0] != '/') {
        return INVALID_FLAG_START;
    }

    if (!(flag[1] >= 'a' && flag[1] <= 'z') || flag[2] != '\0') {
        return INVALID_FLAG_VALUE;
    }

    return OK;
}

// Вывод всех чисел в пределах 100 (включительно), кратных x в терминал
int printNumsDivisibleByX(const long x) {
    int counter = 0;

    for (int i = 1; i <= 100; i++) {
        if ((i % x) == 0) {
            printf("%d\n", i);
            counter++;
        }
    }

    return counter;
}

// Проверка числа на простоту
int isPrime(const long x) {
    for (long i = 2; i <= x / 2; i++)
        if (x % i == 0)
            return 0;

    return 1;
}

int getNumLengthInNumSys(long x, const int base) {
    int counter = 0;

    while (x > 0) {
        x /= base;
        counter++;
    }

    return counter;
}

void printNumInHex(long x) {
    const int n = getNumLengthInNumSys(x, 16);
    char *result = (char *) malloc(n * sizeof(char));

    const char *alphabet = "0123456789ABCDEF";
    int counter = 0;

    while (x > 0) {
        result[counter] = alphabet[x % 16];
        counter++;
        x /= 16;
    }

    for (int i = counter - 1; i >= 0; i--) {
        printf("%c ", result[i]);
    }

    printf("\n");
    free(result);
}

void printPowerTableXRow(const long x) {
    long *row = (long *) malloc(10 * sizeof(long));

    for (int i = 0; i < 10; i++) {
        row[i] = i + 1;

        if (i == 0) {
            printf("%ld", row[i]);
        } else {
            printf(" %11ld", row[i]);
        }
    }

    printf("\n");

    for (int i = 0; i < (x - 1); i++) {
        for (int j = 0; j < 10; j++) {
            row[j] = row[j] * (j + 1);

            if (j == 0) {
                printf("%ld", row[j]);
            } else {
                printf(" %11ld", row[j]);
            }
        }

        printf("\n");
    }

    free(row);
}

ULL_T getSumFromOneToX(const long x) {
    ULL_T sum = 0;

    for (long i = 1; i <= x; i++) {
        sum += i;
    }

    return sum;
}

ULL_T getFactorial(const long x) {
    ULL_T result = 1;
    ULL_T prevResult = 1;

    for (int i = 2; i <= x; i++) {
        prevResult = result;
        result *= i;

        if (result / i != prevResult) {
            return 0;
        }
    }

    return result;
}