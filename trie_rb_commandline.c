#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>


#define ALPHABET_SIZE 26

typedef struct node {
	char data;
	struct node* children[ALPHABET_SIZE];
	char endOfWord;
} node_t;

node_t* root;

int insert(char** args);
int search(char** args);
int delete(char** args);
int nearestWord(char** args);
int print(char** args);
int quit(char** args);

char* builtin_str[] = {
	"insert",
	"search",
	"remove",
	"nearest word",
	"print",
	"quit"
};

int (*builtin_func[])(char**) = {
	&insert,
	&search,
	&delete,
	&nearestWord,
	&print,
	&quit
};

int num_builtins() {
	return sizeof(builtin_str) / sizeof(char*);
}

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

	char* new = malloc(sizeof(char*)*32);
	int i = 1;
	int j = 0;

	while (c[i]) {
		new[j] = c[i];
		j++;
		i++;
	}
	
	return new;
}

void insertHelper(node_t* root, char* c) {
	if (c == '\0') {
		root->endOfWord = 'Y';
		return;
	}
		
	int i = (int)c[0] - (int)'a';
	if(root->children[i] != NULL) {		
		insertHelper(root->children[i], newString(c));
	} else {
		root->children[i] = makeNode(c[0]);
		insertHelper(root->children[i], newString(c));	
	}	

}
int insert(char** c) {
	insertHelper(root, c[1]);
	return 1;
}


bool searchHelper(node_t* root, char* c) {
	if (c == '\0') {
		if(root->endOfWord == 'Y') {
			return true;
		}
		return false;
	} 
	
	int i = (int)c[0] - (int)'a';

	if(root->children[i] != NULL && root->children[i]->data == c[0]) {		
		return searchHelper(root->children[i], newString(c));
	}
	return false;
}

int search(char** c) {
	if (searchHelper(root, c[1])) {
		printf("%s was found.\n",c[1]);
	} else {
		printf("%s was not found.\n",c[1]);
	}
	return 1;
}

int delete(node_t* root, char** c) {
	if (&c == '\0') {
		root->endOfWord = 'N';
		return 1;
	}
		
	int i = (int)&c[0] - (int)'a';

	if(root->children[i]->data == &c[0]) {		
		delete(root->children[i], newString(c));
		int j;
		for (i = 0; i < ALPHABET_SIZE; i++) {
			if (root->children[i] != NULL) {
				return 1;
			}
		}
		root->children[i] = NULL;
	} 
	return 1;
}




int nearestHelper2(node_t* root, char* fullWord) {
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
			return 1;
		}
	}
	return 1;
}

int nearestHelper1(node_t* root, char* current, char* fullWord) {
	if (current == '\0') {
		if(root->endOfWord == 'Y') {
			printf("%s is the nearest word.\n", fullWord);
			return 1;
		} else {
			nearestHelper2(root, fullWord);
			printf("%s is the nearest word.\n", fullWord);
			return 1;
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
	printf("%s is the nearest word.\n", fullWord);
	return 1;		
}

int nearestWord(char** c) {
/*	if (search(root, c) ) {

		return c;
	}*/

	char* fullWord = (char*)malloc(sizeof(char)*32);
	return nearestHelper1(root, &c, fullWord);
//	return 1;
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


int print() {
	char* current = malloc(sizeof(char)*32);
	printHelper(root, current);
	return 1;
}

int quit(char** args) {
	return 0;
}

int launch(char** args) {
	pid_t pid, wpid;
	int status;
	
	pid = fork();
	if(pid == 0) {
		if(execvp(args[0],args) == -1) {
			perror("launch");
		}
		exit(EXIT_FAILURE); 
	} else if (pid < 0) {
		perror("launch");
	} else {
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

int execute(char** args) {
	int i;
	if(args[0] == NULL) {
		return 1;
	}
	for (i = 0; i < num_builtins(); i++) {
		if(strcmp(args[0],builtin_str[i]) == 0) {
			return(*builtin_func[i])(args);
		}
	}
	return launch(args);
}

#define RL_BUFSIZE 1024
char* read_line(void) {
	char* line = NULL;
	ssize_t bufsize = 0;

	if(getline(&line, &bufsize, stdin) == -1) {
		if(feof(stdin)) {
			exit(EXIT_SUCCESS);
		} else {
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}

	return line;
}

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"
char** split_line(char* line) {
	int bufsize = TOK_BUFSIZE;
	int position = 0;
	char** tokens = malloc(sizeof(char*) * bufsize);
	char* token;

	if(!tokens) {
		return NULL;
	}

	token = strtok(line, TOK_DELIM);
	while(token != NULL) {
		tokens[position] = token;
		position++;
	
		if (position >= bufsize) {
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if(!tokens){
				return NULL;
			}
		}
	token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

void trie_loop(void) {
	char* line;
	char** args;
	int status;
	root = makeNode(' ');
		
	do{
		printf("> ");
		line = read_line();
		args = split_line(line);
		status = execute(args);
		free(line);
		free(args);
	} while(status);

//	free(line);
//	free(args);
}

int main(int argc, char** argv) {

	trie_loop();



/*
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
*/
	return EXIT_SUCCESS;
}

