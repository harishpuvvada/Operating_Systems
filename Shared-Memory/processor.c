#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSZ 1024		//size of the shared memory segment

void main() {

	int shmid,dig_count;
	key_t key;
	char *shm,*s;
	FILE *fp;

	fp = fopen("secrets.out", "w+");

         key=getuid();                  //The key of the shared memory will be the user id 

	 if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {   //we don't have to create memory segment again
			
			perror("shmget");
			exit(1);
	                                          
				 }

         if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {     // attaching segment to our data space
               perror("shmat");
                  exit(1);
                                 }


while(1){


	if(*shm != '\0'){
		
			dig_count=0;		//to start couting the digits from 0 for everytime

			  for(s=shm;*s!='\0';s++)  // for finding number of digits in input string

				{				
				  if(*s=='1'||*s=='2'||*s=='3'||*s=='4'||*s=='5'||*s=='6'||*s=='7'||*s=='8'||*s=='9'||*s=='0')
				  {	
					dig_count++;
					
				  }
					
				}

			fp = fopen("secrets.out","a"); // for appending the data inside the file
			
			fprintf(fp,"%s:%d\n",shm,dig_count); //writing the original line and the digit count
			
			fclose(fp);

			*shm = '\0';  //program signalizes by inserting a '\0' in the memory address shm is pointing to

			}
	
	}


       if (shmdt(shm) == -1) {
		perror("Shared memory segment couldn't detach"); //detaching the memory space
		exit(1);
	                     }


}
