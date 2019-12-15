#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "binary_search_tree.h"

node *new_node(int val) {
    node* ret = malloc(sizeof(node));
    ret->value = val;
    ret->left = NULL;
    ret->right = NULL;

    return ret;
};

node *insert(node* root, int val) {
    if (root == NULL) {
        root = new_node(val);
        return root;
    }
    insert_propagation(root, val);
    return root;
}

void insert_propagation(node* n, int val) {
    if (n->value > val) {
        if (n->left == NULL) {
            n->left = new_node(val);
            return;
        }
        insert_propagation(n->left, val);
    } else {
        if (n->right == NULL) {
            n->right = new_node(val);
            return;
        }
        insert_propagation(n->right, val);
    }
}

int find(node* root, int val) {
    node *ret = find_propagation(root, val);
    if (ret != NULL) {
        return ret->value;
    }
    return -1;
}

node *find_propagation(node* n, int val) {
    if (n == NULL) {
        return NULL;
    }
    if (n->value == val) {
        return n;
    } else if (n->value > val) {
        return find_propagation(n->left, val);
    } else {
        return find_propagation(n->right, val);
    }
}

void print_tree(node* n) {
    if (n == NULL) {
        return;
    }
    printf("%d\n", n->value);
    print_tree(n->left);
    print_tree(n->right);
}

int main() {
    node* root = new_node(3);
    insert(root, 5);
    insert(root, 8);
    print_tree(root);
    printf("#####################################\n");
    int ret = find(root, 5);
    printf("%d\n", ret);
    int ret2 = find(root, 10);
    printf("%d\n", ret2);
    return 0;
};
