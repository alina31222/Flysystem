# Flysystem
Фальванова

Имя файла, начинающееся с символа "/".
Содержимое файла, состоящее из одной или нескольких строк.
Разделитель "/" для обозначения конца содержимого файла.

Пример структуры файловой системы в файле (например, my_filesystem.fs):
/file1.txt Hello, World!
Second line
/file2.txt Document content

Файловая система поддерживает меню для выполнения операций.
Описание функций

1. open_fs - Открывает файл, представляющий файловую систему, в режиме добавления и чтения (a+). Если файл не существует, он будет создан
FILE* open_fs(const char* name);

2. read_file - Выводит содержимое файла
char* read_file(const char* fs, const char* file);
fs — имя файла файловой системы.
file — имя файла, содержимое которого нужно прочитать.
Выводит содержимое файла или сообщение об ошибке

3. delete_file - Удаляет файл из файловой системы
int delete_file(const char* fs, const char* file);
fs — имя файла файловой системы.
file — имя файла для удаления.
0 успешное удаление, -1 ошибка

4.create_file - Создает новый файл в файловой системе
int create_file(const char* fs, const char* file, const char* content);
fs — имя файла файловой системы.
file — имя создаваемого файла.
content — содержимое файла.
Возвращает: 0 успешное создание, -1 ошибка

5. update_file - Изменяет содержимое существующего файла
int update_file(const char* fs, const char* file, const char* new_content);
fs — имя файла файловой системы.
file — имя файла для обновления.
new_content — новое содержимое файла.
Возвращает: 0 успешное обновление, -1 ошибка


6. Выход из программы


Компиляция и запуск:
Для компиляции программы выполните следующую команду в терминале:
gcc main.c filesystem.c -o flysystem
Эта команда компилирует файлы main.c и filesystem.c, создавая исполняемый файл flysystem.
Для запуска программы выполните: ./flysystem

Пример работы:
Выберите действие:
1. Создать новый файл
2. Удалить файл
3. Изменить содержимое файла
4. Прочитать содержимое файла
5. Выйти из программы

1
Введите имя файла и содержимое (через пробел): aa.txt aa
Файл успешно создан

Выберите действие:
1. Создать файл
2. Изменить файл
3. Просмотреть файл
4. Удалить файл
5. Выход

3
Введите имя файла и новое содержимое (через пробел): aa.txt ww
Файл успешно изменён

Выберите действие:
1. Создать файл
2. Изменить файл
3. Просмотреть файл
4. Удалить файл
5. Выход

5
Выход...
