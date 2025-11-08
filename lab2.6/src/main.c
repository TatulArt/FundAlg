#include "../include/functions.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char* argv[]) {
    if (argc != 3){
        printf("Invalid input\nType: %s <inputFile> <TraceFile>\n", argv[0]);
        return INVALID_INPUT;
    }
    const char *inputFile = argv[1];
    const char *traceFile = argv[2];
    remove(traceFile);
    int studentCount = 0;
    Student *students = NULL;
    int capacity = 10;
    int size = 0;

    students = malloc(capacity * sizeof(Student));
    if (!students){
        return MEMORY_ERROR;
    }
    ReadStatus readedStatus = readStudents(inputFile, &studentCount, students, &capacity);
    switch (readedStatus){
    case OK_READED:
        break;
    case NOTHING_READED:
        printf("No one valide student find\n");
        return INVALID_INPUT;
    case READ_FILE_ERROR:
        printf("Cant read file\n");
        return FILE_ERROR;
    }
    int choice;
    char StrNumber[3];
    unsigned int searchId;
    char searchStr[50];

    do {
        printf("1. Search by ID\n");
        printf("2. Search by Surname\n");
        printf("3. Search by Name\n");
        printf("4. Search by Group\n");
        printf("5. Sort by ID\n");
        printf("6. Sort by Surname\n");
        printf("7. Sort by Name\n");
        printf("8. Sort by Group\n");
        printf("9. Write student by ID to trace file\n");
        printf("10. Write students above average to trace file\n");
        printf("11. Display all students\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        scanf("%s", &StrNumber);
        ParseNumberStatus numberStatus = ParseNumber(StrNumber, &choice);
        if (numberStatus != OK_NUMBER){
            printf("Unknown command\n");
            continue;
        }
        switch (choice) {
            case 1:
                printf("Enter ID to search: ");
                scanf("%u", &searchId);
                searchById(students, studentCount, searchId);
                printf("-----------------------------------------------------------\n");
                break;

            case 2:
                printf("Enter surname to search: ");
                scanf("%s", searchStr);
                searchBySurname(students, studentCount, searchStr);
                printf("-----------------------------------------------------------\n");
                break;

            case 3:
                printf("Enter name to search: ");
                scanf("%s", searchStr);
                searchByName(students, studentCount, searchStr);
                printf("-----------------------------------------------------------\n");
                break;

            case 4:
                printf("Enter group to search: ");
                scanf("%s", searchStr);
                searchByGroup(students, studentCount, searchStr);
                printf("-----------------------------------------------------------\n");
                break;

            case 5:
                qsort(students, studentCount, sizeof(Student), compareById);
                printf("Students sorted by ID.\n");
                printf("-----------------------------------------------------------\n");
                break;

            case 6:
                qsort(students, studentCount, sizeof(Student), compareBySurname);
                printf("Students sorted by Surname.\n");
                printf("-----------------------------------------------------------\n");
                break;

            case 7:
                qsort(students, studentCount, sizeof(Student), compareByName);
                printf("Students sorted by Name.\n");
                printf("-----------------------------------------------------------\n");
                break;

            case 8:
                qsort(students, studentCount, sizeof(Student), compareByGroup);
                printf("Students sorted by Group.\n");
                printf("-----------------------------------------------------------\n");
                break;

            case 9:
                printf("Enter student ID to write to trace file: ");
                scanf("%u", &searchId);
                writeStudentByIdToTraceFile(students, studentCount, searchId, traceFile);
                printf("-----------------------------------------------------------\n");
                break;

            case 10:
                writeStudentsAboveAverageToTraceFile(students, studentCount, traceFile);
                printf("-----------------------------------------------------------\n");
                break;

            case 11:
                for (int i = 0; i < studentCount; i++) {
                    printf("%d. ", i + 1);
                    printStudent(&students[i]);
                }
                printf("-----------------------------------------------------------\n");
                break;

            case 0:
                break;

            default:
                printf("Unknown command\n");
                break;
        }
    } while (choice != 0);

    freeStudents(students, studentCount);
    return 0;
}
