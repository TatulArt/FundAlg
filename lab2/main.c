#include "./include/myLib.h"

int main() {
    char amountStr[11];
    printf("Введите количество строк на ввод: \n");
    fgets(amountStr, 10, stdin);

    const StatusCode validationStatus = validateNumInStr(amountStr);

    if (validationStatus != OK) {
      printf("Ошибка: %s\n", statusDescriptions[validationStatus]);
      return validationStatus;
    }

    const int numbersAmount = convertStrToInt(amountStr);

    if (numbersAmount <= 0) {
        printf("Ошибка: %s\n", statusDescriptions[VALUE_NOT_NATURAL]);
        return VALUE_NOT_NATURAL;
    }

    printf("%d\n", numbersAmount);
    int numbers[numbersAmount + 1];

    printf("Введите порядковые номера искомых простых чисел (по одному натуральному числу в каждой строке):\n");

    for (int i = 0; i < numbersAmount; i++) {
        char numStr[11];
        printf("Введите число номер %d: ", i + 1);
        fgets(numStr, 10, stdin);

        const StatusCode strValidationStatus = validateNumInStr(numStr);

        if (strValidationStatus != OK) {
          printf("%s\n", statusDescriptions[strValidationStatus]);
          return strValidationStatus;
        }

        const int number = convertStrToInt(numStr);
        const StatusCode numValidationStatus = validateNumOfPrime(number);

        if (numValidationStatus != OK) {
            printf("%s\n", statusDescriptions[numValidationStatus]);
        }

        numbers[i] = number;
    }

    const int maxNum = getMaxNum(numbers, numbersAmount);
    const int* primes = getNPrimeNumbersSieve(maxNum);

    printf("\n");
    for (int i = 0; i < numbersAmount; i++) {
        printf("Простое число номер %d: %d\n", numbers[i], primes[numbers[i] - 1]);
    }
}