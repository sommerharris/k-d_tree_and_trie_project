

#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int dataX;
    int dataY;
    struct node* left;
    struct node* right;   
}node_t;

typedef struct tree {
    node_t* root;
    int numNodes;
}tree_t;

//this creates a new tree with a NULL root and numNodes of 0.
tree_t* makeTree() {
    tree_t* newTree = (tree_t*)malloc(sizeof(tree_t));

    if(newTree == NULL) {
        return 0;
    }

    newTree->root = NULL;
    newTree->numNodes = 0;

    return newTree;
}


//make node function which creates a new node with a given value
//different from a usual BST, we separate the x and y data into two pointers
//in the node. This will allow us to switch back and forth between 
//the values when determining where to place it in the tree
node_t *makeNode(int x, int y) {
    node_t* newNode = (node_t*)malloc(sizeof(node_t));

    if (newNode == NULL) {
        return NULL;
    }

    newNode->dataX = x;
    newNode->dataY = y;
    newNode->right = NULL;
    newNode->left = NULL;

    return newNode;
}