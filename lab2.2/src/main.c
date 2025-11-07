#include "../include/functions.h"

#include <string.h>

int main() {
    printf("1. memchr:\n");
    char str1[] = "Hello World!";
    char *result1 = memchr(str1, 'W', 12);
    printf("   memchr('Hello World!', 'W', 12) = %s\n", result1 ? result1 : "NULL");
    printf("   Result: %s\n\n", result1 ? "FOUND" : "NOT FOUND");

    printf("2. memcmp:\n");
    char a[] = "abc";
    char b[] = "abd";
    int result2 = memcmp(a, b, 3);
    printf("   memcmp('abc', 'abd', 3) = %d\n", result2);
    printf("   Result: %s\n\n", result2 < 0 ? "abc < abd" : result2 > 0 ? "abc > abd" : "abc == abd");


    printf("3. memcpy:\n");
    char src[] = "Source";
    char dest[10];
    void *result3 = memcpy(dest, src, 7);
    printf("   memcpy(dest, 'Source', 7) = '%s'\n", (char*)result3);
    printf("   Result: %s\n\n", strcmp(dest, "Source") == 0 ? "SUCCESS" : "ERROR");

    printf("4. memset:\n");
    char buf[10];
    void *result4 = memset(buf, 'X', 5);
    buf[5] = '\0';
    printf("   memset(buf, 'X', 5) = '%s'\n", (char*)result4);
    printf("   Result: %s\n\n", strcmp(buf, "XXXXX") == 0 ? "SUCCESS" : "ERROR");

    printf("5. strncat:\n");
    char dest5[20] = "Hello";
    char *result5 = strncat(dest5, " World!", 4);
    printf("   strncat('Hello', ' World!', 4) = '%s'\n", result5);
    printf("   Result: %s\n\n", strcmp(result5, "Hello Wor") == 0 ? "SUCCESS" : "ERROR");

    printf("6. strchr:\n");
    char *result6 = strchr("Hello", 'l');
    printf("   strchr('Hello', 'l') = '%s'\n", result6 ? result6 : "NULL");
    printf("   Result: %s\n\n", result6 && strcmp(result6, "llo") == 0 ? "SUCCESS" : "ERROR");

    printf("7. strncmp:\n");
    int result7 = strncmp("Hello", "Hellp", 4);
    printf("   strncmp('Hello', 'Hellp', 4) = %d\n", result7);
    printf("   Result: %s\n\n", result7 == 0 ? "EQUAL" : "NOT EQUAL");


    printf("8. strncpy:\n");
    char dest8[10];
    char *result8 = strncpy(dest8, "Hello", 8);
    printf("   strncpy(dest, 'Hello', 8) = '");
    for(int i = 0; i < 8; i++) {
        if(dest8[i] == '\0') printf("\\0");
        else printf("%c", dest8[i]);
    }
    printf("'\n");
    printf("   Result: %s\n\n", result8 == dest8 ? "SUCCESS" : "ERROR");

    printf("9. strcspn:\n");
    size_t result9 = strcspn("Hello World", "aeiou");
    printf("   strcspn('Hello World', 'aeiou') = %zu\n", result9);
    printf("   Result: vowel found at position %zu\n\n", result9);

    printf("10. strlen:\n");
    size_t result10 = strlen("Hello");
    printf("   strlen('Hello') = %zu\n", result10);
    printf("   Result: %s\n\n", result10 == 5 ? "SUCCESS" : "ERROR");

    printf("11. strpbrk:\n");
    char *result11 = strpbrk("Hello World", "aeiou");
    printf("   strpbrk('Hello World', 'aeiou') = '%s'\n", result11 ? result11 : "NULL");
    printf("   Result: %s\n\n", result11 && strcmp(result11, "ello World") == 0 ? "SUCCESS" : "ERROR");

    printf("12. strrchr:\n");
    char *result12 = strrchr("Hello", 'l');
    printf("   strrchr('Hello', 'l') = '%s'\n", result12 ? result12 : "NULL");
    printf("   Result: %s\n\n", result12 && strcmp(result12, "lo") == 0 ? "SUCCESS" : "ERROR");

    printf("13. strstr:\n");
    char *result13 = strstr("Hello World", "World");
    printf("   strstr('Hello World', 'World') = '%s'\n", result13 ? result13 : "NULL");
    printf("   Result: %s\n\n", result13 && strcmp(result13, "World") == 0 ? "SUCCESS" : "ERROR");

    printf("14. strtok - basic test:\n");
    char str14[] = "Hello,World;Test";
    printf("   Input string: '%s'\n", str14);
    char *token1 = strtok(str14, ",;");
    char *token2 = strtok(NULL, ",;");
    char *token3 = strtok(NULL, ",;");
    printf("   Token 1: '%s'\n", token1 ? token1 : "NULL");
    printf("   Token 2: '%s'\n", token2 ? token2 : "NULL");
    printf("   Token 3: '%s'\n", token3 ? token3 : "NULL");
    printf("   Result: %s\n\n",
           token1 && token2 && token3 &&
           strcmp(token1, "Hello") == 0 &&
           strcmp(token2, "World") == 0 &&
           strcmp(token3, "Test") == 0 ? "SUCCESS" : "ERROR");

    printf("15. memchr - not found test:\n");
    char *result16 = memchr("Hello", 'x', 5);
    printf("   memchr('Hello', 'x', 5) = %s\n", result16 ? result16 : "NULL");
    printf("   Result: %s\n\n", result16 == NULL ? "SUCCESS" : "ERROR");

    printf("16. strstr - not found test:\n");
    char *result17 = strstr("Hello World", "Python");
    printf("   strstr('Hello World', 'Python') = %s\n", result17 ? result17 : "NULL");
    printf("   Result: %s\n\n", result17 == NULL ? "SUCCESS" : "ERROR");

    printf("17. strrchr - not found test:\n");
    char *result18 = strrchr("Hello", 'x');
    printf("   strrchr('Hello', 'x') = %s\n", result18 ? result18 : "NULL");
    printf("   Result: %s\n\n", result18 == NULL ? "SUCCESS" : "ERROR");
    return 0;
}