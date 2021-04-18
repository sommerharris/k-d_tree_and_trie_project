

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


// int delete(tree_t* t, int dataX, int dataY) {
//     if(t == NULL) {
//         return 0;
//     }

    
//     deleteHelper(t->root, dataX, dataY);
//     return 1;

    
// }

// struct node* findMax(node_t* n) {
//     node_t* temp = n;

//     //traverse through the tree until find null value with node
//     //this will give us the predecessor 

//     while(temp && n->left != NULL) {
//         temp = temp ->left;
//     }

//     return temp;



// }

// struct node* deleteHelper(node_t* node, int deleteX, int deleteY) {
//     if (node == NULL) {
//         return node;
//     }

    
//     if(node->dataX == deleteX) {
//         if(node->dataY == deleteY) {

//             //account for nodes children 
//             if(node->left == NULL) {
//             node_t* tempNode = makeNode(deleteX, deleteY);
//             tempNode = node->right;
//             free(node);
//             return tempNode;     
            
//         }
//         //if node only has zero children 

//         }
//         else if(node->right == NULL) {
//             node_t* tempNode = makeNode(deleteX, deleteY);
//             tempNode = node->left;
//             free(node);
//             return tempNode;

//         }
    
//******************
//         //if node has two children 
//         //must find pred in the list to replace node 
//         //call helper function to find largest value in left subtree
//         else {

        
//         node_t* findP = findMax(n->left);

//         n->data = findP->data;

//         n->left = deleteHelper(n->left, findP->data);

//         }

//         return n;
        
//     }


//     if(n->data < value) {
//         if(n->right != NULL) {
//             return deleteHelper(n->right, value);
              
//         }
//         else {
//             printf("Value cannot be removed because it does not exist");
//         }
//     if(n->data > value) {
//         if(n->left != NULL) {
//             return deleteHelper(n->left, value);
               
//         }
//          else {
//             printf("Value cannot be removed because it does not exist");
//         }
//     }
//     }
//     return n;
// }


