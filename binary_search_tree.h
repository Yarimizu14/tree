#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

typedef struct node_ {
    int value;
    struct node_ *left;
    struct node_ *right;
} node;

node *new_node(int val);
void print_tree(node* n);
node *insert(node* root, int val);
void insert_propagation(node* n, int val);
int find(node* root, int val);
node *find_propagation(node* n, int val);

#endif
