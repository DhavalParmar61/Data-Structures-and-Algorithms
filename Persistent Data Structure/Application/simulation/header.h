#ifndef HEADER_H
#define HEADER_H
#define max 1000
#define def -1
#define unused -1

typedef struct node node;
typedef struct mod mod;
typedef struct list list;

struct node
{
  int data;
  float fw_prob;
  float bw_prob;
  float ss_prob;
  mod* mod;
  node* next;
  node* prev;
};

struct mod
{
  int data;
  float fw_prob;
  float bw_prob;
  float ss_prob;
  int version;
  node* next;
  node* prev;
};

struct list
{
  node* head[max];
  int current_version;
};


void simulate(list* list,int version,int strt_state,int no_transition);
void transit(node* state_ptr,int version,int no_transition);
node* addNode(int data,float fw_prob,float bw_prob,float ss_prob);
list* init_list();
void print_list(list* list, int version);
node* update_parentleft(list* list, node* list_ptr, node* newnode, int current_version);
node* update_parentright(list* list, node* list_ptr, node* newnode, int current_version);
bool insert(list* list, int data, int index,float fw_prob,float bw_prob,float ss_prob);
bool update(list* list, int data, int index,float fw_prob,float bw_prob,float ss_prob);
bool delete_node(list* list, int index);

#endif
