#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
	char data;
	bool endOfWord;
} node_t;

typedef struct trie{
	node_t* root;
	node_t* lchild;
	node_t* rchild;
} trie_t;

int main() {
	return 0;
}

