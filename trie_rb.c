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
		return "\0";
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
	if (c == "\0") {
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



void print(node_t* root) {
	int i=0;
	char* current;
	for (i = 0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != NULL) {
			if (root->children[i]->endOfWord == 'Y') {
				printf("%c\n",root->children[i]->data);
			//	return;
			} else {
				printf("%c", root->children[i]->data);
			}
			print(root->children[i]);
			
		}
	}


}

int main() {

	node_t* root = makeNode(' ');
	char* s = "test";
	char* s2 = "string";
	char* s3 = "testing";
	insert(root,s);
	insert(root,s2);
	insert(root,s3);
	print(root);
	printf("%c\n", root->children[19]->children[4]->children[18]->children[19]->children[8]->data);	
	return 0;
}

