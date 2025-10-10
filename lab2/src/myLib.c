#include "../include/myLib.h"

StatusCode validateNumInStr(const char *str) {
    if (str == NULL || *str == '\0' || *str == '\n') {
        return INVALID_VALUE;
    }
    short int strLen = 0;

    for (short int i = 0; str[i] != '\0'; i++) {
        strLen++;

        if (!(str[i] >= '0' && str[i] <= '9') && str[0] != '-' && str[i] != '\n') {
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

StatusCode validateNumOfPrime(const int number) {
    if (number <= 0) {
        return VALUE_NOT_NATURAL;
    }

    if (number > 500) {
        return PRIME_OUT_OF_MEMORY;
    }

    return OK;
}

// Перевод x в long из строкового представления
int convertStrToInt(const char *str) {
    char *p;
    const long conv = strtol(str, &p, 10);

    // Ловим ошибки при переводе
    if ((*p != '\0' && *p != '\n')|| conv > INT_MAX || conv < INT_MIN) {
        return INT_MAX;
    }

    return conv;
}

int getMaxNum(const int* numbers, const int n) {
    int max = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }

    return max;
}

int* getNPrimeNumbersSieve(const int n) {
    const int upperBound = n * n + 1;

    int* sieve = (int*)calloc(upperBound + 1, sizeof(int));
    if (sieve == NULL) {
        printf("Ошибка: %s\n", statusDescriptions[MEMORY_ALLOCATION_FAILED]);
        return NULL;
    }

    for (int i = 0; i < upperBound; i++) {
        sieve[i] = i + 1;
    }

    for (int i = 0; i < upperBound; i++) {
        if (sieve[i] == 1) {
            continue;
        }

        for (int j = i; j < upperBound; j++) {
            if (sieve[j] == 1 || sieve[j] == sieve[i]) {
                continue;
            }

            if (sieve[j] % sieve[i] == 0) {
                sieve[j] = 1;
            }
        }
    }

    int* primes = (int*)malloc(n * sizeof(int));
    if (primes == NULL) {
        printf("Ошибка: %s\n", statusDescriptions[MEMORY_ALLOCATION_FAILED]);
        free(sieve);
        return NULL;
    }

    int count = 0;

    for (int i = 0; i <= upperBound && count < n; i++) {
        if (sieve[i] != 1) {
            primes[count++] = sieve[i];
        }
    }

    free(sieve);
    return primes;
}

