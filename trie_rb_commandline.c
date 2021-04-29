//The following code is based on Stephen Brennan's tutorial on how to write a shell in C.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

#define ALPHABET_SIZE 26

//Define node struct for trie.
typedef struct node {
	char data;
	struct node* children[ALPHABET_SIZE];
	char endOfWord;
} node_t;

//Declare root of trie as global.
node_t* root;

//Declare built-in functions.
int insert(char** args);
int search(char** args);
int delete(char** args);
int nearestWord(char** args);
int print();
int quit();

//Create array of strings for built-in functions.
char* builtin_str[] = {
	"insert",
	"search",
	"delete",
	"nearest",
	"print",
	"quit"
};

//Create array of pointers to built-in functions.
int (*builtin_func[])(char**) = {
	&insert,
	&search,
	&delete,
	&nearestWord,
	&print,
	&quit
};

//Return the number of built-in functions.
int num_builtins() {
	return sizeof(builtin_str) / sizeof(char*);
}

//Make trie node.
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

//Remove first letter of given string.
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

//Insert helper function.
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

//Insert given string into trie.
int insert(char** c) {
	insertHelper(root, c[1]);
	return 1;
}

//Helper function for search.
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

//Search function to determine whether word exists in trie.
int search(char** c) {
	if (searchHelper(root, c[1])) {
		printf("%s was found.\n",c[1]);
	} else {
		printf("%s was not found.\n",c[1]);
	}
	return 1;
}

//Helper function for delete.
void deleteHelper(node_t* root, char* c) {
	if(searchHelper(root, c) == false) {
		return;
	}

	if (c == '\0') {
		root->endOfWord = 'N';
		return;
	}
		
	int i = (int)c[0] - (int)'a';

	if(root->children[i]->data == c[0]) {		
		deleteHelper(root->children[i], newString(c));
		int j;
		for (i = 0; i < ALPHABET_SIZE; i++) {
			if (root->children[i] != NULL) {
				return;
			}
		}
		root->children[i] = NULL;
	} 
}

//Deletes the given word from the trie.
int delete(char** args) {
	deleteHelper(root, args[1]);
	return 1;
}


//Nearest helper function #2.
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

//Nearest helper function #1.
int nearestHelper1(node_t* root, char* current, char* fullWord) {
	if (current == '\0') {
		if(root->endOfWord == 'Y') {
			return 1;
		} else {
			nearestHelper2(root, fullWord);
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
	return 1;		
}


//Nearest word finds nearest full word to given prefix in trie.
int nearestWord(char** c) {
	char* fullWord = (char*)malloc(sizeof(char)*32);
	nearestHelper1(root, c[1], fullWord);
	printf("%s is the nearest word.\n",fullWord);
	free(fullWord);
	return 1;
}

//Helper function for print.
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

//Prints every word in the trie in alphabetical order.
int print(char** args) {
	char* current = malloc(sizeof(char)*32);
	printHelper(root, current);
	free(current);
	return 1;
}

//Quits the program.
int quit(char** args) {
	return 0;
}

//Keeps program running.
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

//Executes built in function requested.
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

//Reads line entered by user.
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

//Tokenizes line entered by user.
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

//Declares variables and accepts user input.
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
	
	free(root);
}

//Main function to run loop.
int main(int argc, char** argv) {
	trie_loop();
	return EXIT_SUCCESS;
}

