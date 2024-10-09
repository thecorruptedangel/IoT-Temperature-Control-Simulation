#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <process.h>

int temperature = 25;
char degree_char = 248;
CRITICAL_SECTION tempLock;

unsigned __stdcall update_temperature(void* arg) {
    srand((unsigned int)time(NULL));
    while (1) {
        EnterCriticalSection(&tempLock);
        temperature = rand() % 21 + 15; 
        printf("Current temperature: %d %cC\n", temperature, degree_char);

        LeaveCriticalSection(&tempLock);
        Sleep(1000);
    }
    return 0;
}

unsigned __stdcall handle_requests(void* arg) {
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int c;
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(12345);

    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    listen(server_socket, 3);

    c = sizeof(struct sockaddr_in);
    while ((client_socket = accept(server_socket, (struct sockaddr*)&client, &c)) != INVALID_SOCKET) {
        char buffer[1024] = { 0 };
        recv(client_socket, buffer, 1024, 0);
        if (strcmp(buffer, "GET_TEMP") == 0) {
            EnterCriticalSection(&tempLock);
            char temp_str[4];
            sprintf(temp_str, "%d", temperature);
            send(client_socket, temp_str, (int)strlen(temp_str), 0);
            LeaveCriticalSection(&tempLock);
        }
        closesocket(client_socket);
    }

    if (client_socket == INVALID_SOCKET) {
        printf("accept failed with error code : %d", WSAGetLastError());
        return 1;
    }

    closesocket(server_socket);
    WSACleanup();

    return 0;
}

int main() {
    printf("-----  IoT Sensor & Control simulator  ----- \n");
    printf("-----        temp sensor module        ----- \n\n");
    printf("\n\n Initializing...\n\n");
    InitializeCriticalSection(&tempLock);
    HANDLE hThreads[2];

    hThreads[1] = (HANDLE)_beginthreadex(NULL, 0, &handle_requests, NULL, 0, NULL);
    hThreads[0] = (HANDLE)_beginthreadex(NULL, 0, &update_temperature, NULL, 0, NULL);


    if (hThreads[0] == NULL || hThreads[1] == NULL) {
        fprintf(stderr, "Error creating threads\n");
        if (hThreads[0]) CloseHandle(hThreads[0]);
        if (hThreads[1]) CloseHandle(hThreads[1]);
        DeleteCriticalSection(&tempLock);
        return 1;
    }

    WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

    if (hThreads[0]) CloseHandle(hThreads[0]);
    if (hThreads[1]) CloseHandle(hThreads[1]);

    DeleteCriticalSection(&tempLock);
    return 0;
}