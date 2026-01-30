#include "../include/functions.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* argv[]){
    char flag = '\0';
    ArgsStatus argsStatus = NumberOfArgs(argc);

    switch (argsStatus) {
    case ARGS_OK:
        break;

    case TOO_FEW_ARGS:
        printf("Not enough args\n");
        return INVALID_INPUT;
    
    case TOO_MANY_ARGS:
        printf("Too many args\n");
        return INVALID_INPUT;
    }

    ParseFlagStatus flagStatus = ParseFlag(argv[1], &flag);

    switch (flagStatus) {
    case FLAG_PARSED:
        break;

    case FLAG_NULL_PTR:
        printf("NULL PTR error");
        return INVALID_INPUT;

    case UNKNOWN_FLAG:
        printf("Unknown flag: %s\n", argv[1]);
        return INVALID_INPUT;

    case NOT_A_FLAG:
        printf("Second argument is not a flag: %s\n", argv[1]);
        return INVALID_INPUT;
    }

    switch (flag) {
        case 'q':{
            if (argc != 6) {
                printf("Not suitable number of args. Must be 4 for flag %c", flag);
                return INVALID_INPUT;
            }

            double FnumberE;
            double FnumberA;
            double FnumberB;
            double FnumberC;

            ParseNumberStatus frstValidateStatus = ValidateFloat(argv[2], &FnumberE);

            switch (frstValidateStatus) {
            case NUMBER_NULL_PTR:
                printf("NULL PTR error");
                return INVALID_INPUT;
            case OK_NUMBER:
                break;
            case DOUBLE_OVERFLOW:
                printf("Impossible to convert: overflow\n");
                return OVERFLOW;
            case NOT_DIGITS_IN_NUMBER:
                printf("Non-digits in number: %s\n", argv[2]);
                return INVALID_INPUT;
            default:
                return UNKNOWN_ERROR;
            }

            if (FnumberE <= 0){
                printf("Epsilon must be > 0");
                return INVALID_INPUT;
            }

            ParseNumberStatus secValidateStatus = ValidateFloat(argv[3], &FnumberA);

            switch (secValidateStatus){
            case OK_NUMBER:
                break;
            case NUMBER_NULL_PTR:
                printf("NULL PTR error");
                return INVALID_INPUT;
            case DOUBLE_OVERFLOW:
                printf("Impossible to convert: overflow\n");
                return OVERFLOW;
            case NOT_DIGITS_IN_NUMBER:
                printf("Non-digits in number: %s\n", argv[3]);
                return INVALID_INPUT;
            default:
                return UNKNOWN_ERROR;
            }

            ParseNumberStatus trdValidateStatus = ValidateFloat(argv[4], &FnumberB);

            switch (trdValidateStatus){
            case OK_NUMBER:
                break;
            case DOUBLE_OVERFLOW:
                printf("Impossible to convert: overflow\n");
                return OVERFLOW;
            case NOT_DIGITS_IN_NUMBER:
                printf("Non-digits in number: %s\n", argv[4]);
                return INVALID_INPUT;
            default:
                return UNKNOWN_ERROR;
            }

            ParseNumberStatus frthValidateStatus = ValidateFloat(argv[5], &FnumberC);

            switch (frthValidateStatus){
            case OK_NUMBER:
                break;
            case DOUBLE_OVERFLOW:
                printf("Impossible to convert: overflow\n");
                return OVERFLOW;
            case NOT_DIGITS_IN_NUMBER:
                printf("Non-digits in number: %s\n", argv[5]);
                return INVALID_INPUT;
            default:
                return UNKNOWN_ERROR;
            }

            double *result = malloc(sizeof(double) * 4);
            if (!result){
                printf("Memory allocation error\n");
                return MEMORY_ERROR;
            }

            PrintUniqueRes(FnumberE, FnumberA, FnumberB, FnumberC, result);
            free(result);
            break;
        }
        case 'm':{
            if (argc != 4){
                printf("Not suitable number of args. Must be 2 for flag %c", flag);
                return INVALID_INPUT;
            }
            int number1 = 0;
            int number2 = 0;

            ParseNumberStatus numberStatus1 = ParseNumber(argv[2], &number1);
            switch (numberStatus1){
            case OK_NUMBER:
                break;
            case NUMBER_NULL_PTR:
                printf("NULL PTR error");
                return INVALID_INPUT;
            case NOT_DIGITS_IN_NUMBER:
                printf("Non-digits in number: %s\n", argv[2]);
                return INVALID_INPUT;
            case NUMBER_INT_OVERFLOW:
                printf("Number overflow: %s\n", argv[2]);
                return OVERFLOW;
            default:
                return UNKNOWN_ERROR;
            }

            ParseNumberStatus numberStatus2 = ParseNumber(argv[3], &number2);
            switch (numberStatus2){
            case OK_NUMBER:
                break;
            case NUMBER_NULL_PTR:
                printf("NULL PTR error");
                return INVALID_INPUT;
            case NOT_DIGITS_IN_NUMBER:
                printf("Non-digits in number: %s\n", argv[3]);
                return INVALID_INPUT;
            case NUMBER_INT_OVERFLOW:
                printf("Number overflow: %s\n", argv[3]);
                return OVERFLOW;
            default:
                return UNKNOWN_ERROR;
            }

            DevisibleStatus devStatus = DevisibleOrNot(number1, number2);
            switch (devStatus){
            case ZERO_ERROR:
                printf("First number mustn't be 0\n");
                return INVALID_INPUT;
            case DEVISIBLE:
                printf("%d is multiple of %d\n", number2, number1);
                break;
            case NOT_DEVISIBLE:
                printf("%d is not multiple of %d\n", number2, number1);
                break;
            }
            break;
        }
        case 't':{
            if (argc != 6){
                printf("Not suitable number of args. Must be 4 for flag %c", flag);
                return INVALID_INPUT;
            }
            double FnumberE;
            double FnumberA;
            double FnumberB;
            double FnumberC;

            ParseNumberStatus frstValidateStatus = ValidateFloat(argv[2], &FnumberE); 
            switch (frstValidateStatus){
            case NUMBER_NULL_PTR:
                printf("NULL PTR error");
                return INVALID_INPUT;
            case OK_NUMBER:
                break;
            case DOUBLE_OVERFLOW:
                printf("Impossible to convert: overflow\n");
                return OVERFLOW;
            case NOT_DIGITS_IN_NUMBER:
                printf("Non-digits in number: %s\n", argv[2]);
                return INVALID_INPUT;
            default:
                return UNKNOWN_ERROR;
            }

            if (FnumberE <= 0){
                printf("Epsilon must be > 0");
                return INVALID_INPUT;
            }
            ParseNumberStatus secValidateStatus = ValidateFloat(argv[3], &FnumberA); 
            switch (secValidateStatus){
            case OK_NUMBER:
                break;
            case NUMBER_NULL_PTR:
                printf("NULL PTR error");
                return INVALID_INPUT;
            case DOUBLE_OVERFLOW:
                printf("Impossible to convert: overflow\n");
                return OVERFLOW;
            case NOT_DIGITS_IN_NUMBER:
                printf("Non-digits in number: %s\n", argv[3]);
                return INVALID_INPUT;
            default:
                return UNKNOWN_ERROR;
            }

            ParseNumberStatus trdValidateStatus = ValidateFloat(argv[4], &FnumberB); 
            switch (trdValidateStatus){
            case OK_NUMBER:
                break;
            case NUMBER_NULL_PTR:
                printf("NULL PTR error");
                return INVALID_INPUT;
            case DOUBLE_OVERFLOW:
                printf("Impossible to convert: overflow\n");
                return OVERFLOW;
            case NOT_DIGITS_IN_NUMBER:
                printf("Non-digits in number: %s\n", argv[4]);
                return INVALID_INPUT;
            default:
                return UNKNOWN_ERROR;
            }

            ParseNumberStatus frthValidateStatus = ValidateFloat(argv[5], &FnumberC); 
            switch (frthValidateStatus){
            case OK_NUMBER:
                break;
            case NUMBER_NULL_PTR:
                printf("NULL PTR error");
                return INVALID_INPUT;
            case DOUBLE_OVERFLOW:
                printf("Impossible to convert: overflow\n");
                return OVERFLOW;
            case NOT_DIGITS_IN_NUMBER:
                printf("Non-digits in number: %s\n", argv[5]);
                return INVALID_INPUT;
            default:
                return UNKNOWN_ERROR;
            }

            TriangleStatus TriStatus = IsRightTriangle(FnumberE, FnumberA, FnumberB, FnumberC);
            switch (TriStatus){
            case NEGATIVE_SIDES:
                printf("Sides of triangle must be > 0\n");
                return INVALID_INPUT;
            case IS_RIGHT:
                printf("Triangle with sides %f %f %f can be right", FnumberA, FnumberB, FnumberC);
                break;
            case NOT_RIGHT:
                printf("Triangle with sides %f %f %f can't be right", FnumberA, FnumberB, FnumberC);
                break;
        }
        break;
    }
    default:
        printf("Unknown flag\n");
        return INVALID_INPUT;
    }
    return 0;
}
