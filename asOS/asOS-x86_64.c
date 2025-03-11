#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>  // Для mkdir
#include <windows.h> // Для SetConsoleTextAttribute
#include <stdbool.h>

int is_spac_script_exists(const char* script_name) {
	char path[256];
    snprintf(path, sizeof(path), "C:\\asOS\\packages\\%s.spac", script_name);

    FILE* file = fopen(path, "r");
    if (file) {
        fclose(file);
        return 1; // Скрипт существует
    }
    return 0; // Скрипт не существует
}

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

// Установка жёлтого цвета текста
void set_yellow_color() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

// Локализация
typedef struct {
    char booting[100];
    char welcome[100];
    char file_created[100];
    char file_creation_failed[100];
    char file_not_found[100];
    char file_deleted[100];
    char file_deletion_failed[100];
    char directory_changed[100];
    char directory_change_failed[100];
    char directory_created[100];
    char directory_creation_failed[100];
    char current_directory_error[100];
    char user_registered[100];
    char user_limit_reached[100];
    char user_logged_in[100];
    char user_logged_out[100];
    char invalid_credentials[100];
    char no_user_logged_in[100];
    char language_set[100];
    char unknown_command[100];
    char shutting_down[100];
    char help_message[2000];
    char user_deleted[100];
    char user_restricted[100];
    char user_granted[100];
    char user_not_found[100];
    char permission_denied[100];
    char permission_disabled[100];
    char permission_enabled[100];
} Locale;

typedef struct {
    char username[50];
    char password[50];
    char shortname[20];
    int permissions;
} User;

Locale english = {
    "asOS is booting...",
    "Welcome to asOS!",
    "File '%s' created.",
    "Failed to create file '%s'.",
    "File '%s' not found.",
    "File '%s' deleted.",
    "Failed to delete file '%s'.",
    "Changed directory to: %s",
    "Failed to change directory to: %s",
    "Directory '%s' created.",
    "Failed to create directory '%s'.",
    "Error getting current directory.",
    "User '%s' registered.",
    "User limit reached.",
    "User '%s' logged in.",
    "User '%s' logged out.",
    "Invalid username or password.",
    "No user is currently logged in.",
    "Language set to %s.",
    "Unknown command: %s",
    "Shutting down asOS...",
    "Available commands:\n"
    " -> help - Show this help message\n"
    " -> create <filename> <content> - Create a file\n"
    " -> read <filename> - Read a file\n"
    " -> rm/del <filename> - Delete a file\n"
    " -> ls / dir - List files in current directory\n"
    " -> cd <path> - Change directory\n"
    " -> mkdir <path> - Create a directory\n"
    " -> run <program> - Run an external program\n"
    " -> about - Show information about asOS\n"
    " -> register - Register a new user\n"
    " -> login - Login as a user\n"
    " -> logout - Logout current user\n"
    " -> setlang <language> - Set language (English/Russian) (BETA)\n"
    " -> users - List all users\n"
    " -> deleteuser <username> - Delete a user\n"
    " -> restrict <username> - Restrict a user\n"
    " -> grant <username> - Grant permissions to a user\n"
    " -> disableperm <username> <permission> - Disable a permission for a user\n"
    " -> enableperm <username> <permission> - Enable a permission for a user\n"
	" -> np <filename> - asOS Notepad\n"
	" -> pk - Process Killer (Task Manager)\n"
" -> pac [install/update/uninstall/ --version]\n    - PAC System (Package for asOS based on C)\n"
    " -> exit - Shutdown asOS\n",
    "User '%s' deleted.",
    "User '%s' restricted.",
    "User '%s' granted permissions.",
    "User '%s' not found.",
    "Permission denied.",
    "Permission '%s' disabled for user '%s'.",
    "Permission '%s' enabled for user '%s'."
};

