#ifndef HEADER_H
#define HEADER_H

#define max 20
#define str_size 20
#define def -1
#define unused -1

typedef struct node node;
typedef struct mod mod;
typedef struct stack stack;

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

struct stack
{
  node* head[max];
  int num_el;
  int current_version;
};

stack* initialize();
node* addNode(int data, int version);
node* update_left(stack* list, node* list_ptr, node* newnode, int current_version, int version);
node* update_right(stack* list, node* list_ptr, node* newnode, int current_version, int version);
bool insert_list(stack* list, int data, int index, int version);
bool delete_list(stack* list, int index, int version);
bool isempty(stack* stack, int version);
bool push(stack* stack, int data, int version);
int pop(stack* stack, int version);
void print_stack(stack* list, int version);


#endif
