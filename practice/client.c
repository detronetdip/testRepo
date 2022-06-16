#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int serverSocket, clientSocket, size, readSize;
    struct sockaddr_in serverAddress, clientAddress;
    char serverMessage[1000], message[1000];
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket< 0)
    {
        perror("Socket creation failed");
    }
    else
    {
        puts("socket created");
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(8080);
        if (connect(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        {
            perror("bind failed");
        }
        else
        {
            puts("connected");

            while (1)
            {
                printf("Enter Message : ");
                scanf("%s", message);
                if (send(serverSocket, message, strlen(message), 0) < 0)
                {
                    puts("send failed");
                    return 1;
                }
                if (recv(serverSocket, serverMessage, 1000, 0) < 0)
                {
                    puts("recv failed");
                    break;
                }
                puts("Server Reply: ");
                puts(serverMessage);
                memset(serverMessage, '\0', 1000);
            }
        }
    }
}