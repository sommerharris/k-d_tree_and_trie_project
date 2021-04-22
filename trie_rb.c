#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26


typedef struct node {
	char data;
	struct node* children[ALPHABET_SIZE];
	char endOfWord;
} node_t;


node_t* makeNode(char a) {
	int i;	

	node_t* n = (node_t*)malloc(sizeof(node_t));

	if (!n) {
		return NULL;
	}

	n->data = a;
	n->endOfWord = 'N';

	for (i = 0; i < ALPHABET_SIZE; i++) {
		n->children[i] = NULL;
	} 

	return n;
}

void freeNode(node_t* n) {
	free(n->children);
	free(n);
}

void freeTrie(node_t* root) {
	if(!root) {
		return;
	}

	int i;
	for (i = 0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != NULL) {
			freeTrie(root->children[i]);
			free(root->children[i]);
		}
	}	
}


char* newString(char* c) {
	if (strlen(c) == 1 ) {
		return '\0';
	}

	char* new = malloc(sizeof(char)*32);
	int i = 1;
	int j = 0;

	while (c[i]) {
		new[j] = c[i];
		j++;
		i++;
	}
	
	return new;
}



void insert(node_t* root, char* c) {
	if (c == '\0') {
		root->endOfWord = 'Y';
		return;
	}
		
	int i = (int)c[0] - (int)'a';

	if(root->children[i] != NULL) {
		char* new = newString(c);		
		insert(root->children[i], new);
	} else {
		char* new = newString(c);
		root->children[i] = makeNode(c[0]);
		insert(root->children[i], new);
	}	

}


bool search(node_t* root, char* c) {
	if (c == '\0') {
		if(root->endOfWord == 'Y') {
			return true;
		}
		return false;
	} 
	
	int i = (int)c[0] - (int)'a';

	if(root->children[i] != NULL && root->children[i]->data == c[0]) {		
		return search(root->children[i], newString(c));
	}
	return false;
}


void deleteHelper(node_t* root, char* c) {

	if (c == '\0') {
		root->endOfWord = 'N';
		return;
	}
		
	int i = (int)c[0] - (int)'a';

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

void delete(node_t* root, char* c) {
	if (search(root, c)) {
		deleteHelper(root, c);
	}
}


void nearestHelper2(node_t* root, char* fullWord) {
	int i;
	for (i = 0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != NULL) {
			if(root->children[i]->endOfWord == 'Y') {	
				fullWord[strlen(fullWord)] = root->children[i]->data;
				break;
			} else {
				fullWord[strlen(fullWord)] = root->children[i]->data;
				nearestHelper2(root->children[i], fullWord);
			}
			return;
		}
	}
}

char* nearestHelper1(node_t* root, char* current, char* fullWord) {
	if (current == '\0') {
		if(root->endOfWord == 'Y') {
			return fullWord;
		} else {
			nearestHelper2(root, fullWord);
			return fullWord;
		}
	}

	int i = (int)current[0] - (int)'a';

	if (root->children[i] != NULL && current[0] == root->children[i]->data) {
		fullWord[strlen(fullWord)] = current[0];
		nearestHelper1(root->children[i], newString(current), fullWord);
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
	} else {
		nearestHelper2(root, fullWord);
	} 

	return fullWord;		
}

char* nearestWord(node_t* root, char* c) {
	if (search(root, c)) {
		return c;
	}

	char* fullWord = (char*)malloc(sizeof(char)*32);
	return nearestHelper1(root, c, fullWord);
}

void printHelper(node_t* root, char* current) {
	int i;
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
	current[strlen(current)-1] = '\0';
		
}


void print(node_t* root) {
	char* current = malloc(sizeof(char)*32);
	printHelper(root, current);
	free(current);
}



int main() {

	node_t* root = makeNode(' ');

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

	printf("\nAfter deleting \"string\" and \"testing\": \n");

	delete(root,"string");
	delete(root,"testing");
	print(root);

	printf("\nAfter deleting \"banana\" and \"us\": \n");

	delete(root,"us");
	delete(root,"banana");
	print(root);



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

	freeTrie(root);

	return 0;
}