Locale russian = {
    "asOS загружается...",
    "Добро пожаловать в asOS!",
    "Файл '%s' создан.",
    "Не удалось создать файл '%s'.",
    "Файл '%s' не найден.",
    "Файл '%s' удалён.",
    "Не удалось удалить файл '%s'.",
    "Директория изменена на: %s",
    "Не удалось изменить директорию на: %s",
    "Директория '%s' создана.",
    "Не удалось создать директорию '%s'.",
    "Ошибка получения текущей директории.",
    "Пользователь '%s' зарегистрирован.",
    "Достигнут лимит пользователей.",
    "Пользователь '%s' вошёл в систему.",
    "Пользователь '%s' вышел из системы.",
    "Неверное имя пользователя или пароль.",
    "Нет текущего пользователя в системе.",
    "Язык изменён на %s.",
    "Неизвестная команда: %s",
    "Завершение работы asOS...",
    "Доступные команды:\n"
    " -> help - Показать это сообщение\n"
    " -> create <имя_файла> <содержимое> - Создать файл\n"
    " -> read <имя_файла> - Прочитать файл\n"
    " -> rm/del <имя_файла> - Удалить файл\n"
    " -> ls / dir - Список файлов в текущей директории\n"
    " -> cd <путь> - Изменить директорию\n"
    " -> mkdir <путь> - Создать директорию\n"
    " -> run <программа> - Запустить внешнюю программу\n"
    " -> about - Информация о asOS\n"
    " -> register - Зарегистрировать нового пользователя\n"
    " -> login - Войти как пользователь\n"
    " -> logout - Выйти из системы\n"
    " -> setlang <язык> - Установить язык (English/Russian) (БЕТА)\n"
    " -> users - Список всех пользователей\n"
    " -> deleteuser <имя_пользователя> - Удалить пользователя\n"
    " -> restrict <имя_пользователя> - Ограничить пользователя\n"
    " -> grant <имя_пользователя> - Вернуть разрешения пользователю\n"
    " -> disableperm <имя_пользователя> <разрешение> - Отключить разрешение для пользователя\n"
    " -> enableperm <имя_пользователя> <разрешение> - Включить разрешение для пользователя\n"
	" -> np <имя_файла> - asOS Блокнот\n"
	" -> pk - Process Killer (Диспетчер задач)\n"
" -> pac [install/update/uninstall/ --version]\n    - PAC Система (Пакет для asOS созданный на C)\n"
    " -> exit - Завершить работу asOS\n",
    "Пользователь '%s' удалён.",
    "Пользователь '%s' ограничен.",
    "Пользователь '%s' получил разрешения.",
    "Пользователь '%s' не найден.",
    "Доступ запрещён.",
    "Разрешение '%s' отключено для пользователя '%s'.",
    "Разрешение '%s' включено для пользователя '%s'."
};

Locale* current_locale = &english; // По умолчанию язык English

// Массив пользователей (в реальной системе это должно быть в базе данных)
User users[10];
int user_count = 0;

// Текущий пользователь
User* current_user = NULL;

// Разрешения
#define PERM_CREATE         (1 << 0)
#define PERM_DELETE         (1 << 1)
#define PERM_READ           (1 << 2)
#define PERM_MKDIR          (1 << 3)
#define PERM_CD             (1 << 4)
#define PERM_RUN            (1 << 5)
#define PERM_MANAGE_USERS   (1 << 6)
#define PERM_MODIFY_KERNEL  (1 << 7) // Новое разрешение на изменение ядра
#define PERM_MODIFY_WINDOWS (1 << 8) // Новое разрешение на изменение Windows

// Функция для загрузки пользователей из файла
void load_users() {
    FILE* file = fopen("users.cfg", "r");
    if (file) {
        while (fscanf(file, "%49[^:]:%49[^:]:%19[^:]:%d\n", users[user_count].username, users[user_count].password, users[user_count].shortname, &users[user_count].permissions) == 4) {
            user_count++;
            if (user_count >= 10) break;
        }
        fclose(file);
    }
}

// Функция для сохранения пользователей в файл
void save_users() {
    FILE* file = fopen("users.cfg", "w");
    if (file) {
        for (int i = 0; i < user_count; i++) {
            fprintf(file, "%s:%s:%s:%d\n", users[i].username, users[i].password, users[i].shortname, users[i].permissions);
        }
        fclose(file);
    }
}

// Функция для создания файла
void create_file(const char* filename, const char* content) {
    char command[256];
    snprintf(command, sizeof(command), "asOS-notepad %s", filename);
    system(command);
}

// Функция для чтения файла
void read_file(const char* filename) {
    if (current_user && (current_user->permissions & PERM_READ)) {
        FILE* file = fopen(filename, "r");
        if (file) {
            char content[1000];
            fgets(content, sizeof(content), file);
            fclose(file);
            printf("Content of '%s':\n%s\n", filename, content);
        } else {
            printf("%s\n", current_locale->file_not_found, filename);
        }
    } else {
        printf("%s\n", current_locale->permission_denied);
    }
}

