#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>

FILE* open_fs(const char* name);
char* read_file(const char* fs, const char* file);
int delete_file(const char* fs, const char* file);
int create_file(const char* fs, const char* file, const char* content);
int update_file(const char* fs, const char* file, const char* new_content);

#endif