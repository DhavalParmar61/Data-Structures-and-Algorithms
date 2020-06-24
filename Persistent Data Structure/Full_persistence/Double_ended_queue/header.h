#ifndef HEADER_H
#define HEADER_H

#define max 20
#define str_size 20
#define def -1
#define unused -1

typedef struct node node;
typedef struct mod mod;
typedef struct deque deque;

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

struct deque
{
  node* head[max];
  int num_el;
  int current_version;
};

deque* initialize();
node* addNode(int data, int version);
node* update_left(deque* list, node* list_ptr, node* newnode, int current_version, int version)
node* update_right(deque* list, node* list_ptr, node* newnode, int current_version, int version)
bool isempty(deque* deque, int version);
bool insert(deque* list, int data, int index, int version)
bool insert_front(deque* deque, int data, int version);
bool insert_rear(deque* deque, int data, int version);
bool delete_list(deque* list, int index, int version)
int delete_front(deque* deque, int version);
int delete_rear(deque* deque, int version);
void print_dequeue(deque* list, int version);


#endif
