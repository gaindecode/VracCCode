#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include  <stdio.h>
#include  <stdlib.h>

void fin (int i);
void appli(int no_client_socket);
char buffer[512];
int ma_socket;
void  INThandler(int sig);

void main ( void )
{
	int client_socket;
	struct sockaddr_in mon_address, client_address;
	int mon_address_longueur, lg;

	bzero(&mon_address,sizeof(mon_address));
	mon_address.sin_port = htons(30000);
	mon_address.sin_family = AF_INET;
	mon_address.sin_addr.s_addr = htonl(INADDR_ANY);

	/* creation de socket */
	if ((ma_socket = socket(AF_INET,SOCK_STREAM,0))== -1)
	{
	  printf("ca chie avec la creation\n");
	  exit(0);
	}
	signal(SIGINT,fin);
	/* bind serveur - socket */
	bind(ma_socket,(struct sockaddr *)&mon_address,sizeof(mon_address));

	/* ecoute sur la socket */
	listen(ma_socket,5);

	/* accept la connexion */
	mon_address_longueur = sizeof(client_address);
	while(1)
	{
	signal(SIGINT, INThandler);
	  client_socket = accept(ma_socket,
		                 (struct sockaddr *)&client_address,
		                 &mon_address_longueur);

	  if (fork() == 0)
	  {
	    close(ma_socket);

	    lg = read(client_socket,buffer, 512);
	    printf("le serveur a recu: %s\n",buffer);
	    sprintf(buffer,"%s du serveur\n\n",buffer);
	    write(client_socket,buffer, 512);
	    shutdown(client_socket,2);
	    close(client_socket);
	    exit(0);
	  }
	}
	shutdown(ma_socket,2);
	close(ma_socket);
	}


	void appli(int no_client_socket)
	{
	  printf("ici le serveur\n");
	}

	void fin(int i)
	{
	shutdown(ma_socket,2);
	close(ma_socket);
}

void  INThandler(int sig)
{
     char  c;

     signal(sig, SIG_IGN);
     printf("OUCH, did you hit Ctrl-C?\n"
            "Do you really want to quit? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y')
          exit(0);
     else
          signal(SIGINT, INThandler);
     getchar(); // Get new line character
}
