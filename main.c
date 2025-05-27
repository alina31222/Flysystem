#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD 256
#define MAX_ARGS 3

void show_help() {
    printf("Выберите действие:\n");
    printf("1. Создать новый файл\n");
    printf("2. Удалить файл\n");
    printf("3. Изменить содержимое файла\n");
    printf("4. Прочитать содержимое файла\n");
    printf("5. Выйти из программы\n");
}

int main() {
    char fs[] = "my_filesystem.fs";
    char cmd[MAX_CMD];
    char* args[MAX_ARGS];
    
    printf("Простая файловая система\n");
    
    while (1) {
        show_help();
        printf("Введите номер команды: ");
        if (!fgets(cmd, MAX_CMD, stdin)) {
            continue;
        }
        
        cmd[strcspn(cmd, "\n")] = 0;
        
        // Проверяем, что введена одна цифра
        if (strlen(cmd) != 1 || cmd[0] < '1' || cmd[0] > '5') {
            printf("Ошибка: введите число от 1 до 5\n");
            continue;
        }

        switch (cmd[0]) {
            case '1': // Создать
                printf("Введите имя файла и содержимое (через пробел): ");
                if (!fgets(cmd, MAX_CMD, stdin)) {
                    continue;
                }
                cmd[strcspn(cmd, "\n")] = 0;
                
                args[0] = strtok(cmd, " ");
                args[1] = strtok(NULL, " ");
                if (args[0] && args[1]) {
                    if (create_file(fs, args[0], args[1]) == 0) {
                        printf("Файл успешно создан\n");
                    } else {
                        printf("Ошибка создания файла\n");
                    }
                } else {
                    printf("Ошибка: укажите имя файла и содержимое\n");
                }
                break;

            case '2': // Удалить
                printf("Введите имя файла: ");
                if (!fgets(cmd, MAX_CMD, stdin)) {
                    continue;
                }
                cmd[strcspn(cmd, "\n")] = 0;
                
                if (strlen(cmd) > 0) {
                    if (delete_file(fs, cmd) == 0) {
                        printf("Файл успешно удалён\n");
                    } else {
                        printf("Ошибка удаления файла\n");
                    }
                } else {
                    printf("Ошибка: укажите имя файла\n");
                }
                break;

            case '3': // Изменить
                printf("Введите имя файла и новое содержимое (через пробел): ");
                if (!fgets(cmd, MAX_CMD, stdin)) {
                    continue;
                }
                cmd[strcspn(cmd, "\n")] = 0;
                
                args[0] = strtok(cmd, " ");
                args[1] = strtok(NULL, " ");
                if (args[0] && args[1]) {
                    if (update_file(fs, args[0], args[1]) == 0) {
                        printf("Файл успешно изменён\n");
                    } else {
                        printf("Ошибка изменения файла\n");
                    }
                } else {
                    printf("Ошибка: укажите имя файла и новое содержимое\n");
                }
                break;

            case '4': // Прочитать
                printf("Введите имя файла: ");
                if (!fgets(cmd, MAX_CMD, stdin)) {
                    continue;
                }
                cmd[strcspn(cmd, "\n")] = 0;
                
                if (strlen(cmd) > 0) {
                    char* content = read_file(fs, cmd);
                    if (content) {
                        printf("Содержимое файла:\n%s\n", content);
                        free(content);
                    } else {
                        printf("Файл не найден или ошибка чтения\n");
                    }
                } else {
                    printf("Ошибка: укажите имя файла\n");
                }
                break;

            case '5': // Выход
                printf("Выход...\n");
                return 0;

            default:
                printf("Ошибка: неизвестная команда\n");
                break;
        }
    }

    return 0;
}