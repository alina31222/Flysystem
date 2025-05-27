#include "filesystem.h"
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

FILE* open_fs(const char* name) {
    FILE* fs = fopen(name, "a+");
    if (!fs) {
        perror("Ошибка открытия файловой системы");
    }
    return fs;
}

char* read_file(const char* fs, const char* file) {
    FILE* f = open_fs(fs);
    if (!f) return NULL;

    char* result = NULL;
    char line[MAX_LINE];
    int found = 0;
    long start = 0;
    long end = 0;

    fseek(f, 0, SEEK_SET);
    while (fgets(line, MAX_LINE, f)) {
        line[strcspn(line, "\n")] = 0;
        if (strcmp(line, file) == 0) {
            found = 1;
            start = ftell(f);
            continue;
        }
        if (found && line[0] == '/') {
            end = ftell(f) - strlen(line) - 1;
            break;
        }
    }

    if (found) {
        if (end == 0) {
            fseek(f, 0, SEEK_END);
            end = ftell(f);
        }
        
        long length = end - start;
        result = malloc(length + 1);
        if (result) {
            fseek(f, start, SEEK_SET);
            size_t bytes = fread(result, 1, length, f);
            result[bytes] = '\0';
        }
    }

    fclose(f);
    return result;
}

int delete_file(const char* fs, const char* file) {
    FILE* f = open_fs(fs);
    if (!f) return -1;

    char temp[] = "temp.fs";
    FILE* t = fopen(temp, "w");
    if (!t) {
        fclose(f);
        return -1;
    }

    char line[MAX_LINE];
    int skip = 0;

    fseek(f, 0, SEEK_SET);
    while (fgets(line, MAX_LINE, f)) {
        line[strcspn(line, "\n")] = 0;
        if (strcmp(line, file) == 0) {
            skip = 1;
            continue;
        }
        if (skip && line[0] == '/') {
            skip = 0;
            continue;
        }
        if (!skip) {
            fprintf(t, "%s\n", line);
        }
    }

    fclose(f);
    fclose(t);
    
    remove(fs);
    rename(temp, fs);
    return 0;
}

int create_file(const char* fs, const char* file, const char* content) {
    FILE* f = open_fs(fs);
    if (!f) return -1;

    fseek(f, 0, SEEK_END);
    fprintf(f, "%s\n%s\n/\n", file, content);
    
    fclose(f);
    return 0;
}

int update_file(const char* fs, const char* file, const char* new_content) {
    if (delete_file(fs, file) != 0) {
        return -1;
    }
    return create_file(fs, file, new_content);
}