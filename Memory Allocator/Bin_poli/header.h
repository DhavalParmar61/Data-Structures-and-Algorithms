#ifndef HEADER_H
#define HEADER_H
struct node
{
	int i;
	float a;
	struct node* right;
	struct node* left;
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

struct node *divide_poly(struct node *h1,struct node *h2);
struct node *input_poly();
void output_poly(struct node *header);
void initialize_bin(int size);
void* alloc_bin(int size);
void free_bin(struct node* ptr1);
void print_bin_data();

#endif
