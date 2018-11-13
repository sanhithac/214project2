#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "multiThreadSorter_thread.h"

int sorter(FILE *fp, char *colName, DIR *dir){	
  char firstrow[1000];
   if(fp==NULL){
     printf("Invalid Input");
     return -1;
  }
  fscanf(fp, "%[^\n]", firstrow);
  printf("%s\n", firstrow);
  int colInd=columnNum(firstrow, colName);
  if(colInd==-1){
    printf("Invalid Input: Column does not exist");
    return -1;
  }
	
  Node *head=readfile(colInd, fp);//read file and organize rows into nodes
	
  //error checking
  if(head==NULL)
     return 0;
	
  //sorts the nodes/rows
  Node **new=&head;	
  MergeSort(new);
	
  //prints the first row and sorted nodes to stdout
  print(head);
	
  //free data
  Finish(head);
	
   return 0;
}


Node* readfile(int colInd, FILE *fp){
  char line[1000];
	
  //organizing the rows into nodes
  Node *temp =NULL;
  Node *head=NULL;
  Node *p=NULL;
  int size=0;
  char *str;
	
  while(fgets(line, 1000, fp)!=NULL){
    if(size!=0){
      temp=(Node *)malloc(sizeof(Node));
      temp->row=(char*)malloc(sizeof(char)*1000);
      temp->data=(char*)malloc(sizeof(char)*100);
      strcpy((temp)->row, line);
      str=tokenizer(colInd, line);
      strcpy((temp)->data,str);
      if(head==NULL){
	head=temp;
      }
      else{
	p=head;
	while(p->next!=NULL){
	  p=p->next;
	}
	p->next=temp;
      }
    }
    size++;
  }
  return head;
}
 

//finds the index of column
int columnNum(char *row, char *col){
   char *word;
  const char s[2]=",";
  char *token;
  int count=-1;
  token=strtok(row, s);
  while(token!=NULL){
  token=remove_leading_spaces(token);
   if(strcmp(token, col)==0){
      count++;
      return count;
      }
    count++;
    token=strtok(NULL, s);
  }
  return -1;
}
  

//removes the leading and trailing whitespaces of a token
char *remove_leading_spaces(char* str) 
{   
  char *end;
  while(isspace((unsigned char)*str)){
	 str++;
  }
  end=str+strlen(str)-1;
  while(end>str && isspace((unsigned char)*end)){
	  end--;
  }
  return str;

} 
	
	
//splits row into col values
char *tokenizer(int col, char *line){
  const char s[2]=",";
  char *token;
  int count=0;
  token=strtok(line, s);
  while(token!=NULL){
  token=remove_leading_spaces(token);
    if(col==count){
      return token;
    }
    count++;
    token=strtok(NULL,s);
  }
  return token;
}

	
//traverses through ll and prints nodes
void print(Node *head){
  Node *p=NULL;
  p=head;
  while (p!= NULL){
    printf("%s\n",p->row);
    p = p->next;
  }
  return;
}

void Finish(Node* head){ //frees everything
	Node* temp = head;
	Node*p=NULL;
	int n = 0;
	while(temp!= NULL){
		free(temp->row);
		free(temp->data);
		p=temp->next;
		free(temp);
		temp=p;
    }
}
  
  // sorts LL 
  
void MergeSort (Node** headRef){
    Node* head = *headRef;
    Node* a;
    Node* b;

    if((head == NULL) || (head->next == NULL)){
      return;
    }
  // split head into 'a' 'b'
    FrontBackSplit(head, &a, &b);
    
    MergeSort(&a);
    MergeSort(&b);
    
    *headRef = SortedMerge(a, b);
}
    
Node* SortedMerge(Node* a, Node* b){ 
  Node* result = NULL; 
  int cmp=0;
  
  if (a == NULL) 
    return(b); 
  else if (b == NULL) 
    return(a);
      
  cmp = strcmp(a->data, b->data);
 
  if(cmp <= 0){
    result=a;
    result->next=SortedMerge(a->next, b);
  }else{
    result=b;
    result->next=SortedMerge(a, b->next);
  }
  return(result);
}
      
void FrontBackSplit(Node* source, Node** frontRef, Node** backRef){
      Node* fast;
      Node* slow;
      slow = source;
      fast = source->next;
      
      while(fast != NULL){
        fast = fast->next;
        if(fast != NULL)
        {
          slow = slow->next;
          fast = fast->next;
        }
      
      //assign the front and back to a and b
      *frontRef = source;
      *backRef = slow->next;
      slow->next = NULL;
    }

  }
