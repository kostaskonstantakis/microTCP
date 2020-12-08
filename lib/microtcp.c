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
B * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "microtcp.h"
#include "../utils/crc32.h"
#include <stdio.h>
#include <errno.h>
//#include <unistd.h>
microtcp_sock_t

microtcp_socket (int domain, int type, int protocol)
{
    //socket creation and verification
    microtcp_sock_t sockfd;/* newsockfd is microtcp_sock_t variable */
    sockfd.state = 0;//"UNKNOWN";
    /*First we must call the socket function specyfying the communication protocol (TCP based on UDP)*/
    sockfd.sd = socket(domain, type, protocol); /*domain,type,and protocol are given but it will be UDP*/;
    if (sockfd.sd < 0) {
        //perror("failed to create socket");//printf("failed to create socket"); //or error
        //return 0;//exit(0);
	sockfd.state=6;
    }
    return sockfd; 
    
}

int
microtcp_bind (microtcp_sock_t *socket, const struct sockaddr *address,
               socklen_t address_len)
{
    //Must we assign IP,PORT?
    /*The bind() assigns a local protocol address to a socket. With the Internet protocols, the address is the combination of an IPv4 or IPv6 address (32-bit or 128-bit) address along with a 16 bit TCP port number.*/
    //if ((bind(socket->sd, address, address_len)) != 0) {
        //printf("socket bind failed...\n");
      //  return 1;//exit(0);
   /// }
    //else
        //printf("Socket successfully binded..\n");
//	return 0;
	return bind(socket->sd, address, address_len);

}

int
microtcp_connect (microtcp_sock_t *socket, const struct sockaddr *address,
                  socklen_t address_len)
{
    
    return connect(socket->sd, address, address_len);
            //return 0;//perror("ERROR connecting");

    //return 1;
}

int
microtcp_accept (microtcp_sock_t *socket, struct sockaddr *address,
                 socklen_t address_len)
{
    //microtcp_sock_t connfd;                 /* newsockfd is microtcp_sock_t variable */
    //connfd.state = 2;
    /*must create the newsockfd*/
    return accept(socket->sd,address,&address_len);
    //if (connfd < 0)
        //perror("ERROR on accept");
//	return 0;

  //  else
    //    return 1;//printf("server accept the client..\n");
}

int
microtcp_shutdown (microtcp_sock_t *socket, int how)
{
  /* Your code here */
        if(shutdown(socket->sd,how)==0) return 0; //success
        else if(shutdown(socket->sd,how)==-1) return -1; //failure
        else if(socket==NULL) return EBADF;  //invalid socket or null
        else if(how!=SHUT_RD||how!=SHUT_WR||how!=SHUT_RDWR) return EINVAL; //invalid value for how argument
        //else if(!microtcp_connect(socket, socket->address, socket->address_len)) return ENOTCONN;
        else return ENOTSOCK; //socket doesn't refer to a socket

}

ssize_t
microtcp_send (microtcp_sock_t *socket, const void *buffer, size_t length,
               int flags)
{

//    int n = 0;
    // copy server message in the buffer
//    while ((buffer[n++] = getchar()) != '\n');

    // and send the buffer to client
//    write(*socket->sd, buffer, sizeof(buffer));
}

ssize_t
microtcp_recv (microtcp_sock_t *socket, void *buffer, size_t length, int flags)
{
  /* Your code here */
}

