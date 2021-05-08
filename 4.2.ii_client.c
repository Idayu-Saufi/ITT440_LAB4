#include<string.h>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h> //inet_addr

int main(int argc,char*argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	char *message;
	char server_reply[2000];

	//CREATE SOCKET
	socket_desc = socket(AF_INET,SOCK_STREAM,0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	server.sin_addr.s_addr=inet_addr("192.168.56.103"); //ip_address_server
	server.sin_family=AF_INET;
	server.sin_port=htons(8888); //port

	//CONNECT TO REMOTE SERVER
	if(connect(socket_desc,(struct sockaddr*)&server,sizeof(server))<0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected\n");

	//Send some data
	message= "connect";
	if(send(socket_desc, message, strlen(message), 0)<0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");
	//Receive a reply from server
	if( recv(socket_desc,server_reply,2000,0)< 0)

	{
		puts("recv failed");
	}
	puts("Reply Received\n");
	puts(server_reply);

	close(socket_desc);
	return 0;
}
