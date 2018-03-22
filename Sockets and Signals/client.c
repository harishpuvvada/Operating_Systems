#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>



int main(int argc, char *argv[]){

        int sd; // socket descriptor
       struct sockaddr_in serv_addr; 
	char buffer[1024];
	int n;

	    if(argc != 2) //checking if ip address is given as a argument
	    {
		printf("\n Usage: %s <ip of server> \n",argv[0]);
		return 1;
	    } 

	    memset(buffer, '0',sizeof(buffer));   //setting the buffer memory to 0
	    if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	    {
		printf("\n Error : Could not create socket \n");
		return 1;
	    } 

	    memset(&serv_addr, '0', sizeof(serv_addr)); 

	    serv_addr.sin_family = AF_INET; //intializing the server address
	    serv_addr.sin_port = htons(5000);  
	   
	    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
	    {
		printf("\n inet_pton error occured\n");
		return 1;
	    } 

	    if( connect(sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	    {
	       printf("\n Error : Connect Failed \n");
	       return 1;
	    } 

            printf("Please type your alpha numeric input with secret code \n");


while(1){


	   memset(buffer, 0, sizeof(buffer));  //initialize the buffer to zeroes in client
	   fgets(buffer, 100, stdin);	      //get lines from user

      if(strstr(buffer,"COOL")!=NULL){ //checking if input has secret code "COOL"
	   n=write(sd,buffer,strlen(buffer)); //sending data to socket through write system call
	   
	       if(n<0)
		{
		    printf("Writing to socket failed\n");
		    return(0);
		}	
                                      }	
         }

        close(sd);
	return 0;
      }