void nearestNodeHelper(node_t* node, int nearestX, int nearestY, int prevSmallest) {
    static int SMALLEST = 0;
    static int smallestXCoord = 0;
    static int smallestYCoord = 0;

    int currentSmallestDis = 0;
    int currentSmallestXCoord = 0;
    int currentSmallestYCoord = 0;
    //traverse through each node in the tree and determine the distance 

    //traverse through the tree until find null value with node
    //this will give us the predecessor 

    if(node->left != NULL && node->right != NULL) {
        
    int distanceLeft = sqrt(pow((node->left->dataX - nearestX), 2.0) + pow((node->left->dataY - nearestY), 2.0));
    int distanceRight = sqrt(pow((node->right->dataX - nearestX), 2.0) + pow((node->right->dataY - nearestY), 2.0));

    if(distanceLeft < distanceRight && prevSmallest == 0) {
        prevSmallest = distanceLeft;
        smallestXCoord = node->left->dataX;
        smallestYCoord= node->left->dataY;  
        //printf("1-(%d,%d) is the closest coordinate to (%d, %d) with a distance of %d \n", smallestXCoord, smallestYCoord, nearestX, nearestY, prevSmallest);
       
        }

    else if(distanceLeft > distanceRight && prevSmallest == 0) {
        prevSmallest = distanceRight;
        smallestXCoord = node->right->dataX;
        smallestYCoord= node->right->dataY;
        //printf("2-(%d,%d) is the closest coordinate to (%d, %d) with a distance of %d \n", smallestXCoord, smallestYCoord, nearestX, nearestY, prevSmallest);
        }

    else if (distanceLeft < distanceRight && prevSmallest != 0) {
            if(distanceLeft < prevSmallest) {
                smallestXCoord = node->left->dataX;
                smallestYCoord= node->left->dataY;  
                prevSmallest = distanceLeft;
                //printf("3-(%d,%d) is the closest coordinate to (%d, %d) with a distance of %d \n", smallestXCoord, smallestYCoord, nearestX, nearestY, prevSmallest);

            }
        }
    

        else if(distanceLeft > distanceRight && prevSmallest != 0)
        if(distanceRight < prevSmallest) {
            smallestXCoord = node->right->dataX;
            smallestYCoord= node->right->dataY;
            prevSmallest = distanceRight;
            //printf("4-(%d,%d) is the closest coordinate to (%d, %d) with a distance of %d \n", smallestXCoord, smallestYCoord, nearestX, nearestY, prevSmallest);
        }

        }

    //if left node is not null and right node 
    else if(node->left != NULL && node->right == NULL){ 
        int distanceLeft = sqrt(pow((node->left->dataX - nearestX), 2.0) + pow((node->left->dataY - nearestY), 2.0));
        

            if(prevSmallest == 0) {    
                smallestXCoord = node->left->dataX;
                smallestYCoord = node->left->dataY;
                prevSmallest = distanceLeft;
                }
                
            

            currentSmallestDis = distanceLeft;
            currentSmallestXCoord = node->left->dataX;
            currentSmallestYCoord = node->left->dataY;

            if(currentSmallestDis < prevSmallest) {
                smallestXCoord = currentSmallestXCoord;
                smallestYCoord = currentSmallestYCoord;
                prevSmallest = currentSmallestDis;
            }

        }

        else if(node->left == NULL && node->right != NULL){ 
            int distanceRight = sqrt(pow((node->right->dataX - nearestX), 2.0) + pow((node->right->dataY - nearestY), 2.0));
            currentSmallestXCoord = node->right->dataX;
            currentSmallestYCoord= node->right->dataY;
            currentSmallestDis = distanceRight;
            
            if(prevSmallest == 0) {
                smallestXCoord = node->left->dataX;
                smallestYCoord = node->left->dataY;
                prevSmallest = distanceRight;
                }
            

            if(prevSmallest != 0) {
                if(currentSmallestDis < prevSmallest) {
                    prevSmallest = currentSmallestDis;
                    smallestXCoord = currentSmallestXCoord;
                    smallestYCoord = currentSmallestYCoord;
                    }
                }
        }  

        if(node->left == NULL && node->right == NULL) {
            printf("HERE");
        }
        printf("\n (%d,%d) is the closest coordinate to (%d, %d) with a distance of %d \n", smallestXCoord, smallestYCoord, nearestX, nearestY, prevSmallest);

    } 

    

    


void findNearestNode(tree_t* t, int nearestX, int nearestY) {
    
    if(t == NULL) {
        return;
    }


    //if value is the root node
    if(t->root->dataX == nearestX) {
        if(t->root->dataY == nearestY) {
            printf("\n (%d, %d) -- Coordinate is found!\n", nearestX, nearestY);
            nearestNodeHelper(t->root, nearestX, nearestY,0);
        return;
        }

        else if (t->root->left == NULL || t->root->right != NULL) {
            if(t->root->left != NULL) {
                nearestNodeHelper(t->root->left, nearestX, nearestY,0);
            }

            if(t->root->right != NULL) {
                nearestNodeHelper(t->root->right, nearestX, nearestY,0);
            }

        }

        else {

            printf("\n (%d, %d) -- Coordinate is not found\n", nearestX, nearestY);
        }
        
 
    

  

    return;
}
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

    insert(myTree, 21,1);

    insert(myTree, 1,19);

  

    

    // printTreeTree(myTree);

    printf("\n");

    printTreeTree(myTree);

    search(myTree, 4,5);

    search(myTree, 13,16);

    search(myTree, 10,3);

    search(myTree, 6,12);

    search(myTree, 3,7);

    search(myTree, 17,15);

    search(myTree, 2,8);

    search(myTree, 10, 19);

    findNearestNode(myTree, 3, 7);

    printf("\nHERE\n");

    findNearestNode(myTree, 9, 1);







return 0;
}