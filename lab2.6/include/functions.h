#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stddef.h>

typedef enum{
    OK_INPUT,
    INVALID_INPUT,
    OVERFLOW,
    ACTION_ERROR,
    MEMORY_ERROR,
    FILE_ERROR
} MainStatus;

typedef enum{
    NUMBER_INT_OVERFLOW,
    NOT_POSITIVE_NUMBER,
    NOT_DIGITS_IN_NUMBER,
    OK_NUMBER
} ParseNumberStatus;

typedef enum{
    READ_FILE_ERROR,
    NOTHING_READED,
    OK_READED
} ReadStatus;

typedef struct{
    unsigned int id;
    char name[50];
    char surname[50];
    char group[20];
    unsigned char *marks;
} Student;

int ParseNumber(const char *StrNumber, int *number);
int isValidName(const char *str);
void toLowerCase(char *str);
void printStudent(const Student *student);
ReadStatus readStudents(const char *filename, int *count, Student* students, int *capacity);
void freeStudents(Student *students, int count);
void searchById(Student *students, int count, unsigned int id);
void searchBySurname(Student *students, int count, const char *surname);
void searchByName(Student *students, int count, const char *name);
void searchByGroup(Student *students, int count, const char *group);
int compareById(const void *a, const void *b);
int compareBySurname(const void *a, const void *b);
int compareByName(const void *a, const void *b);
int compareByGroup(const void *a, const void *b);
void writeStudentByIdToTraceFile(Student *students, int count, unsigned int id, const char *traceFile);
double calculateOverallAverage(Student *students, int count);
double calculateAverageGrade(const Student *student);
void writeStudentsAboveAverageToTraceFile(Student *students, int count, const char *traceFile);


#endif //FUNCTIONS_H