// Функция для удаления файла
void delete_file(const char* filename) {
    if (current_user && (current_user->permissions & PERM_DELETE)) {
        if (remove(filename) == 0) {
            printf("%s\n", current_locale->file_deleted, filename);
        } else {
            printf("%s\n", current_locale->file_deletion_failed, filename);
        }
    } else {
        printf("%s\n", current_locale->permission_denied);
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
    if (getcwd(buffer, size) != NULL) {
        printf("", buffer);
    } else {
        printf("ERROR 303");
    }
}

// Функция для регистрации нового пользователя
void register_user() {
    if (user_count >= 10) {
        printf("%s\n", current_locale->user_limit_reached);
        return;
    }

    char username[50];
    char password[50];
    char shortname[20];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter shortname: ");
    scanf("%s", shortname);

    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    strcpy(users[user_count].shortname, shortname);
    users[user_count].permissions = PERM_CREATE | PERM_DELETE | PERM_READ | PERM_MKDIR | PERM_CD | PERM_RUN; // По умолчанию все разрешения, кроме управления ядром и Windows
    user_count++;

    printf("%s\n\n", current_locale->user_registered, username);
    save_users();
}

// Функция для входа пользователя
void login_user() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            current_user = &users[i];
            printf("User '%s' logged in.\n", username);
            return;
        }
    }

    printf("Invalid username or password.\n");
}

// Функция для выхода пользователя
void logout_user() {
    if (current_user) {
        printf("%s\n\n", current_locale->user_logged_out, current_user->username);
        current_user = NULL;
    } else {
        printf("%s\n\n", current_locale->no_user_logged_in);
    }
}

// Функция для удаления пользователя
void delete_user(const char* username) {
    if (current_user && (current_user->permissions & PERM_MANAGE_USERS)) {
        for (int i = 0; i < user_count; i++) {
            if (strcmp(users[i].username, username) == 0) {
                for (int j = i; j < user_count - 1; j++) {
                    users[j] = users[j + 1];
                }
                user_count--;
                printf("%s\n\n", current_locale->user_deleted, username);
                save_users();
                return;
            }
        }
        printf("%s\n\n", current_locale->user_not_found, username);
    } else {
        printf("%s\n\n", current_locale->permission_denied);
    }
}

// Функция для ограничения пользователя
void restrict_user(const char* username) {
    if (current_user && (current_user->permissions & PERM_MANAGE_USERS)) {
        for (int i = 0; i < user_count; i++) {
            if (strcmp(users[i].username, username) == 0) {
                users[i].permissions = PERM_READ; // Оставляем только разрешение на чтение
                printf("%s\n\n", current_locale->user_restricted, username);
                save_users();
                return;
            }
        }
        printf("%s\n\n", current_locale->user_not_found, username);
    } else {
        printf("%s\n\n", current_locale->permission_denied);
    }
}

// Функция для возвращения разрешений пользователю
void grant_user(const char* username) {
    if (current_user && (current_user->permissions & PERM_MANAGE_USERS)) {
        for (int i = 0; i < user_count; i++) {
            if (strcmp(users[i].username, username) == 0) {
                users[i].permissions = PERM_CREATE | PERM_DELETE | PERM_READ | PERM_MKDIR | PERM_CD | PERM_RUN; // Возвращаем все разрешения
                printf("%s\n\n", current_locale->user_granted, username);
                save_users();
                return;
            }
        }
        printf("%s\n\n", current_locale->user_not_found, username);
    } else {
        printf("%s\n\n", current_locale->permission_denied);
    }
}

