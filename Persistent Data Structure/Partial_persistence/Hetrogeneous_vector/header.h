#ifndef HEADER_H
#define HEADER_H

#define max 20
#define def -1
#define unused -1
#define string_size 50

typedef struct node node;
typedef struct mod mod;
typedef struct list list;

struct node
{
  char *identifier; 
  int int_data;
  float float_data;
  char char_data;
  double double_data;
  
  mod* mod;
  node* next;
  node* prev;
};

struct mod
{
  char *identifier;
  int int_data;
  float float_data;
  char char_data;
  double double_data;
  
  int version;
  node* next;
  node* prev;
};

struct list
{
  node* head[max];
  int current_version;
};

node* addNode(int data);
list* initialize();
void print_list(list* list, int version);
node* update_left(list* list, node* list_list, node* newnode, int current_version);
node* update_right(list* list, node* list_list, node* newnode, int current_version);
bool insert(list* list, char str[], int index);
bool update(list* list, char str[], int index);
bool delete_list(list* list, int index);

#endif
