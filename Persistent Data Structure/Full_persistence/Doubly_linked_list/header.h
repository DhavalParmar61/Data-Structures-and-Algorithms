#ifndef HEADER_H
#define HEADER_H

#define max 20
#define def -1
#define unused -1
#define str_size 50

typedef struct node node;
typedef struct mod mod;
typedef struct list list;

struct node
{
  int data;
  int node_version;
  mod* mod;
  node* next;
  node* prev;
};

struct mod
{
  int data;
  int version;
  node* next;
  node* prev;
};

struct list
{
  node* head[max];
  int current_version;
};

list* initialize();
node* addNode(int data, int version);
void print_list(list* list, int version);
node* update_left(list* list, node* list_ptr, node* newnode, int current_version, int version);
node* update_right(list* list, node* list_ptr, node* newnode, int current_version, int version);
bool update(list* list, int data, int index, int version);
bool insert(list* list, int data, int index, int version);
bool delete_list(list* list, int index, int version);


#endif
