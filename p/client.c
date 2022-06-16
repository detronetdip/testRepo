#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int sock, i, len;
	char temp;
	struct sockaddr_in server;
	char message[2000], server_reply[2000];
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		printf("Could not creat socket");
	}
	puts("Socket created");
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("connect failed.Error");
		return 1;
	}
	puts("connected");
	while (1)
	{
		printf("Enter Message : ");
		scanf("%s", message);
		if (strcmp(message, "EXIT") == 0)
		{
			puts("Exited");
			close(sock);
			exit(1);
		}
		/*
		len=strlen(message);
		for(i=0;i<len/2;i++){
		temp=message[i]; //client reverse
		message[i]=message[len-i-1];
		message[len-i-1]=temp;
		}
		/*
		len=strlen(message);
		for(i=0;i<len;i++){
		if(message[i]>'a' && message[i]<'z')
			message[i]=message[i]-32;//client case change
		else if(message[i]>'A' && message[i]<'Z')
			message[i]=message[i]+32;
		}*/
		if (send(sock, message, strlen(message), 0) < 0)
		{
			puts("send failed");
			return 1;
		}
		if (recv(sock, server_reply, 2000, 0) < 0)
		{
			puts("recv failed");
			break;
		}
		puts("Server Reply: ");
		// for(int i=0;i<5;i++)
		puts(server_reply);
		memset(server_reply, '\0', 2000);
	}
	close(sock);
	return 0;
}
