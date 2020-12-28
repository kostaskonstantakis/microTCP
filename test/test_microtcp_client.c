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
 * You can use this file to write a test microTCP client.
 * This file is already inserted at the build system.
 */


#include <unistd.h>

#include <sys/socket.h>
#include "../lib/microtcp.h"
#include "../utils/crc32.h"
#include <arpa/inet.h>
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

char buff[MAX];

void func(int sockfd) 
{ 
	int n; 
	for (;;) { 
		bzero(buff, sizeof(buff)); 
		printf("To server: "); 
		n = 0; 
		while ((buff[n++] = getchar()) != '\n') 
			; 
		write(sockfd, buff, sizeof(buff)); 
		bzero(buff, sizeof(buff)); 
		read(sockfd, buff, sizeof(buff)); 
		printf("\tFrom Server : %s", buff); 
		if ((strncmp(buff, "exit", 4)) == 0) { 
			printf("Client Exit...\n"); 
			break; 
		} 
	} 
} 

int main() 
{ 
	microtcp_header_t *header=(microtcp_header_t *)malloc(sizeof(microtcp_header_t));
	microtcp_sock_t sockfd;
	int  connfd; 
	struct sockaddr_in servaddr, cli; 
	int r=0; //random number used for SEQ, etc.

	// socket create and verification 
	sockfd =  microtcp_socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd.sd ==-1) { 
		printf("Socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 
	if (microtcp_connect(&sockfd, (SA*)&servaddr, sizeof(servaddr)) < 0) { 
<<<<<<< HEAD
		printf("Connection to the server failed...\n"); 
=======
		printf("Connection with the server failed...\n"); 
>>>>>>> 2ea6947de1d840ba4907bdf8deea56d6017afe2e
		exit(0); 
	} 
	else
	{ //starting handshake here 
		header->control = (header->control | (1 << 14)); //set SYN bit=1.
		r=rand();//choose random SEQ number.
<<<<<<< HEAD
		sockfd.seq_number=(uint32_t)r;
		//connfd=send(sockfd.sd, buff, sizeof(buff), 0);//send();
		//connfd=recv(sockfd.sd, buff, sizeof(buff), 0); //recv()
		r=rand();
		sockfd.ack_number=(uint32_t)r; //random ACK
		header->control = (header->control | (1 << 12)); //set ACK bit=1
		sockfd.seq_number++; //seq=N+1
                //connfd=recv(sockfd.sd, buff, sizeof(buff), 0); //recv()
		//connfd=send(sockfd.sd, buff, sizeof(buff), 0);//send();
=======
		header->seq_number=(uint32_t)r;
		//printf("SEQ=%d\n",header->seq_number);
		//after sending the first packet, and receiving from the server
		r=rand();
		header->ack_number=(uint32_t)r; //random ACK
		header->control = (header->control | (1 << 12)); //set ACK bit=1
		header->seq_number++; //seq=N+1
		//header->ack_number=M+1; //ack=SEQ+1, from server
>>>>>>> 2ea6947de1d840ba4907bdf8deea56d6017afe2e
		printf("Connected to the server..\n");
 
	}
	// function for chat 
	func(sockfd.sd); 

	//shutdown happens here
<<<<<<< HEAD
	 header->control = (header->control | (1 << 12)); //set ACK bit=1
	 header->control = (header->control | (1 << 15)); //set FIN bit=1
	 r=rand();//choose random SEQ number.
         sockfd.seq_number=(uint32_t)r;
	 //connfd=send(sockfd.sd, buff, sizeof(buff), 0);//send();
	 //connfd=recv(sockfd.sd, buff, sizeof(buff), 0); //recv()
	 //set state after receiving ACK from server
	 sockfd.state=CLOSING_BY_HOST;	
	 //connfd=recv(sockfd.sd, buff, sizeof(buff), 0); //recv()
	 header->control = (header->control | (1 << 12)); //set ACK bit=1
	 //connfd=send(sockfd.sd, buff, sizeof(buff), 0);//send();
	 sockfd.state=CLOSED;
	 microtcp_shutdown(&sockfd, SHUT_RDWR);
=======

>>>>>>> 2ea6947de1d840ba4907bdf8deea56d6017afe2e
	// close the socket 
	close(sockfd.sd); 
} 























//int
//main(int argc, char **argv)
//{

//	int socket_desc;
//	socket_desc = microtcp_socket(AF_INET , SOCK_STREAM , 0).sd; //SOCK_DGRAM
//	
//	if (socket_desc == -1)
//	{
//		return 0;
		//printf("Could not create socket");
//	}
	
///	return 1;

//}



