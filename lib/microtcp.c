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

#include "microtcp.h"
#include "../utils/crc32.h"

microtcp_sock_t
microtcp_socket (int domain, int type, int protocol)
{
    //socket creation and verification
    microtcp_sock_t sockfd;/* newsockfd is microtcp_sock_t variable */
    sockfd.state = "UNKNOWN";
    /*First we must call the socket function specyfying the communication protocol (TCP based on UDP)*/
    sockfd = socket(domain, type, protocol); /*domain,type,and protocol are given but it will be UDP*/;
    if (sockfd < 0) {
        printf("failed to create socket"); //or error
        exit(0);
    }
    return sockfd; 
    
}

int
microtcp_bind (microtcp_sock_t *socket, const struct sockaddr *address,
               socklen_t address_len)
{
    //Must we assign IP,PORT?
    /*The bind() assigns a local protocol address to a socket. With the Internet protocols, the address is the combination of an IPv4 or IPv6 address (32-bit or 128-bit) address along with a 16 bit TCP port number.*/
    if ((bind(socket, address, sizeof(address))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");


}

int
microtcp_connect (microtcp_sock_t *socket, const struct sockaddr *address,
                  socklen_t address_len)
{
    
    if (connect(socket, address, sizeof(address_len)) < 0)
            error("ERROR connecting");

}

int
microtcp_accept (microtcp_sock_t *socket, struct sockaddr *address,
                 socklen_t address_len)
{
    microtcp_sock_t connfd;                 /* newsockfd is microtcp_sock_t variable */
    connfd.state = "ESTABLISHED";
    /*must create the newsockfd*/
    connfd = accept(socket,address,sizeof(address_len));
    if (connfd < 0)
        error("ERROR on accept");

    else
        printf("server accept the client..\n");
}

int
microtcp_shutdown (microtcp_sock_t *socket, int how)
{
  /* Your code here */
}

ssize_t
microtcp_send (microtcp_sock_t *socket, const void *buffer, size_t length,
               int flags)
{
    n = 0;
    // copy server message in the buffer
    while ((buff[n++] = getchar()) != '\n');

    // and send the buffer to client
    write(socket, buff, sizeof(buff));
}

ssize_t
microtcp_recv (microtcp_sock_t *socket, void *buffer, size_t length, int flags)
{
  /* Your code here */
}

