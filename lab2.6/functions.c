#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stddef.h>
#include <ctype.h>
#include <math.h>

int ParseNumber(const char *StrNumber, int *number) {
    char *endptr;
    long long lgnum = strtoll(StrNumber, &endptr, 10);
    if (*endptr != '\0') {
        return NOT_DIGITS_IN_NUMBER;
    }
    if (lgnum < 0) {
        return NOT_POSITIVE_NUMBER;
    }
    if (lgnum > INT_MAX) {
        return NUMBER_INT_OVERFLOW;
    }
    *number = (int)lgnum;
    return OK_NUMBER;
}

int isValidName(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) {
            return 0;
        }
    }
    return 1;
}

void toLowerCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

void printStudent(const Student *student) {
    printf("%u %s %s %s ",
           student->id, student->name, student->surname, student->group);
    for (int i = 0; i < 5; i++) {
        printf("%c ", student->marks[i]);
    }
    printf("\n");
}

ReadStatus readStudents(const char *filename, int *count, Student* students, int *capacity) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return READ_FILE_ERROR;
    }
    char buffer[256];
    int id;
    char name[50];
    char surname[50];
    char group[20];
    unsigned char marks[5];
    int size = 0;

    while(fgets(buffer, sizeof(buffer), file)){
        Student temp;
        temp.marks = malloc(5 * sizeof(unsigned char));
        if (sscanf(buffer, "%u %s %s %s %c %c %c %c %c", &temp.id, temp.name, temp.surname, temp.group, (char*)&temp.marks[0], (char*)&temp.marks[1], (char*)&temp.marks[2], (char*)&temp.marks[3], (char*)&temp.marks[4]) != 9){
            free(temp.marks);
            continue;
        }
        if (!isValidName(temp.name) || !isValidName(temp.surname)) {
            free(temp.marks);
            continue;
        }

        if (size >= *capacity) {
            *capacity *= 2;
            Student *newStudents = realloc(students, *capacity * sizeof(Student));
            if (!newStudents) {
                free(temp.marks);
                break;
            }
            students = newStudents;
        }
        students[size++] = temp;
    }
    fclose(file);
    *count = size;
    
    if (size == 0) {
        free(students);
        return NOTHING_READED;
    }
    return OK_READED;
}

void freeStudents(Student *students, int count) {
    for (int i = 0; i < count; i++) {
        free(students[i].marks);
    }
    free(students);
}

void searchById(Student *students, int count, unsigned int id) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printStudent(&students[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("No student found with ID: %u\n", id);
    }
}

void searchBySurname(Student *students, int count, const char *surname) {
    int found = 0;
    char searchLower[50];
    char studentLower[50];
    
    strcpy(searchLower, surname);
    toLowerCase(searchLower);
    
    for (int i = 0; i < count; i++) {
        strcpy(studentLower, students[i].surname);
        toLowerCase(studentLower);
        
        if (strcmp(studentLower, searchLower) == 0) {
            printStudent(&students[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No student found with surname: %s\n", surname);
    }
}

void searchByName(Student *students, int count, const char *name) {
    int found = 0;
    char searchLower[50];
    char studentLower[50];
    
    strcpy(searchLower, name);
    toLowerCase(searchLower);
    
    for (int i = 0; i < count; i++) {
        strcpy(studentLower, students[i].name);
        toLowerCase(studentLower);
        
        if (strcmp(studentLower, searchLower) == 0) {
            printStudent(&students[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No student found with name: %s\n", name);
    }
}

void searchByGroup(Student *students, int count, const char *group) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].group, group) == 0) {
            printStudent(&students[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No students found in group: %s\n", group);
    }
}

int compareById(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    return (studentA->id > studentB->id) - (studentA->id < studentB->id);
}

int compareBySurname(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    return strcmp(studentA->surname, studentB->surname);
}

int compareByName(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    return strcmp(studentA->name, studentB->name);
}

int compareByGroup(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    return strcmp(studentA->group, studentB->group);
}

double calculateAverageGrade(const Student *student) {
    double sum = 0;
    for (int i = 0; i < 5; i++) {
        int value = 0;
        if ('A'<=student->marks[i] && student->marks[i]<='F' && student->marks[i] != 'E'){
            if (student->marks[i] == 'F'){
                value = 1;
            } else {
            value = student->marks[i] - (char)'A' + 5;
            }
        } else {value = student->marks[i] - '0';}
        sum += value;
    }
    return sum / 5;
}

double calculateOverallAverage(Student *students, int count) {
    if (count == 0){
        return 0;
    }
    double totalSum = 0;
    for (int i = 0; i < count; i++) {
        totalSum += calculateAverageGrade(&students[i]);
    }
    return totalSum / count;
}

void writeStudentByIdToTraceFile(Student *students, int count, unsigned int id, const char *traceFile) {
    FILE *file = fopen(traceFile, "a");
    if (!file) {
        printf("Error opening trace file.\n");
        return;
    }
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            fprintf(file, "%d %s %s %s ", students[i].id, students[i].surname, students[i].name, students[i].group);
            for (int j = 0; j < 5; j++) {
                fprintf(file, "%c ", students[i].marks[j]);
            }
            fprintf(file, "\n");
            found = 1;
            break;
        }
    } 
    if (!found) {
        printf("No student found with ID: %u\n", id);
    }
    fclose(file);
}

void writeStudentsAboveAverageToTraceFile(Student *students, int count, const char *traceFile) {
    FILE *file = fopen(traceFile, "a");
    if (!file) {
        printf("Error opening trace file.\n");
        return;
    }
    double overallAverage = calculateOverallAverage(students, count);
    printf("\nStudents with average grade above overall average (%.2f) where writen:\n", overallAverage);
    int found = 0;
    for (int i = 0; i < count; i++) {
        double studentAverage = calculateAverageGrade(&students[i]);
        if (studentAverage > overallAverage) {
            fprintf(file, "%d %s %s %s ", students[i].id, students[i].surname, students[i].name, students[i].group);
            for (int j = 0; j < 5; j++) {
                fprintf(file, "%c ", students[i].marks[j]);
            }
            fprintf(file, "\n");
            found = 1;
        }
    }
    
    if (!found) {
        fprintf(file, "No students found above average.\n");
    }
    
    fclose(file);
}