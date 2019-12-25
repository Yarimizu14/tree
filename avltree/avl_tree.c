#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "avl_tree.h"

#define max(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })

int_fast8_t subtree_height(node* n) {
    if (n == NULL) {
        return 0;
    }
    // TODO: stop calc recursively
    return max(subtree_height(n->left), subtree_height(n->right)) + 1;
}

int_fast8_t bias(node* n) {
    if (n == NULL) {
        return 0;
    }
    return subtree_height(n->left) - subtree_height(n->right);
};

node* new_node(int_fast16_t val) {
    node* n = malloc(sizeof(node));
    n->value = val;
    n->height = 0;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/*
 * Rotate node right
 */
node *rotateRight(node* root) {
    node* new_root = root->left;
    node* tmp = new_root->right;

    new_root->right = root;
    root->left = tmp;

    root->height = subtree_height(root);
    new_root->height = subtree_height(new_root);

    return new_root;
};

/*
 * Rotate node left
 */
node *rotateLeft(node* root) {
    node* new_root = root->right;
    node* tmp = new_root->left;

    new_root->left = root;
    root->right = tmp;

    root->height = subtree_height(root);
    new_root->height = subtree_height(new_root);

    return new_root;
};

node *insert(node* n, int_fast16_t val) {
    if (n == NULL)
        return new_node(val);

    if (n->value == val)
        return n;

    // insert to tree
    if (n->value < val) {
        n->right = insert(n->right, val);
        printf("node %d is inserted right of %d\n", val, n->value);
    } else if (n->value > val) {
        n->left = insert(n->left, val);
        printf("node %d is inserted left of %d\n", val, n->value);
    }

    // update height of the node
    n->height = subtree_height(n);

    // calculate bias of the node
    int b = bias(n);

    // Left side of tree is taller than Right
    if (b > 1) {
        int_fast8_t lbias = bias(n->left);
        // Left Left case (left child's left child is the tallest)
        if (lbias >= 1) {
            return rotateRight(n);
        }
        // Left Right case (left child's right child is the tallest)
        if (lbias <= -1) {
            n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
    } else if (b < -1) {
        int_fast8_t rbias = bias(n->right);
        // Right Left case (right child's left child is the tallest)
        if (rbias >= 1) {
            n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        // Right Right case (right child's right child is the tallest)
        if (rbias <= -1) {
            return rotateLeft(n);
        }
    }
    return n;
}

int main() {
    node* root = insert(NULL, 10);
    insert(root, 1);
    insert(root, 13);
    insert(root, 2);
    insert(root, 6);
    insert(root, 14);
    insert(root, 4);
    insert(root, 12);
    insert(root, 3);
    insert(root, 9);
    insert(root, 11);
    insert(root, 5);
    insert(root, 8);
    insert(root, 7);
    printf("root height is %d\n", root->height);
    printf("root bias is %d\n", bias(root));
};
