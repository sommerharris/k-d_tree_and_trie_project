

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

int insertHelperX(node_t* treeNode, node_t* newNode);

int insertHelperY(node_t* treeNode, node_t* newNode) {

    if(newNode->dataY < treeNode->dataY) {
        //traverse left through the tree
        //check and see if the left pointer is null
        //if yes, add the data point here

        if(treeNode->left == NULL) {
            treeNode->left = newNode;
            return 1;
        }

        else {
            insertHelperX(treeNode->left, newNode);
        }
    }

    else if (newNode->dataY > treeNode->dataY) {

        if(treeNode->right == NULL) {
            treeNode->right = newNode;
            return 1;
        }

        else{
            insertHelperX(treeNode->right, newNode);
        }
    }
    return 1;
    


}

int insertHelperX(node_t* treeNode, node_t* newNode) {
//start on the x level every time
//continue to the y level, and then if need to continue will recursively
//the function to continue adding to the tree
    if(newNode->dataX < treeNode->dataX) {

        //traverse LEFT through the tree
        //check and see if the left pointer is null
        //if yes, add the data point here

        if(treeNode->left == NULL) {
            treeNode->left = newNode;
            return 1;
        }

        //now if the left is not NULL
        //we compare the Y values 

        else {
            insertHelperY(treeNode->left, newNode);
        }

    }

    else if(newNode->dataX > treeNode->dataX) {
        //traverse RIGHT through the tree
        //check and see if the RIGHT pointer is null
        //if yes, add the data point here

        if(treeNode->right == NULL) {
            treeNode->right = newNode;
            return 1;
        }

        else {
            insertHelperY(treeNode->right, newNode);
        }
    }
    return 1;



    }

int searchHelperX(node_t* treeNode, int searchX, int searchY);

//just use searchHelperY to traverse through the Y values because we know if the 
//x values are not equal, then the coordinates are not equal. Thus we neeed to 
//travel to the next "X" layer of the tree, and to do this we must traverse through 
//the y-layer. 
int searchHelperY(node_t* treeNode, int searchX, int searchY) {
    if (treeNode == NULL) {
        return 0;
    }

    //traverse to the right child
    if(treeNode->dataY < searchY) {

        if(treeNode->right == NULL) {
            printf("\n (%d, %d) -- Coordinate is found!\n", searchX, searchY);

        }

        else {
            searchHelperX(treeNode->right, searchX, searchY);
        }
    }

        //traverse to the LEFT child
    if(treeNode->dataY > searchY) {

        if(treeNode->left == NULL) {
            printf("\n (%d, %d) -- Coordinate is found!\n", searchX, searchY);

        }

        else {
            searchHelperX(treeNode->left, searchX, searchY);
        }
    }

    return 1;
}


int searchHelperX(node_t* treeNode, int searchX, int searchY) {
    if (treeNode == NULL) {
        return 0;
    }

    //check if value is the current node

    if(treeNode->dataX == searchX & treeNode->dataY == searchY) {
        printf("\n (%d, %d) -- Coordinate is found!\n", searchX, searchY);
    }

    if(treeNode->dataX < searchX) {

        //travel to the right side of the tree

        if(treeNode->right != NULL) {
            searchHelperY(treeNode->right, searchX, searchY);
        }


        //if the right child is null, we know that there will not be a match further down the tree
        else {
            printf("\n (%d, %d) -- !Coordinate is not found\n", searchX, searchY);
            
        }
    }

    if(treeNode->dataX > searchX) {
        

        // traverse to LEFT side of tree

    if (treeNode->right != NULL) {
        searchHelperY(treeNode->right, searchX, searchY);
        }

    else {
        printf("\n(%d, %d) -- *Coordinate is not found\n", searchX, searchY);
        return 1;
        }
    }

    return 0;



}




int search(tree_t* t, int searchX, int searchY) {
    if(t == NULL) {
        return 0;
    }

    //if value is the root node
    if(t->root->dataX == searchX) {
        if(t->root->dataY == searchY) {
            printf("\n (%d, %d) -- Coordinate is found!\n", searchX, searchY);
        return 1;
        }

        else {
            printf("\n (%d, %d) -- *Coordinate is not found\n", searchX, searchY);

        }

        }
 
    //else we call 

    else {
        searchHelperY(t->root, searchX, searchY);
    }

    return 0;
}
        

//prints the tree in sorted order from smallest to largest. 
void printHelperX(node_t* treeNode) {
    if(treeNode == NULL) {
        return;
    }

    printHelperX(treeNode->left);
    printf("%d ", treeNode->dataX);
    printHelperX(treeNode->right);

    return;
}

//printing our tree in order smallest to largest

//prints the tree. 
void printTreeX(tree_t* t) {
    if(t == NULL) {
        return;
    }
    printHelperX(t->root);
}

//prints the tree in sorted order from smallest to largest. 
void printHelperY(node_t* treeNode) {
    if(treeNode == NULL) {
        return;
    }

    printHelperY(treeNode->left);
    printf("%d ", treeNode->dataY);
    printHelperY(treeNode->right);

    return;
}

//printing our tree in order smallest to largest

//prints the tree. 
void printTreeY(tree_t* t) {
    if(t == NULL) {
        return;
    }
    printHelperY(t->root);
}

//prints the tree in sorted order from smallest to largest. 
void printHelperTree(node_t* treeNode) {
    if(treeNode == NULL) {
        return;
    }

    printHelperTree(treeNode->left);
    printf("(%d, %d) ", treeNode->dataX, treeNode->dataY);
    printHelperTree(treeNode->right);

    return;
}

//printing our tree in order smallest to largest

//prints the tree. 
void printTreeTree(tree_t* t) {
    if(t == NULL) {
        return;
    }
    printHelperTree(t->root);
}



    













//INSERTION
//we will do two levels on the insertion to account for the swapping of
//x and y, then we can recursively call the function to continue on with the 
//lowest y node value

int insert(tree_t* t, int dataX, int dataY) {

    if(t == NULL) {
        return 0;
    }

    node_t* newNode = makeNode(dataX, dataY);

    if(t->root == NULL) {
        t->root = newNode;
        return 1;
    }

    insertHelperX(t->root, newNode);
    return 1;

}

int main() {
    tree_t* myTree = makeTree();
    node_t* start = makeNode(10,3);

    myTree->root = start;

    

    insert(myTree, 2,20);

    

    insert(myTree, 4,5);

  

    

    // printTreeTree(myTree);

    printf("\n");

    printTreeTree(myTree);

    search(myTree, 4,5);

    search(myTree, 2,20);

    search(myTree, 10,3);




return 0;
}