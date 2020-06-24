#ifndef HEADER_H
#define HEADER_H

#define max 20
#define def -1
#define unused -1

typedef struct node node;
typedef struct mod mod;
typedef struct list list;

struct node
{
  int data;
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
node* addNode(int data);
node* update_left(list* list, node* list_ptr, node* newnode, int current_version);
node* update_right(list* list, node* list_ptr, node* newnode, int current_version);
bool insert_list(list* list, int data, int index);
int delete_list(list* list, int index);
void print_list(list* list, int version);
bool insert(list* list, int data, int index);
bool update(list* list, int data, int index);
bool delete_node(list* list, int index);


#endif
