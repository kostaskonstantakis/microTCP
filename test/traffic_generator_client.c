/*
 * microtcp, a lightweight implementation of TCP for teaching,
 * and academic purposes.
 *
 * Copyright (C) 2017  Manolis Surligas <surligas@gmail.com>
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

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include "../lib/microtcp.h"
#include "../utils/log.h"
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

static char running = 1;


        
static void
sig_handler(int signal)
{
  if(signal == SIGINT) {
    LOG_INFO("Stopping traffic generator client...");
    running = 0;
  }
}

int
main(int argc, char **argv) {
  uint16_t port;

 	microtcp_sock_t sockfd;
        microtcp_header_t *header=(microtcp_header_t *)malloc(sizeof(microtcp_header_t));
        //int sockfd,
        int connfd, len;
        struct sockaddr_in servaddr, cli;
        int r=0; //random number

        // socket create and verification

        sockfd = microtcp_socket(AF_INET, SOCK_STREAM, 0);

int i=0;
  /*
   * Register a signal handler so we can terminate the client with
   * Ctrl+C
   */
  signal(SIGINT, sig_handler);

  LOG_INFO("Start receiving traffic from port %u", port);
  i=microtcp_connect(&sockfd, (SA*)&servaddr, sizeof(servaddr));
  /*TODO: Connect using microtcp_connect() */
  while(running) {
	struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = MICROTCP_ACK_TIMEOUT_US;
        if (setsockopt(&sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval )) < 0)
                perror("setsockopt");
    /* TODO: Measure time */
    /* TODO: Receive using microtcp_recv()*/
    /* TODO: Measure time */
    /* TODO: Do other stuff... */
  }

  /* Ctrl+C pressed! Store properly time measurements for plotting */
}

