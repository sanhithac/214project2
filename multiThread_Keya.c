#include <dirent.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <sys/types.h> 
#include "multiThreadSorter_thread.h" 

 int main(int argc, char** argv){ 
   //input and output directories
   char *inDir=".";
   char *outDir=".";
   char *colName;
   
   pidNode * head=NULL;
	 
   //flag check open
      if(argc%2 ==0){ //even
     printf("Incorrect Input\n");
     return -1; 
   } 
   if(argc >7){ //too long
     printf("Incorrect Input\n");
     return -1; 
   } 
   if(argc<3){
    printf("Incorrect Input: No column name\n");
     return -1; 
   }

   //if there is 1 input
   if(argc==3){ 
    if(strcmp(argv[1],"-c")!=0){
      printf("Incorrect Input: No column flag\n");
      return -1;
    }
    colName=argv[2];
   }

   //if there are 2 inputs
   if(argc==5){ 
    if(strcmp(argv[1],"-c")!=0 && strcmp(argv[3],"-c")!=0){
      printf("Incorrect Input: No column flag\n");
      return -1; 
    }
    if(strcmp(argv[1],"-d")!=0 && strcmp(argv[3],"-d")!=0 && strcmp(argv[1],"-o")!=0 && strcmp(argv[3],"-o")!=0){
      printf("Incorrect Input: No column flag\n");
      return -1;
    }
    if(strcmp(argv[1],"-c")==0){
      colName=argv[2];
      if(strcmp(argv[3],"-d")==0){ //directory specified
        inDir=argv[4];
      }
      else{ //output directory specified
        outDir=argv[4];
      }
    }
    else{
      colName=argv[4];
      if(strcmp(argv[1],"-d")==0){ //directory specified
        inDir=argv[2];
      }
      else{
        outDir=argv[2]; //output directory specified
      }
    }
   }

   //if there are 3 inputs
   if(argc==7){ 
    if(strcmp(argv[1],"-c")!=0 && strcmp(argv[3],"-c")!=0 && strcmp(argv[5],"-c")!=0){
      printf("Incorrect Input: No column flag\n");
      return -1; 
    }
    if(strcmp(argv[1],"-d")!=0 && strcmp(argv[3],"-d")!=0 && strcmp(argv[5],"-d")!=0){
      printf("Incorrect Input: No column flag\n");
      return -1;
    }
    if(strcmp(argv[1],"-o")!=0 && strcmp(argv[3],"-o")!=0 && strcmp(argv[5],"-o")!=0){
      printf("Incorrect Input: No column flag\n");
      return -1;
    }
    if(strcmp(argv[1],"-c")==0){ //c first
      colName=argv[2];
      if(strcmp(argv[3],"-d") ==0){//c-d-o
        inDir=argv[4];
        outDir=argv[6];
      }
      else{ //c-o-d
        inDir=argv[6];
        outDir=argv[4];
      }
    }
    else if(strcmp(argv[3],"-c")==0){ //c second
      colName=argv[4];
      if(strcmp(argv[1],"-d") ==0){//d-c-o
        inDir=argv[2];
        outDir=argv[6];
      }
      else{ //o-c-d
        inDir=argv[6];
        outDir=argv[2];
      }
    }
    else{ //c last
      colName=argv[6];
      if(strcmp(argv[1],"-d") ==0){//d-o-c
        inDir=argv[2];
        outDir=argv[4];
      }
      else{ //o-d-c
        inDir=argv[4];
        outDir=argv[2];
      }
    }
   }
//end of flag check 
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
   printVals(getpid(), head, processCounter); //print PIDs
   return 0; 
 } 

void directChild(DIR* dir){
  int isFile =0;
  struct dirent* ptr;
  while((ptr = readdir(dir))!= NULL){
    if(isCSV(ptr->d_name) == 1){ //if CSV
      isFile = fileChecker(ptr);
      if(isFile == 1){
        //thread(TID,...,moveToFinal,ptr);
      }//close inner if
    }//close outer if
    else if(ptr->d_type == DT_DIR){ //if directory
      //thread(TID,...,directChild, ptr);
    }//close else if directory
    else{ //if anything else
      continue;
    }//close else
  }//close while
}//close directChild

void moveToFinal(){
  
}//close moveToFinal

//check for a valid CSV file
int fileChecker(ptr){
  char* header = read(ptr); //read the header row

  int tokCounter =0;
  while(strtok(header, “,”) != NULL){
    tokCounter++;
  }//close while

  int checker =0;
  while((char* token = strtok(header,”,”)) != NULL){
    if(token == colName){
      checker = 1;
      break;
    }//close if
  }//close while
  if(checker == 0){//if input category is not in the list
    return 0;
  }//close if

  int rowTokCounter = 0;
  while((char* newLine = read(ptr)) != NULL){
    while(strtok(newLine, “,”) != NULL){
      rowTokCounter++;
    }//close inner while
    if(rowTokCounter != tokCounter){
      return 0;
    }//close if
  }//close while
  return 1; //is a good CSV
}//close fileChecker

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
*/
