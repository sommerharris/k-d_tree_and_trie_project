
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct node {
    int dataX;
    int dataY;
    struct node* left;
    struct node* right;   
}node_t;

typedef struct tree {
    node_t* root;
}tree_t;

//this creates a new tree with a NULL root and numNodes of 0.
tree_t* makeTree() {
    tree_t* newTree = (tree_t*)malloc(sizeof(tree_t));

    if(newTree == NULL) {
        return 0;
    }

    newTree->root = NULL;

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

    if(treeNode->dataX == searchX && treeNode->dataY == searchY) {
        printf("\n (%d,%d) -- Coordinate is found!\n", searchX, searchY);
    }
    //traverse to the right child
    if(treeNode->dataY < searchY) {

        if(treeNode->right != NULL) {
            searchHelperX(treeNode->right, searchX, searchY);
            

        }

        else {
            printf("\n (%d, %d) -- Coordinate is NOT found!\n", searchX, searchY);
            
        }
    }

        //traverse to the LEFT child
    if(treeNode->dataY > searchY) {

        if(treeNode->left == NULL) {
            printf("\n (%d, %d) -- Coordinate is NOT found!\n", searchX, searchY);

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

    if(treeNode->dataX == searchX && treeNode->dataY == searchY) {
        printf("\n (%d, %d) -- Coordinate is found!\n", searchX, searchY);
    }

    if(searchX > treeNode->dataX) {

        //travel to the right side of the tree

        if(treeNode->right != NULL) {
            searchHelperY(treeNode->right, searchX, searchY);
        }


        //if the right child is null, we know that there will not be a match further down the tree
        else {
            printf("\n (%d, %d) -- *1Coordinate is not found\n", searchX, searchY);
            
        }
    }

    if(searchX < treeNode->dataX)  {
        

        // traverse to LEFT side of tree

    if (treeNode->left!= NULL) {
        searchHelperY(treeNode->left, searchX, searchY);
        }

    else {
        printf("\n(%d, %d) -- **Coordinate is not found\n", searchX, searchY);
        return 1;
        }
    }

    return 0;



}




void search(tree_t* t, int searchX, int searchY) {
    if(t == NULL) {
        return;
    }

    

    //if value is the root node
    if(t->root->dataX == searchX && t->root->dataY == searchY) {
        
         printf("\n (%d, %d) -- Coordinate is found!\n", searchX, searchY);
        return;
        }
 
    //else we call 

    
    searchHelperX(t->root, searchX, searchY);
        
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

void printResultNN(int nnX, int nnY, double distance, int xCoord, int yCoord);
//prints the tree in sorted order from smallest to largest. 
void NNHelper(node_t* treeNode, int nnX, int nnY) {
    static double smallestDistance = 0;
    static int xCoord = 0;
    static int yCoord = 0;

    if(treeNode == NULL) {
        return;
    }
    
    
    NNHelper(treeNode->left, nnX, nnY);
    
    //distance function
    double distance = 0;
    distance = sqrt((pow((treeNode->dataX - nnX), 2.0) + pow((treeNode->dataY - nnY), 2.0)));

    //two print statements 
    printf("\n (%d,%d) is at a distance of %f to coordinate (%d, %d)  \n", nnX, nnY, distance, treeNode->dataX, treeNode->dataY);
    printResultNN(nnX, nnY, smallestDistance, xCoord, yCoord);

 
    
    NNHelper(treeNode->right, nnX, nnY);

    if(nnX != treeNode->dataX && nnY != treeNode->dataY) {

    
        if(smallestDistance == 0) {
            smallestDistance = distance;
            xCoord = treeNode->dataX;
            yCoord = treeNode->dataY;
        } 
        else if(distance < smallestDistance) {
            smallestDistance = distance;
            xCoord = treeNode->dataX;
            yCoord = treeNode->dataY;
        }
    }
    
    
    


    
    return;
    
}

//printing our tree in order smallest to largest

//prints the tree. 
void NN(tree_t* t, int nnX, int nnY) {
    if(t == NULL) {
        return;
    }
    NNHelper(t->root, nnX, nnY);
}

void printResultNN(int nnX, int nnY, double distance, int xCoord, int yCoord) {
    printf("\n (%d,%d) is the CURRENT SMALLEST distance of %f to coordinate (%d, %d)  \n", nnX, nnY, distance, xCoord, yCoord);
 return;
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



//frees the tree in sorted order from smallest to largest. 
void freeHelper(node_t* treeNode) {
    if(treeNode == NULL) {
        return;
    }


    freeHelper(treeNode->left);
    freeHelper(treeNode->right);
    printf("\n deleting node: %d,%d\n", treeNode->dataX, treeNode->dataY);
    free(treeNode);

    return;
}

//printing our tree in order smallest to largest

//prints the tree. 
void freeTree(tree_t* t) {
    if(t == NULL) {
        return;
    }
    freeHelper(t->root);
    free(t);
    
}




int main() {
    tree_t* myTree = makeTree();
    node_t* start = makeNode(3,7);

    myTree->root = start;

    

    insert(myTree, 17,15);

    insert(myTree, 13,16);
    

    insert(myTree, 6,12);

    insert(myTree, 9,1);

    insert(myTree, 2,8);

    insert(myTree, 10,19);

   // insert(myTree, 21,1);

    insert(myTree, 1,19);

    printTreeTree(myTree);

    printf("\n");

    printTreeTree(myTree);
    printf("\n");


   

    // search(myTree, 4,5);

    // search(myTree, 13,16);

    // search(myTree, 10,3);

    // search(myTree, 6,12);

    // search(myTree, 3,7);

    // search(myTree, 17,15);

    // search(myTree, 2,8);

    // search(myTree, 10, 19);

    NN(myTree, 3, 7);

    // NN(myTree, 10, 19);

    // NN(myTree, 17, 15);

    // printTreeTree(myTree);

     freeTree(myTree);

    








return 0;
}