// Функция для отключения разрешения у пользователя
void disable_permission(const char* username, const char* permission) {
    if (current_user && (current_user->permissions & PERM_MANAGE_USERS)) {
        for (int i = 0; i < user_count; i++) {
            if (strcmp(users[i].username, username) == 0) {
                if (strcmp(permission, "CREATE") == 0) {
                    users[i].permissions &= ~PERM_CREATE;
                } else if (strcmp(permission, "DELETE") == 0) {
                    users[i].permissions &= ~PERM_DELETE;
                } else if (strcmp(permission, "READ") == 0) {
                    users[i].permissions &= ~PERM_READ;
                } else if (strcmp(permission, "MKDIR") == 0) {
                    users[i].permissions &= ~PERM_MKDIR;
                } else if (strcmp(permission, "CD") == 0) {
                    users[i].permissions &= ~PERM_CD;
                } else if (strcmp(permission, "RUN") == 0) {
                    users[i].permissions &= ~PERM_RUN;
                } else if (strcmp(permission, "MANAGE_USERS") == 0) {
                    users[i].permissions &= ~PERM_MANAGE_USERS;
                } else if (strcmp(permission, "MODIFY_KERNEL") == 0) {
                    users[i].permissions &= ~PERM_MODIFY_KERNEL;
                } else if (strcmp(permission, "MODIFY_WINDOWS") == 0) {
                    users[i].permissions &= ~PERM_MODIFY_WINDOWS;
                } else {
                    printf("Unknown permission: %s\n\n", permission);
                    return;
                }
                printf("%s\n\n", current_locale->permission_disabled, permission, username);
                save_users();
                return;
            }
        }
        printf("%s\n\n", current_locale->user_not_found, username);
    } else {
        printf("%s\n\n", current_locale->permission_denied);
    }
}

// Функция для включения разрешения у пользователя
void enable_permission(const char* username, const char* permission) {
    if (current_user && (current_user->permissions & PERM_MANAGE_USERS)) {
        for (int i = 0; i < user_count; i++) {
            if (strcmp(users[i].username, username) == 0) {
                if (strcmp(permission, "CREATE") == 0) {
                    users[i].permissions |= PERM_CREATE;
                } else if (strcmp(permission, "DELETE") == 0) {
                    users[i].permissions |= PERM_DELETE;
                } else if (strcmp(permission, "READ") == 0) {
                    users[i].permissions |= PERM_READ;
                } else if (strcmp(permission, "MKDIR") == 0) {
                    users[i].permissions |= PERM_MKDIR;
                } else if (strcmp(permission, "CD") == 0) {
                    users[i].permissions |= PERM_CD;
                } else if (strcmp(permission, "RUN") == 0) {
                    users[i].permissions |= PERM_RUN;
                } else if (strcmp(permission, "MANAGE_USERS") == 0) {
                    users[i].permissions |= PERM_MANAGE_USERS;
                } else if (strcmp(permission, "MODIFY_KERNEL") == 0) {
                    users[i].permissions |= PERM_MODIFY_KERNEL;
                } else if (strcmp(permission, "MODIFY_WINDOWS") == 0) {
                    users[i].permissions |= PERM_MODIFY_WINDOWS;
                } else {
                    printf("Unknown permission: %s\n\n", permission);
                    return;
                }
                printf("%s\n\n", current_locale->permission_enabled, permission, username);
                save_users();
                return;
            }
        }
        printf("%s\n\n", current_locale->user_not_found, username);
    } else {
        printf("%s\n\n", current_locale->permission_denied);
    }
}

// Функция для вывода списка всех пользователей
void list_users() {
    printf("Users:\n");
    for (int i = 0; i < user_count; i++) {
        printf("  %s (%s) - Permissions: %s%s%s%s%s%s%s%s%s\n",
               users[i].username,
               users[i].shortname,
               (users[i].permissions & PERM_CREATE) ? "CREATE " : "",
               (users[i].permissions & PERM_DELETE) ? "DELETE " : "",
               (users[i].permissions & PERM_READ) ? "READ " : "",
               (users[i].permissions & PERM_MKDIR) ? "MKDIR " : "",
               (users[i].permissions & PERM_CD) ? "CD " : "",
               (users[i].permissions & PERM_RUN) ? "RUN " : "",
               (users[i].permissions & PERM_MANAGE_USERS) ? "MANAGE_USERS " : "",
               (users[i].permissions & PERM_MODIFY_KERNEL) ? "MODIFY_KERNEL " : "",
               (users[i].permissions & PERM_MODIFY_WINDOWS) ? "MODIFY_WINDOWS " : "");
    }
    printf("\n");
}

void pac_install(const char* path) {
    char command[256];
    snprintf(command, sizeof(command), "copy \"%s\" \"C:\\asOS\\packages\\\"", path);
    system(command);
    printf("Package installed from '%s'\n", path);

    // Проверка, что файл скопирован
    char check_command[256];
    snprintf(check_command, sizeof(check_command), "dir C:\\asOS\\packages\\");
    system(check_command);
}

