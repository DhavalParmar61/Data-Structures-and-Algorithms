#ifndef HEADER_H
#define HEADER_H

#define max 20
#define def -1
#define unused -1

typedef struct node node;
typedef struct mod mod;
typedef struct queue queue;

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

struct queue
{
  node* head[max];
  int num_el;
  int current_version;
};


queue* initialize();
node* addNode(int data);
node* update_left(queue* list, node* list_ptr, node* newnode, int current_version);
node* update_right(queue* list, node* list_ptr, node* newnode, int current_version);
bool insert_list(queue* list, int data, int index);
int delete_list(queue* list, int index);
bool isempty(queue* deque);
bool insert(queue* deque, int data);
int delete_queue(queue* deque);
void print_queue(queue* list, int version);

#endif
