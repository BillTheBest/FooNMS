/*
	daemon.c - Main file for the Yinoss daemon.
	Copyright (c) 2010 The Foo Project.
*/

/* Includes. */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> /* for close() for socket */ 

#include <mysql.h>
 
int main(void)
{
	//MySQL stuff.
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "localhost";
	char *user = "jscott";
	char *password = "no password here"; /* set me first */
	char *database = "jscott_newzen";
	
	//Socket stuff.
	int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	struct sockaddr_in sa; 
	char buffer[1024];
	ssize_t recsize;
	socklen_t fromlen;
 
	memset(&sa, 0, sizeof sa);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_port = htons(37373);
 
	//Bind the port to the socket.
	if(bind(sock,(struct sockaddr *)&sa, sizeof(sa)))
	{
		perror("error bind failed");
		close(sock);
		exit(EXIT_FAILURE);
	}
	
	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
 
	//Loop forever, so we get lots of packets.
	for(;;) 
	{
		memset(&buffer,0,sizeof(char)*1024);
		printf("Empty buffer? %d\n",strlen(buffer));
		
		//Receive the data. This should block if there is no data.
		printf ("recv test....\n");
		recsize = recv(sock, (void *)&buffer, 1024, 0);
		
		if(recsize < 0)
		{
			fprintf(stderr, "%s\n", strerror(errno));
		//      exit(EXIT_FAILURE);
		} else {
			printf("recsize: %d\n ",recsize);
			printf("datagram: %.*s\n", (int)recsize, buffer);
			//sleep(1);
		}
	}
}
