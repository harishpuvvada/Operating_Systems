#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHMSZ 1024

void main(){

int shmid;
key_t key;
char *shm;
char *input= malloc(sizeof(char)*BUFSIZ);


key=getuid();                     //The key of the shared memory will be the user id 

 if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {   //create the shared memory segment
        perror("shmget");
        exit(1);
    }

if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {     // attaching segment to our data space
        perror("shmat");
        exit(1);
    }

while(1){

           printf("Please type your alpha numeric input with secret code \n");
	
	   fgets(input, BUFSIZ, stdin);
		
	   if(strstr(input,"COOL")!=NULL){
				
	       strcpy(shm,input);
	       
                             		 }

			while(*shm!='\0'){ //till processor reads the entire string and inserts a '\0' receiver sleeps
				
				sleep(1);

				         }
             }

   }
