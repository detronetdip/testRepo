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
    char clientMessage[1000];
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        perror("Socket creation failed");
    }
    else
    {
        puts("socket created");
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(8080);
        if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        {
            perror("bind failed");
        }
        else
        {
            puts("Bind successfull");
            listen(serverSocket, 2);
            puts("listning...");
            size=sizeof(struct sockaddr_in);
            clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, (socklen_t *)&size);
            while(readSize=recv(clientSocket,clientMessage,1000,0)>0){
                write(clientSocket,clientMessage,strlen(clientMessage));
                memset(clientMessage,'\0',1000);
            }
        }
    }
}