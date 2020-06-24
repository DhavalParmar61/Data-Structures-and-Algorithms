#ifndef HEADER_H
#define HEADER_H

#define max 20
#define str_size 20
#define def "j"
#define unused -1

typedef struct node node;
typedef struct mod mod;
typedef struct map map;

struct node
{
  char key[str_size];
  char value[str_size];
  int node_version;
  mod* mod;
  node* next;
  node* prev;
};

struct mod
{
  char key[str_size];
  char value[str_size];
  int version;
  node* next;
  node* prev;
};

struct map
{
  node* head[max];
  int current_version;
};

map* initialize();
node* addNode(char input_key[], char input_value[], int version);
void print_map(map* list, int version);
bool insert(map* list, char str[], int index, int version);
bool update(map* list, char str[], int index, int version);
node* update_left(map* list, node* list_ptr, node* newnode, int current_version, int version);
node* update_right(map* list, node* list_ptr, node* newnode, int current_version, int version);
void find(map* list,char find_key[],int version);
bool delete_map(map* list, int index, int version);

#endif
