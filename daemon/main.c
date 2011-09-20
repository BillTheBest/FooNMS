#include <stdio.h>
#include <stdlib.h>
//#include <mysql.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUF 1024

int main(int argc, char* argv[])
{
	//MySQL.
	//MYSQL *conn;
	//MYSQL_RES *res;
	//MYSQL_ROW row;

	//Scoket.
int sockd, sockd2;
  int addrlen;
  struct sockaddr_in my_name, peer_name;
  int status;
	int count;
	char buf[MAX_BUF];

	int portnumber = 37373;

	char *server = "localhost";
	char *user = "jscott";
	char *password = "mWrxp6zG4ezqjDST"; /* set me first */
	char *database = "jscott_newzen";

//	conn = mysql_init(NULL);

	/* Connect to database */
//	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
//	{
///		fprintf(stderr, "%s\n", mysql_error(conn));
//		exit(1);
//	}
	
	/* create a socket */
  sockd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockd == -1)
  {
    perror("Socket creation error");
    exit(1);
  }
/* server address  */
  my_name.sin_family = AF_INET;
  my_name.sin_addr.s_addr = INADDR_ANY;
  my_name.sin_port = htons(portnumber);

  status = bind(sockd, (struct sockaddr*)&my_name, sizeof(my_name));
  if (status == -1)
  {
    perror("Binding error");
    exit(1);
  }

  status = listen(sockd, 5);
  if (status == -1)
  {
    perror("Listening error");
    exit(1);
  }

  for(;;)
  {
    /* wait for a connection */
    addrlen = sizeof(peer_name);
    sockd2 = accept(sockd, (struct sockaddr*)&peer_name, &addrlen);
    if (sockd2 == -1)
    {
      perror("Wrong connection");
      exit(1);
    }
    //write(sockd2, "Hello!\n", 7);
	count = read(sockd, buf, MAX_BUF);
	close(sockd2);
	printf("1: %s",buf);
  }
  return 0;
}

