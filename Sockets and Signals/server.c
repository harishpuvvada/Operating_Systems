#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

	int linecount;
	int countfinal; 

	void sigintHandler(int sig_num) //called when ctrl+c is pressed
	{       
	    
	    signal(SIGINT, sigintHandler);// Reset handler to catch SIGINT next time
	    printf("Soo far %d lines with total no. of %d digits has been written in to secrets.out",linecount,countfinal);
	    fflush(stdout);
	    exit(0);
	}

         int main(int argc, char *argv[]) {
                    

		 int listenfd = 0, connfd = 0;
		 struct sockaddr_in serv_addr,cliaddr; 
		 char buf[100],sendBuff[1024];
	         char *s;
	         int ret,retbind;
                 socklen_t len;
		 FILE *fptr;

		 signal(SIGINT, sigintHandler);    //calling signal handler when control + c is pressed 
		
		listenfd = socket(AF_INET, SOCK_STREAM, 0);  // Create socket
		if (listenfd < 0)
		{
			perror("socket");
			exit(1);
		}

    		//intializing the serv_addr variables
	       memset(&serv_addr, '0', sizeof(serv_addr));
	       serv_addr.sin_family = AF_INET;
	       serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//Address through which server listens
	       serv_addr.sin_port = htons(5000); //Port Number through which server listens
    		
		//binding socket to the address and checking for the error
                retbind=bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
		if(retbind==-1)
		{
			perror("Binding Failed\n");
			exit(1);
		}
                    
		    listen(listenfd, 10); 
		    fptr=fopen("secrets.out","w"); //open new file initially
		    fclose(fptr);
	
		    printf("Waiting for client to connect\n");
		    
	            len=sizeof(cliaddr);
		    connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&len); //accept connection and get connection descriptor


		 printf("Connection from %s\n", inet_ntop(AF_INET,&cliaddr.sin_addr,buf,sizeof(buf)));




    while(1){

		int count=0;
		memset(sendBuff, 0, sizeof(sendBuff));
		fptr=fopen("secrets.out","a"); //open file in append mode for each line
		//Reading data
		ret=read(connfd, sendBuff, 100); // read upto 100 bytes from socket and save to sendBuff variable
		//sendBuff[ret]='\0';  //add escape sequence at end of read string

		
		for(s=sendBuff; *s !='\0'; s++) //checking each character
		{
		    if (*s=='\n'||'\0') //check for end of sentecnce 
		    {
		        fprintf(fptr,"  ");
		    }
		    else
		    {
		        putc(*s,fptr); //write character in file pointer
		    }
		    if (*s=='1'||*s=='2'||*s=='3'||*s=='4'||*s=='5'||*s=='6'||*s=='7'||*s=='8'||*s=='9'||*s=='0') 
			//check if current character is digit
		    {
		        count++;  //digits counter
			countfinal++; //counting number of digits for summary
		    }  
		}
		
		fprintf(fptr,"%d\n",count); //print count value in file
		fclose(fptr);
		linecount++; //couting number of lines for summary 
		
		}

	          close(listenfd);

			
		}
