#ifndef HEADER_H
#define HEADER_H

#define max 20
#define def "j"
#define unused -1
#define str_size 50

typedef struct node node;
typedef struct mod mod;
typedef struct map map;

struct node
{
  char key[str_size];
  char value[str_size];
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
node* addNode(char input_key[], char input_value[]);
node* update_left(map* list, node* list_ptr, node* newnode, int current_version);
node* update_right(map* list, node* list_ptr, node* newnode, int current_version);
bool insert_list(map* list, int data, int index);
bool delete_list(map* list, int index);
void print(map* list, int version);
bool insert(map* list, char str[], int index);
bool update(map* list, char str[], int index);
void find(map* list, char str[]);
bool delete_map(map* list, int index);



#endif
