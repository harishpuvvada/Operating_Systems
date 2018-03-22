#include <stdlib.h>	
#include <unistd.h>	
#include <stdio.h>
#include <string.h>

int runit(char*);
void main() {

	int pid=0;                                     //process ID
	char command[50];
	int d=0;
	while(1)

	{
		printf("Please enter your command!\n");
		scanf("%s", &command);
		switch (pid = fork()) 
		{
			case 0:		               // a fork returns 0 to the child 
				printf("Child process \n");
				d=runit(command);
				if(d==-1){
				printf("command not found \n");}
				break;

			default:
				wait(5);               // a fork returns a pid to the parent 
				printf("Parent process \n"); 
				break;

			case -1:	               //something went wrong 
				perror("fork");
				exit(1);

		}
	}                
}

int runit(char* command) {		               //executing the command

	char path[50]="/bin/";

	int d = execl(strcat(path,command),command,NULL,NULL);     

	return(d);

}

