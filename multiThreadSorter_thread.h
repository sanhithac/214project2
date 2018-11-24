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

typedef struct row{
	char* color;
	char* director_name;
	int num_critic_for_reviews;
	int duration;
	int director_facebook_likes;
	int actor_3_facebook_likes;
	int actor_2_name;
	int actor_1_facebook_likes;
	int gross;
	char* genres;
	char* actor_1_name;
	char* movie_title;
	int num_voted_users;
	int cast_total_facebook_likes;
	char* actor_3_name;
	int facenumber_in_poster;
	char* plot_keywords;
	char* movie_imdb_link;
	int num_user_of_reviews;
	char* language;
	char* country;
	char* content_rating;
	int budget;
	int title_year;
	int actor_2_facebook_likes;
	double imdb_score;
	double aspect_ratio;
	int movie_facebook_likes;
}row;
