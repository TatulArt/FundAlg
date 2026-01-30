#include "functions.h"
#include <string.h>
#include <ctype.h>

int charToV(char c) {
    c = toupper(c);

    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    }
}

int findMinBase(const char* num_str) {
    int maxDigit = 0;
    int len = strlen(num_str);
    int startIndex = 0;
    
    if (len > 0 && num_str[0] == '-') {
        startIndex = 1;
    }
    
    for (int i = startIndex; i < len; i++) {
        int digitValue = charToV(num_str[i]);
        if (digitValue == -1) {
            return -1; 
        }
        if (digitValue > maxDigit) {
            maxDigit = digitValue;
        }
    }
    
    return (maxDigit + 1 > 2) ? maxDigit + 1 : 2;
}
int findSignValue(const char* num_str) {
    if (strlen(num_str) > 0 && num_str[0] == '-') {
        return -1;
    }
    return 1;
}

long long convertToDecimal(const char* num_str, int base) {
    long long result = 0;
    int len = strlen(num_str);
    int startIndex = 0;
    
    if (len > 0 && num_str[0] == '-') {
        startIndex = 1;
    }
    
    for (int i = startIndex; i < len; i++) {
        int digitValue = charToV(num_str[i]);
        result = result * base + digitValue;
        if (result < 0)
            return -1;
    }
    
    return result;
}

void removeZeros(char* str) {
    int len = strlen(str);
    int start = 0;
    int isNegative = 0;

    if (len > 0 && str[0] == '-') {
        isNegative = 1;
        start = 1;
    }

    while (start < len - 1 && str[start] == '0') {
        start++;
    }

    if (start > (isNegative ? 1 : 0)) {
        if (isNegative) {
            memmove(str + 1, str + start, len - start + 1);
            str[0] = '-';
        } else {
            memmove(str, str + start, len - start + 1);
        }
    }
    
    if ((len == 1 && str[0] == '0') || (len == 2 && str[0] == '-' && str[1] == '0')) {
        str[0] = '0';
        str[1] = '\0';
    }
}