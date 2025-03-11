#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция для выполнения команды asOS
void execute_command(const char* command) {
    printf("Executing: %s\n", command);
    system(command);
}

// Функция для выполнения SPAC-скрипта
void execute_spac(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file '%s'\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Убираем символ новой строки
        line[strcspn(line, "\n")] = 0;

        // Пропускаем комментарии
        if (line[0] == '#') continue;

        // Выполняем команду
        if (strncmp(line, "run(", 4) == 0) {
            // Извлекаем команду из run("command")
            char command[256];
            sscanf(line, "run(\"%[^\"]\")", command);
            execute_command(command);
        } else if (strncmp(line, "print(", 6) == 0) {
            // Извлекаем текст из print("text")
            char text[256];
            sscanf(line, "print(\"%[^\"]\")", text);
            printf("%s\n", text);
        } else {
            printf("Unknown command: %s\n", line);
        }
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <script.spac>\n", argv[0]);
        return 1;
    }

    execute_spac(argv[1]);
    return 0;
}