void pac_version() {
    printf("PAC Manager v1.0.0\n");
}

void pac_update(const char* package, const char* path) {
    char command[256];
    snprintf(command, sizeof(command), "cp %s /asOS/packages/%s.spac", path, package);
    system(command);
    printf("Package '%s' updated from '%s'\n", package, path);
}

void pac_uninstall(const char* package) {
    char command[256];
    snprintf(command, sizeof(command), "rm /asOS/packages/%s.spac", package);
    system(command);
    printf("Package '%s' uninstalled\n", package);
}

void pac_command(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: pac <install|uninstall|update|--version>\n");
        return;
    }

    if (strcmp(argv[1], "install") == 0) {
        if (argc < 3) {
            printf("Usage: pac install <path>\n");
            return;
        }
        pac_install(argv[2]);
    } else if (strcmp(argv[1], "uninstall") == 0) {
        if (argc < 3) {
            printf("Usage: pac uninstall <package>\n");
            return;
        }
        pac_uninstall(argv[2]);
    } else if (strcmp(argv[1], "update") == 0) {
        if (argc < 4) {
            printf("Usage: pac update <package> <path>\n");
            return;
        }
        pac_update(argv[2], argv[3]);
    } else if (strcmp(argv[1], "--version") == 0) {
        pac_version();
    } else {
        printf("Unknown pac command: %s\n", argv[1]);
    }
}

void create_packages_directory() {
    if (_mkdir("C:\\asOS\\packages") == 0) {
        printf("Created directory: C:\\asOS\\packages\n");
    } else {
        printf("Directory already exists or could not be created.\n");
    }
}

