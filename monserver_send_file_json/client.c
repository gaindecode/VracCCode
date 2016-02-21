#include <stdio.h>
#include <errno.h>
#include <signal.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <time.h>
#include <stdlib.h>
#include <limits.h>


#define SERVEURNAME "127.0.0.1"

int to_server_socket = -1;

void main ( void )
{
srand(time(NULL));
	int r;
	char cated_string[512];
	char *server_name = SERVEURNAME;
	struct sockaddr_in serverSockAddr;
	struct hostent *serverHostEnt;
	long hostAddr;
	long status;
	char buffer[512];
	char message[512];
	char message_json[512]="{\"type\": \"home\",\"number\": \"212 555-1234\"}\0";
	
	char ch,file_name[25]="test.json";
	char content_of_file[512*4];
   FILE *fp;
   fp = fopen(file_name,"r"); // read mode
 
   if( fp == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
 ///Print the content of the file
   printf("The contents of %s file are :\n", file_name);
   int arrayId=0;
    while( ( ch = fgetc(fp) ) != EOF ){
      printf("%c",ch);
	content_of_file[arrayId]=ch;
	arrayId++;
	  //strncpy(content_of_file, ch, strlen(ch));//put caracter in ch into content_of_file
	  }
	  arrayId=0;
	  printf("\n\n");
	  printf("Text from content_of_file \n");
	  printf(content_of_file);
	  printf("\n\n");
   
   

	bzero(&serverSockAddr,sizeof(serverSockAddr));
	hostAddr = inet_addr(SERVEURNAME);
	if ( (long)hostAddr != (long)-1)
	  bcopy(&hostAddr,&serverSockAddr.sin_addr,sizeof(hostAddr));
	else
	{
	  serverHostEnt = gethostbyname(SERVEURNAME);
	  if (serverHostEnt == NULL)
	  {
	    printf("ca chie gethost\n");
	    exit(0);
	  }
	  bcopy(serverHostEnt->h_addr,&serverSockAddr.sin_addr,serverHostEnt->h_length);
	}
	serverSockAddr.sin_port = htons(30000);
	serverSockAddr.sin_family = AF_INET;

	/* creation de la socket */
	if ( (to_server_socket = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
	  printf("ca chie creation socket client\n");
	  exit(0);
	}
	/* requete de connexion */
	if(connect( to_server_socket,
		    (struct sockaddr *)&serverSockAddr,
		    sizeof(serverSockAddr)) < 0 )
	{
	  printf("ca chie demande de connection\n");
	  exit(0);
	}
	/* envoie de donne et reception */
	r = rand()%200;
	printf("Longueur de message_json : %d\n",strlen(message_json));
	printf("Nombre Généré : %d\n",r);
	printf("Message_json\n");
	printf(message_json);
	strncpy(message, message_json, strlen(message_json));//put json array in message
	//strncpy(message, "Toto", 4);//message="Toto ";
	// printf("Le message a transmettre : %s%d\n\n",message,r);
	//sprintf(cated_string,"%s%d",message,r);
	printf("Le message a transmettre : %s\n\n",content_of_file);
	sprintf(cated_string,"%s%d",content_of_file,r);

	write(to_server_socket,cated_string,strlen(cated_string));
	read(to_server_socket,buffer,512);
	printf(buffer);
	printf("\n");
	/* fermeture de la connection */
	shutdown(to_server_socket,2);
	close(to_server_socket);
}
