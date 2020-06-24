#ifndef HEADER_H
#define HEADER_H

struct ASL_element
{
	int size;
	int kval;
	struct ASL_node* head;
	struct ASL_node* tail;
};

struct ASL_node
{
	int buddy_indx;
	int parent_indx;
	int strt;
	int type;
	int tag;
	struct ASL_node* next;
	struct ASL_node* prev;
};

struct Alloc_node
{
	int indx;
	void* ptr;
	int addr;
	struct Alloc_node* next;
};

struct Alloc_list
{
	struct Alloc_node* head;
	struct Alloc_node* tail;
}; 

struct bin_node
{
	void* ptr;
	int addr;
	struct bin_node* next;
};
struct request_node
{
	int time;
	void* ptr;
	struct request_node* next;
};

void initialize_SPheap_allocator(); 
void* alloc(int size);
void* asign(int indx,struct ASL_node* i);
int split1(int indx,int size,struct ASL_node* i);
int split2(int indx,int size,struct ASL_node* i);
void add_allocated_space(int indx,void* ptr,struct ASL_node* i);
void free_alloc(void* ptr);
void dealloc(int indx,int addr);
struct ASL_node* find(int indx,int addr);
void merge(struct ASL_node* i,int indx_i,struct ASL_node* j,int indx_j);
void print_alloc_list();
void print_sheap_data();
int rand_expo();


#endif

