#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 12345
#define PASSWORD "secret123"

// Функция для обработки клиента (серверная часть)
void handle_client(SOCKET client_socket) {
    char buffer[1024];
    int bytes_received;

    // Получаем пароль от клиента
    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    buffer[bytes_received] = '\0';

    if (strcmp(buffer, PASSWORD) == 0) {
        send(client_socket, "Access granted!\n", 16, 0);
        // Здесь можно добавить логику для доступа к файлам
    } else {
        send(client_socket, "Access denied!\n", 15, 0);
    }

    closesocket(client_socket);
}

// Серверная часть
void start_server() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int c;

    printf("Starting server...\n");

    // Инициализация Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize Winsock.\n");
        return;
    }

    // Создание сокета
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Failed to create socket.\n");
        return;
    }

    // Настройка сервера
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Привязка сокета
    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed.\n");
        return;
    }

    // Ожидание подключений
    listen(server_socket, 3);
    printf("Server is listening on port %d...\n", PORT);

    // Принятие подключений
    c = sizeof(struct sockaddr_in);
    while ((client_socket = accept(server_socket, (struct sockaddr*)&client, &c)) != INVALID_SOCKET) {
        printf("Connection accepted.\n");
        handle_client(client_socket);
    }

    if (client_socket == INVALID_SOCKET) {
        printf("Accept failed.\n");
        return;
    }

    closesocket(server_socket);
    WSACleanup();
}

// Клиентская часть
void connect_to_server(const char* server_ip, const char* password) {
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;
    char buffer[1024];

    printf("Connecting to server...\n");

    // Инициализация Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize Winsock.\n");
        return;
    }

    // Создание сокета
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Failed to create socket.\n");
        return;
    }

    // Настройка сервера
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_port = htons(PORT);

    // Подключение к серверу
    if (connect(client_socket, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Connection failed.\n");
        return;
    }

    // Отправка пароля
    send(client_socket, password, strlen(password), 0);

    // Получение ответа от сервера
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Server response: %s\n", buffer);

    closesocket(client_socket);
    WSACleanup();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage:\n");
        printf("  Server mode: %s -s\n", argv[0]);
        printf("  Client mode: %s -c <server_ip> <password>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-s") == 0) {
        // Запуск в режиме сервера
        start_server();
    } else if (strcmp(argv[1], "-c") == 0) {
        // Запуск в режиме клиента
        if (argc < 4) {
            printf("Usage: %s -c <server_ip> <password>\n", argv[0]);
            return 1;
        }
        connect_to_server(argv[2], argv[3]);
    } else {
        printf("Invalid mode. Use -s for server or -c for client.\n");
        return 1;
    }

    return 0;
}