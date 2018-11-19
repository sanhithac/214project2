#include <stdlib.h>

typedef struct Node{
  char *data;
  char *row;
  struct Node *next;
}Node;

typedef struct pidNode{
  pid_t *pid;
  struct pidNode *next;
}pidNode;

int sorter(FILE *fp, char *colName, DIR *dir);
Node* readfile(int colInd, FILE *fp);
char *remove_leading_spaces(char* str);
int columnNum(char *row, char *col);
char *tokenizer(int col, char *line);
void FrontBackSplit (Node* source, Node** frontRef, Node** backRef);
void MergeSort (Node** headRef);
Node* SortedMerge( Node* a, Node* b);
void print( Node* a);
void Finish(Node* head);


void directChild(DIR* dir, pidNode * head, int processCounter);
int isDirectory(char d_name[]);
int isCSV(char d_name[]);
pidNode* childpid(pidNode * head, pid_t pid);
void printVals(pid_t pid, pidNode *head, int counter);
