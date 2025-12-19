#include "../include/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include <math.h>

ArgsStatus NumberOfArgs(int argc){
    if (argc < 4){
        return TOO_FEW_ARGS;
    }
    if (argc > 6){
        return TOO_MANY_ARGS;
    }
    return ARGS_OK;
}

ParseNumberStatus ParseNumber(const char *StrNumber, int *number) {
    if (StrNumber == NULL || number == NULL) {
        return NUMBER_NULL_PTR;
    }
    char *endptr;
    long long lgnum = strtoll(StrNumber, &endptr, 10);
    if (*endptr != '\0') {
        return NOT_DIGITS_IN_NUMBER;
    }
    if (lgnum > INT_MAX || lgnum < INT_MIN) {
        return NUMBER_INT_OVERFLOW;
    }
    *number = (int)lgnum;
    return OK_NUMBER;
}

ParseNumberStatus ValidateFloat(const char *StrNumber, double *Fnumber) {
    if (StrNumber == NULL || Fnumber == NULL) {
        return NUMBER_NULL_PTR;
    }
    char *endptr;
    double dubN = strtod(StrNumber, &endptr);
    if (*endptr != '\0') {
        return NOT_DIGITS_IN_NUMBER;
    }
    if (isinf(dubN) || isnan(dubN)) {
        return DOUBLE_OVERFLOW;
    }
    *Fnumber = dubN;
    return OK_NUMBER;
}

ParseFlagStatus ParseFlag(const char *InputedFlag, char *flag) {
    if (InputedFlag == NULL || flag == NULL) {
        return FLAG_NULL_PTR;
    }
    if (InputedFlag[0] != '-' && InputedFlag[0] != '/') {
        return NOT_A_FLAG;
    }
    if (InputedFlag[2] != '\0') {
        return UNKNOWN_FLAG;
    }
    *flag = InputedFlag[1];
    return FLAG_PARSED;
}

EqSolutions EquationSolve(double e, double a, double b, double c, double *result) {
    if (result == NULL){
        return EQ_NULL_PTR;
    }

    if (fabs(a) < e) {
        if (fabs(b) < e) {
            if (fabs(c) < e) {
                return INF_SOLUTIONS;
            }

            return NO_SOLUTIONS;
        }

        if (fabs(c) < e) {
            result[0] = 0;
        } else {
            result[0] = -c/b;
        }

        return ONE_SOLUTION;
    }

    const double d = b*b - 4 * a * c;
    if (d < 0) {
        return NO_SOLUTIONS;
    }

    if (d < e) {
        if (fabs(c) < e){
            result[0] = 0;
        } else {
            result[0] = -b/(2 * a);
        }
        return ONE_SOLUTION;
    }

    const double sqrtD = sqrt(d);
    result[0] = (-b + sqrtD) / (2 * a);
    result[1] = (-b - sqrtD) / (2 * a);
    return TWO_SOLUTIONS;
}

void PrintEquationRes(double *result, EqSolutions EqStatus, double a, double b, double c){
    printf("a = %f, b = %f, c = %f\n", a, b, c);
    if (result == NULL) {
        printf("Error: result pointer is NULL\n");
        return;
    }
    switch (EqStatus) {
  case NO_SOLUTIONS:
    printf("No solutions in equation.\n");
    break;
  case INF_SOLUTIONS:
    printf("Infinite solutions in equation.\n");
    break;
  case ONE_SOLUTION:
    printf("One solution in equation: %f\n", result[0]);
    break;
  case TWO_SOLUTIONS:
    printf("Two solutions in equation: %f and %f\n", result[0], result[1]);
    break;
  }
  printf("==========================================================================\n");
}

DevisibleStatus DevisibleOrNot(int number1, int number2){
    if (number1 == 0){
        return ZERO_ERROR;
    }
    if (abs(number2) % abs(number1) == 0){
        return DEVISIBLE;
    } else {
        return NOT_DEVISIBLE;
    }          
}

TriangleStatus IsRightTriangle(double e, double a, double b, double c){
    if (a < e || b < e || c < e){
        return NEGATIVE_SIDES;
    }
    if (fabs(a * a + b * b - c * c) < e || fabs(a * a + c * c - b * b) < e || fabs(b * b + c * c - a * a) < e) {
        return IS_RIGHT;
    }
    return NOT_RIGHT;
}

void PrintUniqueRes(double FnumberE, double FnumberA, double FnumberB, double FnumberC, double * result){
    if (result == NULL) {
        printf("Error: result pointer is NULL\n");
        return;
    }

    double allCombinations[6][3] = {
        {FnumberA, FnumberB, FnumberC},
        {FnumberA, FnumberC, FnumberB},
        {FnumberB, FnumberC, FnumberA},
        {FnumberB, FnumberA, FnumberC},
        {FnumberC, FnumberB, FnumberA},
        {FnumberC, FnumberA, FnumberB}
    };

    double uniqueCombinations[6][3];
    int uniqueCount = 0;

    for (int i = 0; i < 6; i++) {
        int isUnique = 1;
        
        for (int j = 0; j < uniqueCount; j++) {
            if (fabs(allCombinations[i][0] - uniqueCombinations[j][0]) < FnumberE &&
                fabs(allCombinations[i][1] - uniqueCombinations[j][1]) < FnumberE &&
                fabs(allCombinations[i][2] - uniqueCombinations[j][2]) < FnumberE) {
                isUnique = 0;
                break;
            }
        }
        
        if (isUnique) {
            uniqueCombinations[uniqueCount][0] = allCombinations[i][0];
            uniqueCombinations[uniqueCount][1] = allCombinations[i][1];
            uniqueCombinations[uniqueCount][2] = allCombinations[i][2];
            
            EqSolutions sol = EquationSolve(FnumberE, allCombinations[i][0], allCombinations[i][1], allCombinations[i][2], result);
            if (sol == EQ_NULL_PTR) {
                printf("No solutions in equation.\n");
                return;
            }

            PrintEquationRes(result, sol, allCombinations[i][0], allCombinations[i][1], allCombinations[i][2]);
            uniqueCount++;
            result[0] = 0.0;
            result[1] = 0.0;
        }
    }
}



