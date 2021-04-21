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
		insert(root->children[i], newString(c));
	} else {
		root->children[i] = makeNode(c[0]);
		insert(root->children[i], newString(c));	
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


void delete(node_t* root, char* c) {
	if (c == '\0') {
		root->endOfWord = 'N';
		return;
	}
		
	int i = (int)c[0] - (int)'a';

	if(root->children[i]->data == c[0]) {		
		delete(root->children[i], newString(c));
		int j;
		for (i = 0; i < ALPHABET_SIZE; i++) {
			if (root->children[i] != NULL) {
				return;
			}
		}
		root->children[i] = NULL;
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
	} else {
		nearestHelper2(root, fullWord);
	} 	

	return fullWord;		
}

char* nearestWord(node_t* root, char* c) {
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
}



int main() {

	node_t* root = makeNode(' ');

	char* s = "test";
	char* s2 = "string";
	char* s3 = "testing";
	char* s4 = "you";
	char* s5 = "apple";
	char* s6 = "stringy";
	char* s7 = "application";
	char* s8 = "app";

	printf("Contents of trie:\n");
	insert(root,s);
	insert(root,s2);
	insert(root,s3);
	insert(root,s4);
	insert(root,s5);
	insert(root,s6);
	insert(root,s7);
	insert(root,s8);
	insert(root,"arcade");
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

	printf("\nAfter deleting \"string\" and \"testing\": \n");

	delete(root,"string");
	delete(root,"testing");
	print(root);

	printf("\nPrint nearest full word to \"str\":\n");
	printf("%s\n", nearestWord(root,"str"));	

	printf("\nPrint nearest full word to \"a\":\n");
	printf("%s\n", nearestWord(root,"a"));	

	printf("\nPrint nearest full word to \"you\":\n");
	printf("%s\n", nearestWord(root,"you"));	

	printf("\nPrint nearest full word to \"math\":\n");
	printf("%s\n", nearestWord(root,"math"));	



	return 0;
}

