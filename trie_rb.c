#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

//Declare node structure.
typedef struct node {
	//data variable will hold a letter
	char data;
	//children variable will hold an array of node pointers, one for each letter of the alphabet
	struct node* children[ALPHABET_SIZE];
	//endOfWord variable will be Y if end of word, N otherwise
	char endOfWord;
} node_t;


//Create a node.
node_t* makeNode(char a) {
	//Declare iterator variable.
	int i;	

	//Allocate memory for new node.
	node_t* n = (node_t*)malloc(sizeof(node_t));

	//Check that memory allocation worked.
	if (!n) {
		return NULL;
	}

	//Set data to character given as parameter.
	n->data = a;

	//Default is setting endOfWord to N (no).
	n->endOfWord = 'N';

	//Populate children array with NULL pointers.
	for (i = 0; i < ALPHABET_SIZE; i++) {
		n->children[i] = NULL;
	} 

	//Return the new node.	
	return n;
}


//Free memory allocated for node.
void freeNode(node_t* n) {	
	//Check that node is not null.
	if(!n) {
		return;
	}

	//Free the children array.
	free(n->children);

	//Free the node structure.
	free(n);
}


//Free the entire trie.
void freeTrie(node_t* root) {
	//Check that root is not null.
	if(!root) {
		return;
	}

	//Declare iterator variable.
	int i;

	//Go to end of trie's branch and free nodes recursively from the bottom up.
	for (i = 0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != NULL) {
			freeTrie(root->children[i]);
			free(root->children[i]);
		}
	}	
}


//Take a string and remove the first letter for recursive functions.
char* newString(char* c) {
	//Base case is when c is only one character, return null string.
	if (strlen(c) == 1 ) {
		return '\0';
	}

	//Allocate memory for new string.
	char* new = malloc(sizeof(char)*32);

	//Start iterator i at 1 to start copying characters from c at second character.
	int i = 1;

	//Declare iterator j to represent index in new string.
	int j = 0;

	//Copy values from c to new.
	while (c[i]) {
		new[j] = c[i];
		j++;
		i++;
	}
	
	//Return new string.
	return new;
}


//Insert string c in trie starting at root node.
void insert(node_t* root, char* c) {
	//Check that root is not null.
	if(!root) {
		return;
	}
	
	//Base case is null string as c, indicating the end of the word.
	if (c == '\0') {
		root->endOfWord = 'Y';
		return;
	}
	
	//Determine index for first letter of c.	
	int i = (int)c[0] - (int)'a';

	//If given root has a non-null pointer at determined index,
	//call insert again with the child node as the new root and the truncated string.
	if(root->children[i] != NULL) {
		char* new = newString(c);		
		insert(root->children[i], new);
	//If given root has a null pointer at determined index,
	//make new node with the first letter of c and then call
	//insert again with new node as the root and the truncated string.
	} else {
		char* new = newString(c);
		root->children[i] = makeNode(c[0]);
		insert(root->children[i], new);
	}	

}

//Search for string in trie; return true if found, false otherwise.
bool search(node_t* root, char* c) {
	//Check that root is not null.
	if(!root) {
		return;
	}

	//Base case is null string as c. 
	//If endOfWord is set to Y, then the whole word was found and
	//is considered a full word in trie. Otherwise, the whole
	//word was found but the trie does not consider it a full word,
	//so it is considered not found. Example: if 'joy' is searched
	//but only 'joyful' has been added to the trie as a full word,
	//'joy' will not be found.
	if (c == '\0') {
		if(root->endOfWord == 'Y') {
			return true;
		}
		return false;
	} 
	
	//Determine index of the first letter of c.
	int i = (int)c[0] - (int)'a';

	//If root has non-null pointer at i and the data in child node
	//equals the first letter of c, continue calling search recursively.
	if(root->children[i] != NULL && root->children[i]->data == c[0]) {		
		return search(root->children[i], newString(c));
	}
	//If code reaches this line, the search must be unsuccessful because it did not go 
	//into the recursive loop.
	return false;
}


