#ifndef HEADER_H
#define HEADER_H

#define max 20
#define def -1
#define unused -1

typedef struct node node;
typedef struct mod mod;
typedef struct dequeue dequeue;

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

struct dequeue
{
  node* head[max];
  int num_el;
  int current_version;
};

dequeue* initialize();
bool isempty(dequeue* deque);
bool insert_front(dequeue* deque, int data);
bool insert_rear(dequeue* deque, int data);
int delete_front(dequeue* deque);
int delete_rear(dequeue* deque);
void print_dequeue(dequeue* list, int version);
node* update_left(dequeue* list, node* list_ptr, node* newnode, int current_version);
node* update_right(dequeue* list, node* list_ptr, node* newnode, int current_version);
bool insert_list(dequeue* list, int data, int index);
int delete_list(dequeue* list, int index);

#endif