void run_spac_script(const char* script_name) {
	void set_console_title(const char* command) {
        char title[256];
        snprintf(title, sizeof(title), "asOS - SCRIPT PAC - %s", command);
        SetConsoleTitle(title);
    } 
    char command[256];
    snprintf(command, sizeof(command), "C:\\asOS\\packages\\%s.spac", script_name);

    FILE* file = fopen(command, "r");
    if (!file) {
        printf("Script '%s' not found.\n", script_name);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Убираем символ новой строки
        line[strcspn(line, "\n")] = 0;

        // Пропускаем комментарии
        if (line[0] == '#') continue;

        if (strncmp(line, "run(", 4) == 0) {
            // Извлекаем команду из run("command")
            char command[2000];
            sscanf(line, "run(\"%[^\"]\")", command);
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
				} else if (strcmp(cmd, "pac") == 0) {
					// Создаем массив argv для команды pac
					char* pac_argv[10];
					int pac_argc = 0;

						pac_argv[pac_argc++] = cmd; // Первый аргумент — "pac"
					if (arg1) pac_argv[pac_argc++] = arg1;
					if (arg2) pac_argv[pac_argc++] = arg2;

					pac_command(pac_argc, pac_argv);
				} else if (strcmp(cmd, "help") == 0) {
					set_console_title(cmd);
					printf("%s\n\n", current_locale->help_message);
				} else if (strcmp(cmd, "pk") == 0) {
					set_console_title(cmd);
					system("process_killer");
				} else if (strcmp(cmd, "connect") == 0) {
					set_console_title(cmd);
					if (arg1 != NULL && arg2 != NULL) {
						char command[256];
						snprintf(command, sizeof(command), "remote_client %s %s", arg1, arg2);
						system(command);
					} else {
						printf("Usage: connect <server_ip> <password>\n\n");
					}
				} else if (strcmp(cmd, "startserver") == 0) {
					set_console_title(cmd);
					system("remote_server");
				} else if (strcmp(cmd, "create") == 0) {
					if (arg1 != NULL && arg2 != NULL) {
						create_file(arg1, arg2);
					} else {
						printf("Usage: create <filename> <content>\n\n");
					}
				} else if (strcmp(cmd, "read") == 0) {
					set_console_title(cmd);
					if (arg1 != NULL) {
						read_file(arg1);
					} else {
						printf("Usage: read <filename>\n\n");
					}
				} else if (strcmp(cmd, "rm") == 0 || strcmp(cmd, "del") == 0) {
					set_console_title(cmd);
					if (arg1 != NULL) {
						delete_file(arg1);
					} else {
						printf("Usage: rm/del <filename>\n\n");
					}
				} else if (strcmp(cmd, "ls") == 0 || strcmp(cmd, "dir") == 0) {
					set_console_title(cmd);
					list_files();
					printf("\n");
				} else if (strcmp(cmd, "cd") == 0) {
					set_console_title(cmd);
					if (arg1 != NULL) {
						change_directory(arg1);
					} else {
						printf("Usage: cd <path>\n\n");
					}
				} else if (strcmp(cmd, "mkdir") == 0) {
					set_console_title(cmd);
					if (arg1 != NULL) {
						create_directory(arg1);
					} else {
						printf("Usage: mkdir <path>\n\n");
					}
				} else if (strcmp(cmd, "run") == 0) {
					set_console_title(cmd);
					if (arg1 != NULL) {
						system(arg1);
					} else {
						printf("Usage: run <program>\n\n");
					}
				} else if (strcmp(cmd, "about") == 0) {
					set_console_title(cmd);
					printf("---asOS---\n");
					printf("Version: alpha-0.2\n");
					printf("Creators: NTheCuteDrone, DeepSeek\n\n");
					printf("The sub-system based on C & motives = Absolute Solver from Murder Drones\n\n");
					printf("Thanks for using asOS!\n\n");
				} else if (strcmp(cmd, "register") == 0) {
					set_console_title(cmd);
					register_user();
				} else if (strcmp(cmd, "login") == 0) {
					set_console_title(cmd);
					login_user();
				} else if (strcmp(cmd, "logout") == 0) {
					set_console_title(cmd);
					logout_user();
				} else if (strcmp(cmd, "setlang") == 0) {
					set_console_title(cmd);
					if (arg1 != NULL) {
						if (strcmp(arg1, "English") == 0) {
							current_locale = &english;
							printf(current_locale->language_set, "English");
							printf("\n\n");
						} else if (strcmp(arg1, "Russian") == 0) {
							current_locale = &russian;
							printf(current_locale->language_set, "Russian");
							printf("\n\n");
						} else {
							printf("Usage: setlang <English/Russian>\n\n");
						}
					} else {
						printf("Usage: setlang <English/Russian>\n\n");
					}
				} else if (strcmp(cmd, "users") == 0) {
					set_console_title(cmd);
					list_users();
				} else if (strcmp(cmd, "deleteuser") == 0) {
					set_console_title(cmd);
					if (arg1 != NULL) {
                    delete_user(arg1);
					} else {
						printf("Usage: deleteuser <username>\n\n");
					}
				} else if (strcmp(cmd, "restrict") == 0) {
					set_console_title(cmd);
					if (arg1 != NULL) {
						restrict_user(arg1);
					} else {
						printf("Usage: restrict <username>\n\n");
					}
				} else if (strcmp(cmd, "grant") == 0) {
					set_console_title(cmd);
					if (arg1 != NULL) {
						grant_user(arg1);
					} else {
						printf("Usage: grant <username>\n\n");
					}
				} else if (strcmp(cmd, "disableperm") == 0) {
					set_console_title(cmd);
					if (arg1 != NULL && arg2 != NULL) {
						disable_permission(arg1, arg2);
					} else {
						printf("Usage: disableperm <username> <permission>\n\n");
					}
				} else if (strcmp(cmd, "enableperm") == 0) {
					set_console_title(cmd);
					if (arg1 != NULL && arg2 != NULL) {
						enable_permission(arg1, arg2);
					} else {
						printf("Usage: enableperm <username> <permission>\n\n");
					}
				} else if (strcmp(cmd, "exit") == 0) {
					set_console_title(cmd);
					printf("%s\n\n", current_locale->shutting_down);
					break;
				} else if (strcmp(cmd, "np") == 0) {
					set_console_title(cmd);
					if (arg1 != NULL) {
						char command[256];
						snprintf(command, sizeof(command), "asOS-notepad %s", arg1);
						system(command);
					} else {
						printf("Usage: np <filename>\n\n");
					}
				} else {
					// Если команда не найдена, ищем SPAC-скрипт
					printf("Searching for SPAC script: %s\n", cmd); // Отладочное сообщение
					if (is_spac_script_exists(cmd)) {
						printf("SPAC script found: %s\n", cmd); // Отладочное сообщение
						run_spac_script(cmd);
					} else {
						printf("SPAC script not found: %s\n", cmd); // Отладочное сообщение
						printf(current_locale->unknown_command, cmd);
						printf("\n\n");
					}
				}
			}
        } else if (strncmp(line, "print(", 6) == 0) {
            // Извлекаем текст из print("text")
            char text[2000];
            sscanf(line, "print(\"%[^\"]\")", text);
            printf("%s\n", text);
        } else {
            printf("Unknown command: %s\n", line);
        }
    }

    fclose(file);
}


