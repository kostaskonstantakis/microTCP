/*
 * microtcp, a lightweight implementation of TCP for teaching,
 * and academic purposes.
 *
 * Copyright (C) 2015-2017  Manolis Surligas <surligas@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * You can use this file to write a test microTCP server.
 * This file is already inserted at the build system.
 */
//#include<stdio.h>
//#include<sys/socket.h> 
//#include "../lib/microtcp.h"
//#include "../utils/crc32.h"


//int main(int argc , char **argv)
//{
//	int socket_desc;
//	socket_desc = microtcp_socket(AF_INET , SOCK_STREAM , 0).sd;
//	
//	if (socket_desc == -1)
//	{
//		return 0;//printf("Could not create socket");
//	}
//	
//	return 1;
//
//
//}


#include <unistd.h>
#include <arpa/inet.h>


#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include "../lib/microtcp.h"
#include "../utils/crc32.h"

#include <sys/types.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	// infinite loop for chat 
	for (;;) { 
		bzero(buff, MAX); 

		// read the message from client and copy it in buffer 
		read(sockfd, buff, sizeof(buff)); 
		// print buffer which contains the client contents 
		printf("From client: %s\t To client : ", buff); 
		bzero(buff, MAX); 
		n = 0; 
		// copy server message in the buffer 
		while ((buff[n++] = getchar()) != '\n') 
			; 

		// and send that buffer to client 
		write(sockfd, buff, sizeof(buff)); 

		// if msg contains "Exit" then server exit and chat ended. 
		if (strncmp("exit", buff, 4) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		} 
	} 
} 

// Driver function 
int main() 
{ 
	microtcp_sock_t sockfd;
	microtcp_header_t *header=(microtcp_header_t *)malloc(sizeof(microtcp_header_t));
	//int sockfd, 
	int connfd, len; 
	struct sockaddr_in servaddr, cli; 
	int r=0; //random number

	// socket create and verification 

	sockfd = microtcp_socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd.sd < 0) { 
		printf("Socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Binding newly created socket to given IP and verification 
	if ((microtcp_bind(&sockfd, (SA*)&servaddr, sizeof(servaddr))) == -1) { 
		printf("Socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd.sd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = microtcp_accept(&sockfd, (SA*)&cli, len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else //handshake happens here probably
	{
		header->control = (header->control | (1 << 14)); //set SYN bit=1
		header->control = (header->control | (1 << 12)); //set ACK bit=1
                r=rand();//choose random SEQ number.
                header->seq_number=(uint32_t)r;
		//header->ack_number=M+1; //ack=ACK+1, from server

                //printf("SEQ=%d\n",header->seq_number);
		printf("Server acccept the client...\n"); 
	}
	// Function for chatting between client and server 
	func(connfd); 

	// After chatting close the socket 
	close(sockfd.sd); 
} 

