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

/*
typedef struct trie{
	node_t* root;
	node_t* children[ALPHABET_SIZE];
} trie_t;
*/

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
/*
trie_t* makeTrie() {
	int i;
	
	trie_t* t = (trie_t*)malloc(sizeof(trie_t));

	t->root = NULL;
	for (i = 0; i < ALPHABET_SIZE; i++) {
		t->children[i] = NULL;
	} 
	
	return t;
}
*/
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
	printf("%d\n", i);

	if(root->children[i] != NULL) {		
		insert(root->children[i], newString(c));
	} else {
		root->children[i] = makeNode(c[0]);
		insert(root->children[i], newString(c));	
	}	

}



void print(node_t* root) {
	int i=0;
	for (i = 0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != NULL) {
			if (root->children[i]->endOfWord == 'Y') {
				printf("%c\n",root->children[i]->data);
				return;
			} else {
				printf("%c", root->children[i]->data);
				print(root->children[i]);
			}
		}
	}


}

int main() {

	node_t* root = makeNode(' ');
	char* s = "test";
	insert(root,s);
	print(root);
	
	return 0;
}