// Основная оболочка asOS
void shell() {
    void set_console_title(const char* command) {
        char title[256];
        snprintf(title, sizeof(title), "asOS - %s", command);
        SetConsoleTitle(title);
    }
    char command[1000];
    char current_path[MAX_PATH];

    while (1) {
		get_current_directory(current_path, sizeof(current_path));
        // Получаем текущий путь
        printf("asOS@%s:\\\%s\\ > ", (current_user ? current_user->shortname : "NULL"), current_path);

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
            } else if (strcmp(cmd, "pac") == 0) {
                // Создаем массив argv для команды pac
                char* pac_argv[10];
                int pac_argc = 0;

                pac_argv[pac_argc++] = cmd; // Первый аргумент — "pac"
                if (arg1) pac_argv[pac_argc++] = arg1;
                if (arg2) pac_argv[pac_argc++] = arg2;

                pac_command(pac_argc, pac_argv);
            } else if (strcmp(cmd, "help") == 0) {
                set_console_title(cmd);
                printf("%s\n\n", current_locale->help_message);
            } else if (strcmp(cmd, "pk") == 0) {
                set_console_title(cmd);
                system("process_killer");
            } else if (strcmp(cmd, "connect") == 0) {
                set_console_title(cmd);
                if (arg1 != NULL && arg2 != NULL) {
                    char command[256];
                    snprintf(command, sizeof(command), "remote_client %s %s", arg1, arg2);
                    system(command);
                } else {
                    printf("Usage: connect <server_ip> <password>\n\n");
                }
            } else if (strcmp(cmd, "startserver") == 0) {
                set_console_title(cmd);
                system("remote_server");
            } else if (strcmp(cmd, "create") == 0) {
                if (arg1 != NULL && arg2 != NULL) {
                    create_file(arg1, arg2);
                } else {
                    printf("Usage: create <filename> <content>\n\n");
                }
            } else if (strcmp(cmd, "read") == 0) {
                set_console_title(cmd);
                if (arg1 != NULL) {
                    read_file(arg1);
                } else {
                    printf("Usage: read <filename>\n\n");
                }
            } else if (strcmp(cmd, "rm") == 0 || strcmp(cmd, "del") == 0) {
                set_console_title(cmd);
                if (arg1 != NULL) {
                    delete_file(arg1);
                } else {
                    printf("Usage: rm/del <filename>\n\n");
                }
            } else if (strcmp(cmd, "ls") == 0 || strcmp(cmd, "dir") == 0) {
                set_console_title(cmd);
                list_files();
                printf("\n");
            } else if (strcmp(cmd, "cd") == 0) {
                set_console_title(cmd);
                if (arg1 != NULL) {
                    change_directory(arg1);
                } else {
                    printf("Usage: cd <path>\n\n");
                }
            } else if (strcmp(cmd, "mkdir") == 0) {
                set_console_title(cmd);
                if (arg1 != NULL) {
                    create_directory(arg1);
                } else {
                    printf("Usage: mkdir <path>\n\n");
                }
            } else if (strcmp(cmd, "run") == 0) {
                set_console_title(cmd);
                if (arg1 != NULL) {
                    system(arg1);
                } else {
                    printf("Usage: run <program>\n\n");
                }
            } else if (strcmp(cmd, "about") == 0) {
                set_console_title(cmd);
                printf("---asOS---\n");
                printf("Version: alpha-0.2\n");
                printf("Creators: NTheCuteDrone, DeepSeek\n\n");
                printf("The sub-system based on C & motives = Absolute Solver from Murder Drones\n\n");
                printf("Thanks for using asOS!\n\n");
            } else if (strcmp(cmd, "register") == 0) {
                set_console_title(cmd);
                register_user();
            } else if (strcmp(cmd, "login") == 0) {
                set_console_title(cmd);
                login_user();
            } else if (strcmp(cmd, "logout") == 0) {
                set_console_title(cmd);
                logout_user();
            } else if (strcmp(cmd, "setlang") == 0) {
                set_console_title(cmd);
                if (arg1 != NULL) {
                    if (strcmp(arg1, "English") == 0) {
                        current_locale = &english;
                        printf(current_locale->language_set, "English");
                        printf("\n\n");
                    } else if (strcmp(arg1, "Russian") == 0) {
                        current_locale = &russian;
                        printf(current_locale->language_set, "Russian");
                        printf("\n\n");
                    } else {
                        printf("Usage: setlang <English/Russian>\n\n");
                    }
                } else {
                    printf("Usage: setlang <English/Russian>\n\n");
                }
            } else if (strcmp(cmd, "users") == 0) {
                set_console_title(cmd);
                list_users();
            } else if (strcmp(cmd, "deleteuser") == 0) {
                set_console_title(cmd);
                if (arg1 != NULL) {
                    delete_user(arg1);
                } else {
                    printf("Usage: deleteuser <username>\n\n");
                }
            } else if (strcmp(cmd, "restrict") == 0) {
                set_console_title(cmd);
                if (arg1 != NULL) {
                    restrict_user(arg1);
                } else {
                    printf("Usage: restrict <username>\n\n");
                }
            } else if (strcmp(cmd, "grant") == 0) {
                set_console_title(cmd);
                if (arg1 != NULL) {
                    grant_user(arg1);
                } else {
                    printf("Usage: grant <username>\n\n");
                }
            } else if (strcmp(cmd, "disableperm") == 0) {
                set_console_title(cmd);
                if (arg1 != NULL && arg2 != NULL) {
                    disable_permission(arg1, arg2);
                } else {
                    printf("Usage: disableperm <username> <permission>\n\n");
                }
            } else if (strcmp(cmd, "enableperm") == 0) {
                set_console_title(cmd);
                if (arg1 != NULL && arg2 != NULL) {
                    enable_permission(arg1, arg2);
                } else {
                    printf("Usage: enableperm <username> <permission>\n\n");
                }
            } else if (strcmp(cmd, "exit") == 0) {
                set_console_title(cmd);
                printf("%s\n\n", current_locale->shutting_down);
                break;
            } else if (strcmp(cmd, "np") == 0) {
                set_console_title(cmd);
                if (arg1 != NULL) {
                    char command[256];
                    snprintf(command, sizeof(command), "asOS-notepad %s", arg1);
                    system(command);
                } else {
                    printf("Usage: np <filename>\n\n");
                }
            } else {
				// Если команда не найдена, ищем SPAC-скрипт
				printf("Searching for SPAC script: %s\n", cmd); // Отладочное сообщение
				if (is_spac_script_exists(cmd)) {
					printf("SPAC script found: %s\n", cmd); // Отладочное сообщение
					run_spac_script(cmd);
				} else {
					printf("SPAC script not found: %s\n", cmd); // Отладочное сообщение
					printf(current_locale->unknown_command, cmd);
					printf("\n\n");
				}
            }
        }
    }
}

int main() {
    // Включение поддержки ANSI-кодов
    enable_ansi_support();

    // Установка кодировки консоли на UTF-8
    set_console_to_utf8();

    // Установка жёлтого цвета текста
    set_yellow_color();

    // Загрузка пользователей из файла
    load_users();

    // Загрузка стандартного пользователя
    if (true) {
        strcpy(users[user_count].username, "SYS");
        strcpy(users[user_count].password, "sys");
        strcpy(users[user_count].shortname, "SYS");
        users[user_count].permissions = PERM_CREATE | PERM_DELETE | PERM_READ | PERM_MKDIR | PERM_CD | PERM_RUN | PERM_MANAGE_USERS | PERM_MODIFY_KERNEL | PERM_MODIFY_WINDOWS;
        user_count++;
        save_users();
    }
	
	create_packages_directory();

    printf("%s\n", current_locale->booting);
    printf("%s\n\n", current_locale->welcome);
	
	// Вход в систему
    while (1) {
        printf("Logging in as SYS (password: sys)...\n");
        strcpy(users[0].username, "SYS");
        strcpy(users[0].password, "sys");
        current_user = &users[0];
        break;
    }

    // Запуск оболочки
    shell();

    return 0;
}