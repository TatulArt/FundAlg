#ifndef DEF_H
#define DEF_H
#include <stddef.h>

typedef enum{
    OK_INPUT,
    INVALID_INPUT,
    OVERFLOW,
    MEMORY_ERROR,
    UNKNOWN_ERROR,
} MainStatus;

typedef enum{
    ARGS_OK,
    TOO_FEW_ARGS,
    TOO_MANY_ARGS
} ArgsStatus;

typedef enum{
    NUMBER_INT_OVERFLOW,
    NOT_POSITIVE_NUMBER,
    NOT_DIGITS_IN_NUMBER,
    NUMBER_NULL_PTR,
    DOUBLE_OVERFLOW,
    OK_NUMBER
} ParseNumberStatus;

typedef enum{
    INF_SOLUTIONS,
    NO_SOLUTIONS,
    ONE_SOLUTION,
    TWO_SOLUTIONS,
    TWO_COMPLEX_SOLUTIONS,
    EQ_NULL_PTR
} EqSolutions;

typedef enum{
    UNKNOWN_FLAG,
    FLAG_PARSED,
    NOT_A_FLAG,
    FLAG_NULL_PTR
} ParseFlagStatus;

typedef enum{
    NEGATIVE_SIDES,
    IS_RIGHT,
    NOT_RIGHT
} TriangleStatus;

typedef enum{
    ZERO_ERROR,
    DEVISIBLE,
    NOT_DEVISIBLE
} DevisibleStatus;

TriangleStatus IsRightTriangle(double e, double a, double b, double c);
DevisibleStatus DevisibleOrNot(int number1, int number2);
ArgsStatus NumberOfArgs(int argc);
ParseNumberStatus ValidateFloat(const char *StrNumber, double *Fnumber);
ParseNumberStatus ParseNumber(const char *StrNumber, int *number);
ParseFlagStatus ParseFlag(const char *InputedFlag, char *flag);
EqSolutions EquationSolve(double e, double a, double b, double c, double * result);
void PrintEquationRes(double * result, EqSolutions EqStatus, double a, double b, double c);
void PrintUniqueRes(double FnumberE, double FnumberA, double FnumberB, double FnumberC, double * result);
#endif