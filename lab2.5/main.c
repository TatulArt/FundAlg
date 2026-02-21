#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        printf("Ошибка: много аргументов\n");
        return 1;
    }

    char input_filename[256];
    char output_filename[256];
    FILE* input_file = NULL;
    FILE* output_file = NULL;
    StatusCode result;

    printf("Введите имя входного файла: ");
    scanf("%255s", input_filename);

    input_file = fopen(input_filename, "r");
    if (!input_file) {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    printf("Введите имя выходного файла: ");
    scanf("%255s", output_filename);

    output_file = fopen(output_filename, "a");
    if (!output_file) {
        printf("Ошибка создания файла\n");
        fclose(input_file);
        return 1;
    }

    result = formatFile(input_file, output_file);

    fclose(input_file);
    fclose(output_file);

    switch (result) {
        case SUCCESS:
            printf("Форматирование успешно завершено!\n");
            return EXIT_SUCCESS;

        case ERROR_NULL_POINTER:
            printf("Ошибка: передан нулевой указатель\n");
            break;

        case ERROR_FILE_OPEN:
            printf("Ошибка: не удалось открыть файл\n");
            break;

        case ERROR_FILE_READ:
            printf("Ошибка: не удалось прочитать файл\n");
            break;

        case ERROR_FILE_WRITE:
            printf("Ошибка: не удалось записать в файл\n");
            break;

        case ERROR_MEMORY_ALLOCATION:
            printf("Ошибка: недостаточно памяти\n");
            break;

        case ERROR_INVALID_INPUT:
            printf("Ошибка: неверные входные данные\n");
            break;

        case ERROR_EMPTY_STRING:
            printf("Ошибка: пустая строка\n");
            break;

        default:
            printf("Неизвестная ошибка: %d\n", result);
            break;
    }

    return EXIT_FAILURE;
}