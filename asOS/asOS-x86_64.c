#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>  // Для mkdir
#include <windows.h> // Для SetConsoleTextAttribute

// Включение поддержки ANSI-кодов
void enable_ansi_support() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

// Установка жёлтого цвета текста
void set_yellow_color() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

// Функция для создания файла
void create_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%s", content);
        fclose(file);
        printf("File '%s' created.\n", filename);
    } else {
        printf("Failed to create file '%s'.\n", filename);
    }
}

// Функция для чтения файла
void read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        char content[1000];
        fgets(content, sizeof(content), file);
        fclose(file);
        printf("Content of '%s':\n%s\n", filename, content);
    } else {
        printf("File '%s' not found.\n", filename);
    }
}

// Функция для вывода списка файлов (ls/dir)
void list_files() {
    printf("Files in current directory:\n");
    system("dir");
}

// Функция для смены директории (cd)
void change_directory(const char* path) {
    if (chdir(path) == 0) {
        printf("Changed directory to: %s\n", path);
    } else {
        printf("Failed to change directory to: %s\n", path);
    }
}

// Функция для создания директории
void create_directory(const char* path) {
    if (mkdir(path) == 0) {
        printf("Directory '%s' created.\n", path);
    } else {
        printf("Failed to create directory '%s'.\n", path);
    }
}

// Получение текущего пути
void get_current_directory(char* buffer, size_t size) {
    if (getcwd(buffer, size) == NULL) {
        printf("Error getting current directory.\n");
    }
}

// Основная оболочка asOS
void shell() {
    char command[100];
    char current_path[MAX_PATH];

    while (1) {
        // Получаем текущий путь
        get_current_directory(current_path, sizeof(current_path));
        printf("SYS:/%s> ", current_path);

        // Считываем команду
        if (fgets(command, sizeof(command), stdin) != NULL) {
            // Убираем символ новой строки
            command[strcspn(command, "\n")] = 0;

            // Разбиваем команду на части
            char* cmd = strtok(command, " ");
            char* arg1 = strtok(NULL, " ");
            char* arg2 = strtok(NULL, "\n");

            if (cmd == NULL) {
                // Пустая команда (просто нажали ENTER)
                continue;
            } else if (strcmp(cmd, "help") == 0) {
                printf("Available commands:\n");
                printf("  help - Show this help message\n");
                printf("  create <filename> <content> - Create a file\n");
                printf("  read <filename> - Read a file\n");
                printf("  ls / dir - List files in current directory\n");
                printf("  cd <path> - Change directory\n");
                printf("  mkdir <path> - Create a directory\n");
                printf("  run <program> - Run an external program\n");
                printf("  about - Show information about asOS\n");
                printf("  exit - Shutdown asOS\n");
            } else if (strcmp(cmd, "create") == 0) {
                if (arg1 != NULL && arg2 != NULL) {
                    create_file(arg1, arg2);
                } else {
                    printf("Usage: create <filename> <content>\n");
                }
            } else if (strcmp(cmd, "read") == 0) {
                if (arg1 != NULL) {
                    read_file(arg1);
                } else {
                    printf("Usage: read <filename>\n");
                }
            } else if (strcmp(cmd, "ls") == 0 || strcmp(cmd, "dir") == 0) {
                list_files();
            } else if (strcmp(cmd, "cd") == 0) {
                if (arg1 != NULL) {
                    change_directory(arg1);
                } else {
                    printf("Usage: cd <path>\n");
                }
            } else if (strcmp(cmd, "mkdir") == 0) {
                if (arg1 != NULL) {
                    create_directory(arg1);
                } else {
                    printf("Usage: mkdir <path>\n");
                }
            } else if (strcmp(cmd, "run") == 0) {
                if (arg1 != NULL) {
                    system(arg1);
                } else {
                    printf("Usage: run <program>\n");
                }
            } else if (strcmp(cmd, "about") == 0) {
                printf("---asOS---\n");
                printf("Version: alpha-0.1\n");
                printf("Creators: NTheCuteDrone, DeepSeek\n\n");
                printf("The sub-system based on C & motives = Absolute Solver from Murder Drones\n\n");
                printf("Thanks for using asOS!\n");
            } else if (strcmp(cmd, "exit") == 0) {
                printf("Shutting down asOS...\n");
                break;
            } else {
                printf("Unknown command: %s\n", cmd);
            }
        }
    }
}

int main() {
    // Включение поддержки ANSI-кодов
    enable_ansi_support();

    // Установка жёлтого цвета текста
    set_yellow_color();

    printf("asOS is booting...\n");
    printf("Welcome to asOS!\n");

    // Запуск оболочки
    shell();

    return 0;
}