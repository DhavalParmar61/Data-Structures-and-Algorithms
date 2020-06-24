#ifndef HEADER_H
#define HEADER_H

#define max 20
#define def -1
#define unused -1

typedef struct node node;
typedef struct mod mod;
typedef struct stack stack;

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

struct stack
{
  node* head[max];
  int num_el;
  int current_version;
};


stack* initialize();
node* addNode(int data);
node* update_left(stack* list, node* list_ptr, node* newnode, int current_version);
node* update_right(stack* list, node* list_ptr, node* newnode, int current_version);
bool insert_list(stack* list, int data, int index);
int delete_list(stack* list, int index);
bool isempty(stack* deque);
bool push(stack* deque, int data);
int pop(stack* deque);
void print_stack(stack* list, int version);

#endif
