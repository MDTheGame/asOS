#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Функция для вывода списка процессов
void list_processes() {
    system("tasklist");
}

// Функция для завершения процесса по ID
void kill_process(int pid) {
    char command[50];
    snprintf(command, sizeof(command), "taskkill /PID %d /F", pid);
    system(command);
}

int main() {
    int choice;
    int pid;

    while (1) {
        printf("=== Process Killer ===\n");
        printf("1. List processes\n");
        printf("2. Kill process by PID\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list_processes();
                break;
            case 2:
                printf("Enter PID to kill: ");
                scanf("%d", &pid);
                kill_process(pid);
                break;
            case 3:
                printf("Exiting Process Killer...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}