//Helper function for delete function.
void deleteHelper(node_t* root, char* c) {
	//Check that root is not null.
	if(!root) {
		return;
	}

	//Base case is null string as c. 
	//Because we are deleting full word, set endOfWord to N (no). 
	if (c == '\0') {
		root->endOfWord = 'N';
		return;
	}

	//Determine index of first letter of c.	
	int i = (int)c[0] - (int)'a';

	//If the child node at i contains the same letter as 
	//the first letter of c, continue calling deleteHelper recursively.
	//When the function reaches the end of the word and returns,
	//it will iterate through the node's children. If there are non-null children,
	//it will return because this indicates the node has children other than the
	//nodes in the word we are deleting. If it does not return, it will free
	//the node.
	if(root->children[i]->data == c[0]) {		
		deleteHelper(root->children[i], newString(c));
		int j;
		for (j = 0; j < ALPHABET_SIZE; j++) {
			if (root->children[j] != NULL) {
				return;
			}
		}

		free(root->children[i]);
	} else {
		return;
	} 
}


//Deletes a word from the trie.
void delete(node_t* root, char* c) {
	//Only run delete function if search function returns true.
	if (search(root, c)) {
		deleteHelper(root, c);
	}
}


//Helper function for nearest word.
//Function comes here after traversing all letters in the original
//word that exist in the tree without reaching a full word.
void nearestHelper2(node_t* root, char* fullWord) {
	//Declare iterator variable.
	int i;

	//Iterate through given root's children.
	for (i = 0; i < ALPHABET_SIZE; i++) {
		//If non-null pointer is found...
		if (root->children[i] != NULL) {
			//...and endOfWord is Y (yes), add letter to end of fullWord
			//and break out of loop.
			if(root->children[i]->endOfWord == 'Y') {	
				fullWord[strlen(fullWord)] = root->children[i]->data;
				break;
			//...and endOffWord is N (no), add letter to end of fullWord
			//and call helper function recursively to continue down the word.
			} else {
				fullWord[strlen(fullWord)] = root->children[i]->data;
				nearestHelper2(root->children[i], fullWord);
			}
			return;
		}
	}
}

//Helper function for nearest word.
char* nearestHelper1(node_t* root, char* current, char* fullWord) {
	//Check that root is not null.
	if(!root) {
		return;
	}
	
	//Base case is null string as current string.
	//If the current root is at the end of a word, return fullWord,
	//which will be the same as the original word.
	//Otherwise, go to nearestHelper2 to find next letter.
	if (current == '\0') {
		if(root->endOfWord == 'Y') {
			return fullWord;
		} else {
			nearestHelper2(root, fullWord);
			return fullWord;
		}
	}

	//Determine index of first letter of current string.
	int i = (int)current[0] - (int)'a';


	//If the child at index i is not null and its data is the same letter
	//as the first letter of current string, add this letter to the end of 
	//fullWord and call nearestHelper1 recursively for next letter. 
	if (root->children[i] != NULL && current[0] == root->children[i]->data) {
		fullWord[strlen(fullWord)] = current[0];
		nearestHelper1(root->children[i], newString(current), fullWord);
	//Otherwise, if the length of fullWord is 0, determine the closest non-null
	//index to i. Send the child at this index to nearestHelper2. 
	} else if(strlen(fullWord) == 0) {
		int forward = 0;
		int backward = 0;
		int j = i;
		int k = i;
		while(root->children[j % ALPHABET_SIZE] == NULL) {
			forward++;
			j++;
		}
		while(root->children[k % ALPHABET_SIZE]==NULL) {
			backward++;
			k--;
		}
		if (forward <= backward) {
			fullWord[strlen(fullWord)] = root->children[j % ALPHABET_SIZE]->data;
			nearestHelper2(root->children[j % ALPHABET_SIZE], fullWord);
		} else {
			fullWord[strlen(fullWord)] = root->children[k % ALPHABET_SIZE]->data;
			nearestHelper2(root->children[k % ALPHABET_SIZE], fullWord);
		}
	//If the length of fullWord is greater than 0, send the root to 
	//nearestHelper2 for next letter.	
	} else {
		nearestHelper2(root, fullWord);
	} 

	//Return fullWord string.
	return fullWord;		
}


//Look for nearest word to given string c.
char* nearestWord(node_t* root, char* c) {
	//If word already exists in trie, return the word.
	if (search(root, c)) {
		return c;
	}

	//Otherewise, allocate memory for new string to hold
	//letters as we traverse the trie.
	char* fullWord = (char*)malloc(sizeof(char)*32);

	//Send root, string, and fullWord to nearestHelper1.
	return nearestHelper1(root, c, fullWord);

	//Because of the recursive structure, fullWord is never
	//freed, which will cause memory leaks.
}


