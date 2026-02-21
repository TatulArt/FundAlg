#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int isWordChar(char c) {
    return isprint((unsigned char)c) && !isspace((unsigned char)c);
}

static void removeTrailingSpaces(char* line) {
    if (!line) return;
    int len = (int)strlen(line);
    while (len > 0 && isspace((unsigned char)line[len - 1])) {
        len--;
    }
    line[len] = '\0';
}

static int findOptimalBreak(const char* line, int start_pos) {
    int line_len = (int)strlen(line);

    if (start_pos + 80 >= line_len) {
        return line_len;
    }

    int last_space = -1;
    for (int i = start_pos + 79; i >= start_pos; i--) {
        if (i < line_len && isspace((unsigned char)line[i])) {
            last_space = i;
            break;
        }
    }

    if (last_space != -1 && last_space > start_pos) {
        return last_space;
    }

    for (int i = start_pos + 80; i < line_len; i++) {
        if (isspace((unsigned char)line[i])) {
            return i;
        }
    }

    return (start_pos + 80 < line_len) ? start_pos + 80 : line_len;
}

static StatusCode justifyChunk(char* chunk, int target_length) {
    int current_length = (int)strlen(chunk);

    if (current_length >= target_length || current_length == 0) {
        return SUCCESS;
    }

    int spaces_needed = target_length - current_length;

    int word_count = 0;
    int in_word = 0;

    for (int i = 0; i < current_length; i++) {
        if (isWordChar(chunk[i])) {
            if (!in_word) {
                word_count++;
                in_word = 1;

            }
        } else {
            in_word = 0;
        }
    }

    int gap_count = word_count - 1;
    if (gap_count <= 0)
        return SUCCESS;

    int spaces_per_gap = spaces_needed / gap_count;
    int extra_spaces = spaces_needed % gap_count;

    int added_spaces = 0;

    for (int i = current_length - 1; i >= 0; i--) {
        if (i > 0 && isWordChar(chunk[i]) && !isWordChar(chunk[i - 1])) {

            int spaces_to_add = spaces_per_gap + (extra_spaces > 0 ? 1 : 0);
            if (extra_spaces > 0) extra_spaces--;

            memmove(&chunk[i + spaces_to_add], &chunk[i], current_length - i + added_spaces + 1);
            for (int j = 0; j < spaces_to_add; j++) {
                chunk[i + j] = ' ';
            }

            added_spaces += spaces_to_add;
        }
    }

    return SUCCESS;
}

StatusCode formatLine(const char* line, char** result) {
    if (!line || !result) return ERROR_NULL_POINTER;

    size_t line_len = strlen(line);

    if (line_len == 0) {
        *result = malloc(1);
        if (!*result) return ERROR_MEMORY_ALLOCATION;
        (*result)[0] = '\0';
        return SUCCESS;
    }

    if (line_len <= 80) {
        *result = malloc(line_len + 1);
        if (!*result) return ERROR_MEMORY_ALLOCATION;
        strcpy(*result, line);
        return SUCCESS;
    }

    *result = malloc(1);
    if (!*result) return ERROR_MEMORY_ALLOCATION;
    (*result)[0] = '\0';

    int pos = 0;
    StatusCode status = SUCCESS;

    while (pos < (int)line_len && status == SUCCESS) {
        int break_pos = findOptimalBreak(line, pos);

        int chunk_len = break_pos - pos;
        char chunk[256];
        strncpy(chunk, line + pos, chunk_len);
        chunk[chunk_len] = '\0';
        removeTrailingSpaces(chunk);

        int current_chunk_len = (int)strlen(chunk);

        if (break_pos < (int)line_len && current_chunk_len < 80 && current_chunk_len > 0) {
            status = justifyChunk(chunk, 80);
            if (status != SUCCESS) break;
        }

        size_t old_len = strlen(*result);
        size_t new_len = old_len + strlen(chunk) + 2; // +2 для \n и \0
        char* new_result = realloc(*result, new_len);
        if (!new_result) {
            status = ERROR_MEMORY_ALLOCATION;
            break;
        }
        *result = new_result;

        if (old_len > 0)
            strcat(*result, "\n");

        strcat(*result, chunk);

        pos = break_pos;
        while (pos < (int)line_len && isspace((unsigned char)line[pos]))
            pos++;

    }

    return status;
}

StatusCode formatFile(FILE* input, FILE* output) {
    if (!input || !output) return ERROR_NULL_POINTER;

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    StatusCode status = SUCCESS;

    while ((read = getline(&line, &len, input)) != -1) {
        if (read > 0 && line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        char* formatted = NULL;
        status = formatLine(line, &formatted);

        if (status != SUCCESS) break;

        if (fprintf(output, "%s\n", formatted) < 0) {
            status = ERROR_FILE_WRITE;
            free(formatted);
            break;
        }

        free(formatted);
    }

    free(line);

    if (ferror(input)) {
        return ERROR_FILE_READ;
    }

    return status;
}