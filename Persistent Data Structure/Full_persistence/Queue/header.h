#ifndef HEADER_H
#define HEADER_H

#define max 20
#define str_size 20
#define def -1
#define unused -1

typedef struct node node;
typedef struct mod mod;
typedef struct queue queue;

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

struct queue
{
  node* head[max];
  int num_el;
  int current_version;
};

queue* initialize();
node* addNode(int data, int version);
node* update_parentleft(queue* list, node* list_ptr, node* newnode, int current_version, int version);
node* update_parentright(queue* list, node* list_ptr, node* newnode, int current_version, int version);
bool insert_list(queue* list, int data, int index, int version);
bool isempty(queue* queue, int version);
bool insert(queue* queue, int data, int version);
int delete_queue(queue* queue, int version);
void print_queue(queue* list, int version);


#endif
