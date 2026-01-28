#include "../include/functions.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main(int argc, const char* argv[]){
    int* ans;
    CheckNumbersStatus checkStatus1 = check_numbers(&ans, 4, 10, 1/3.0, 0.1, 0.2, 0.54567876);
    if (StatusProcessing(checkStatus1) == OK_PROC){
        for (int i = 0; i < 4; ++i) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    free(ans);

    CheckNumbersStatus checkStatus2 = check_numbers(&ans, 2, 255, 1.0/255, 1/51.0, 0.5);
    if (StatusProcessing(checkStatus2) == OK_PROC){
        for (int i = 0; i < 2; ++i) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    free(ans);

    CheckNumbersStatus checkStatus3 = check_numbers(&ans, 5, 3, 0.1, 1.0/3, 0.33333, 0.5, 0.0);
    if (StatusProcessing(checkStatus3) == OK_PROC){
        for (int i = 0; i < 5; ++i) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    free(ans);

    CheckNumbersStatus checkStatus4 = check_numbers(&ans, 2, 2, 0.9, 0.5);
    if (StatusProcessing(checkStatus4) == OK_PROC){
        for (int i = 0; i < 2; ++i) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    free(ans);

    return 0;
}