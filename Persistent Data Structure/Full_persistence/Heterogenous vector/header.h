#ifndef HEADER_H
#define HEADER_H

#define max 20
#define str_size 20
#define def -1
#define unused -1

typedef struct node node;
typedef struct mod mod;
typedef struct list list;

struct node
{
  char *identifier;
  int node_version;
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


list* initialize();
node* addNode(int data, int version);
node* float_addNode(float data, int version);
node* char_addNode(char data, int version);
node* double_addNode(double data, int version);
void print_list(list* list, int version);
bool insert(list* list, char str[], int index, int version);
bool update(list* list, char str[], int index, int version);
bool delete_list(list* list, int index, int version);

#endif
