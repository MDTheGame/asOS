#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Включение поддержки ANSI-кодов
void enable_ansi_support() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

// Установка кодировки консоли на UTF-8
void set_console_to_utf8() {
    SetConsoleOutputCP(65001); // UTF-8
}

// Функция для отображения содержимого файла и его редактирования
void notepad(const char* filename) {
    char content[10000] = {0}; // Буфер для содержимого файла
    FILE* file;

    // Если файл существует, загружаем его содержимое
    file = fopen(filename, "r");
    if (file) {
        fread(content, 1, sizeof(content) - 1, file);
        fclose(file);
    }

    // Основной цикл редактирования
    while (1) {
        system("cls"); // Очистка экрана
        printf("=== asOS Notepad ===\n");
        printf("Editing: %s\n\n", filename);
        printf("%s\n\n", content);
        printf("Commands: [Ctrl+S] Save | [Ctrl+Q] Quit without saving\n");

        // Обработка ввода пользователя
        char input = getchar();

        if (input == 19) { // Ctrl+S (сохранить)
            file = fopen(filename, "w");
            if (file) {
                fprintf(file, "%s", content);
                fclose(file);
                printf("\nFile saved successfully.\n");
                Sleep(1000); // Пауза для отображения сообщения
            } else {
                printf("\nFailed to save file.\n");
                Sleep(1000); // Пауза для отображения сообщения
            }
        } else if (input == 17) { // Ctrl+Q (выйти без сохранения)
            printf("\nExiting without saving.\n");
            Sleep(1000); // Пауза для отображения сообщения
            break;
        } else {
            // Добавление введенного символа в содержимое
            strncat(content, &input, 1);
        }
    }
}

int main(int argc, char* argv[]) {
    // Включение поддержки ANSI-кодов
    enable_ansi_support();

    // Установка кодировки консоли на UTF-8
    set_console_to_utf8();

    // Проверка аргументов командной строки
    if (argc < 2) {
        printf("Usage: asOS-notepad <filename>\n");
        return 1;
    }

    // Запуск блокнота
    notepad(argv[1]);

    return 0;
}