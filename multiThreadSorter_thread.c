#include <dirent.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <sys/types.h> 
#include "simpleCSVsorter.c" 

 int main(int argc, char** argv){ 
   //input and output directories
   char *inDir=".";
   char *outDir=".";
   char *colName;
   
   pidNode * head=NULL;
	 
   if(argc%2 ==0){ //even
     printf("Incorrect Input\n");
     return -1; 
   } 
   if(argc >7){ //too long
     printf("Incorrect Input\n");
     return -1; 
   } 
   if(strcmp(argv[1],"-c")!=0){ //no -c
     printf("Incorrect Input: No column flag\n");
     return -1; 
   } 
   if(strcmp(argv[2],"-d")==0||strcmp(argv[2],"-o")==0){ //no category
     printf("Incorrect Input: No column name\n");
     return -1;  
   } 
   else{//record column Name
     colName=argv[2];
   }
   if(argc>3){
     if(strcmp(argv[3],"-d")==0){//input directory specified
       inDir=argv[4];
     }
     else if(strcmp(argv[3],"-o")==0){//output directory specified
       outDir=argv[4];
     }
     if(argc>5){
       if(strcmp(argv[5],"-o")==0){//output directory specified
             outDir=argv[6];
       }
     }
   }
       
   int processCounter=0;
   DIR* dir; 
   DIR* out;
   //struct dirent* ptr; 

   dir = opendir(inDir); //opens a directory
   out = opendir(outDir);	 
	 
   if(dir == NULL){ 
     printf("Incorrect Input: Input directory specified does not exist\n");
     return -1; 
   }
   if(outDir==NULL){
     printf("Incorrect Input: Output directory specified does not exist\n");
     return -1; 
   }
	 
   directChild(dir, head, processCounter);
   printVals(getpid(), head, processCounter);
   return 0; 
 } 

void directChild(DIR* dir, pidNode * head, int processCounter){
  int pid;

  struct dirent* ptr; //points to the directory that is read
  while((ptr = readdir(dir))!= NULL){
	DIR* temp;
	pid = fork();
	processCounter++;
	if(ptr->d_type == DT_DIR){//directory
		if (pid == 0){//child pid
			if(access(strcat("./", ptr->d_name), R_OK)==0{	
				temp=opendir(ptr->d_name);
				directChild(temp, head, processCounter); //recurse
				childpid(head, pid);
			}
        	}
		else if (pid ==1){//parent pid
			while(wait(0, NULL, 0)<=0){
			}
			continue;
        	}
	}
	else{
		if (pid == 0){
			if(access(strcat("./", ptr->d_name), R_OK)==0{	
				if(isCSV(ptr->d_name) == 1){
					mergesort();
					childpid(head, pid);
        			}
			}
		}
		if (pid == 1){
			while(wait(0, NULL, 0)<=0){
			}
			continue;
        	}
		  
      }
  }
}

/*
//checks if the input is a directory
int isDirectory(char d_name[]){
  for(int i =0; i< strlen(d_name);i++){
    if(strcmp(d_name[i],".") != 0){
      return 0;
    }
  }
  return 1;
}
*/

//checks if the input is a csv file
int isCSV(char* d_name){
  char[5] tempStr = "";
  if (strlen(d_name) < 5)
    return 0;
  for(int i = strlen(d_name)-4; i < strlen(d_name); i++){
    tempStr += d_name[i];
  }
  if(strcmp(tempStr, ".csv") == 0)
    return 1;
  return 0;
}

pidNode* childpid(pidNode * head, pid_t pid){
	pidNode *temp= (pidNode *)malloc(sizeof(pidNode));
	pidNode *p=NULL;
	
	if(head==NULL){
		head = (pidNode *)malloc(sizeof(pidNode));
		head->data=pid;
	}
	else{
		p=head;
		while(p->next !=NULL){
			p=p->next;
		}
		p->next =temp;
		temp->data=pid;
	}
	return head;
}

void printVals(pid_t pid, pidNode *head, int counter){
	printf("Initial PID: %d\n", pid);
	printf("PID of all child processes:");
	Node *p=NULL;
  	p=head;
  	while (p!= NULL){
    		printf("%d", p->data, ", ");
    		p = p->next;
 	 }
	printf("\n Total number of processes: %lf\n", pow(2, counter));
	return;
}