//Helper function for print function.
void printHelper(node_t* root, char* current) {
	//Check that root is not null.
	if(!root) {
		return;
	}

	//Declare iterator variable.
	int i;

	//Iterate through root's children until a non-null index.
	//If index is the end of a word, add the letter to the current
	//string and print the string with a new line. Otherwise, just
	//add letter to the current string. In both cases, call printHelper
	//recursively with child as root. 
	for (i = 0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != NULL) {
			if (root->children[i]->endOfWord == 'Y') {
				current[strlen(current)] = root->children[i]->data;
				printf("%s\n", current);
			} else {
				current[strlen(current)] = root->children[i]->data;
			} 
			printHelper(root->children[i], current);
		}
	}
	//After traversing entire alphabet for a node, remove the letter associated
	//with that node from the current string.
	current[strlen(current)-1] = '\0';
		
}


//Print all words in trie.
void print(node_t* root) {
	//Allocate memory for string to hold characters as we traverse trie.
	char* current = malloc(sizeof(char)*32);

	//Send root and current string to printHelper. 
	printHelper(root, current);

	//Free current string memory allocation.
	free(current);
}


//Main function to test trie functions.
int main() {
	//Make root node.
	node_t* root = makeNode(' ');

	//Insert and print words in trie.
	printf("Contents of trie:\n");
	insert(root,"test");
	insert(root,"string");
	insert(root,"testing");
	insert(root,"you");
	insert(root,"apple");
	insert(root,"stringy");
	insert(root,"application");
	insert(root,"app");
	insert(root,"arcade");
	insert(root,"use");
	print(root);


	//Search for words and print results.
	printf("\nSearch tests:\n");
	if (search(root, "apple")) {
		printf("apple was found.\n");
	} else {
		printf("apple was not found.\n");
	}
	if (search(root, "app")) {
		printf("app was found.\n");
	} else {
		printf("app was not found.\n");
	}
	if (search(root, "test")) {
		printf("test was found.\n");
	} else {
		printf("test was not found.\n");
	}
	if (search(root, "testing")) {
		printf("testing was found.\n");
	} else {
		printf("testing was not found.\n");
	}
	if (search(root, "banana")) {
		printf("banana was found.\n");
	} else {
		printf("banana was not found.\n");
	}
	if (search(root, "useful")) {
		printf("useful was found.\n");
	} else {
		printf("useful was not found.\n");
	}
	if (search(root, "us")) {
		printf("us was found.\n");
	} else {
		printf("us was not found.\n");
	}


	//Delete words that exist in trie and print results.
	printf("\nAfter deleting \"string\" and \"testing\": \n");

	delete(root,"string");
	delete(root,"testing");
	print(root);

	//Delete words that do not exist in trie and print results.
	printf("\nAfter deleting \"banana\" and \"us\": \n");

	delete(root,"us");
	delete(root,"banana");
	print(root);


	//Look for and print nearest full words.
	printf("\nPrint nearest full word to \"str\":\n");
	printf("%s\n", nearestWord(root,"str"));	

	printf("\nPrint nearest full word to \"a\":\n");
	printf("%s\n", nearestWord(root,"a"));	

	printf("\nPrint nearest full word to \"you\":\n");
	printf("%s\n", nearestWord(root,"you"));	

	printf("\nPrint nearest full word to \"math\":\n");
	printf("%s\n", nearestWord(root,"math"));	

	printf("\nPrint nearest full word to \"apply\":\n");
	printf("%s\n", nearestWord(root,"apply"));

	printf("\nPrint nearest full word to \"your\":\n");
	printf("%s\n", nearestWord(root,"your"));
	
	printf("\nPrint nearest full word to \"zoo\":\n");
	printf("%s\n", nearestWord(root,"zoo"));

	printf("\nPrint nearest full word to \"useful\":\n");
	printf("%s\n", nearestWord(root,"useful"));

	printf("\nPrint nearest full word to \"applic\":\n");
	printf("%s\n", nearestWord(root,"applic"));

	//Free trie.
	freeTrie(root);

	return 0;
}

