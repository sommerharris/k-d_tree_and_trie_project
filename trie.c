#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

#define ALPHABET_SIZE 26
#define ANY_WORD_SIZE 46

typedef struct TrieNode {
    char character; // stroed for printing
    int isWord; // 0:false; 1:true;
    struct TrieNode* children[ALPHABET_SIZE]; // record only lower case characters
}t_node;

// make a new TrieNode with charater
t_node* makeTrieNode(char word) {
    t_node* newTrieNode = (t_node*)malloc(sizeof(t_node));
    if(!newTrieNode) {
        return NULL;
    }

    newTrieNode -> isWord = 0;
    newTrieNode -> character = word;

    int i;
    while(i < ALPHABET_SIZE) {
        newTrieNode -> children[i] = NULL;
        i++;
    }
    return newTrieNode;
}

void insert(t_node* root, char* word) {
    t_node* cur = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int idx = (int) word[i] - 'a';
        if (cur->children[idx] == NULL) {
            cur->children[idx] = makeTrieNode(word[i]);
        }
        cur = cur ->children[idx]; 
    }
    cur->isWord = 1;
}

// return the last TrieNode that contains the word
t_node* search(t_node* root, char* word) {
    t_node* cur = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int idx = (int) word[i] - 'a';
        if (cur -> children[idx] == NULL) {
            printf("The word is \"%s\" not in the Trie!\n", word);
            return NULL;
        }
        cur = cur->children[idx];
    }
    if (cur != NULL && cur->isWord == 1) {
        printf("Found the word \"%s\".\n", word);
        return cur; // find the word;
    }
    printf("Word \"%s\" is not in the Trie!\n", word);
    return NULL;
}

// search prefix and return the Trie Node with the last character in the prefix
t_node* searchPrefix(t_node* root, char* prefix) {
    t_node* cur = root;
    for (int i = 0; prefix[i] != '\0'; i++) {
        int idx = (int) prefix[i] - 'a';
        if (cur -> children[idx] == NULL) {
            printf("No word with prefix %s is in the Trie!\n", prefix);
            return NULL;
        }
        cur = cur->children[idx];
    }
    return cur;
}

// Delete the alst Trie Node in the word physically if it doesn'thave any children
// Mark the word in the Trie as not a word.
int delete(t_node* root, char* word) {
    if (!root) {
        return 0;
    }
    if(!word || word[0] == '\0') {
        return 0;
    }
    //search if the word is in the trie and get the last Trie Node that contains the word
    t_node* last = search(root, word);
    if(last != NULL) {
        last->isWord = 0; //mark it as not a word
        printf("Successfully delete the word \"%s\" in the Trie.\n", word);
        return 1;
    }
    
    return 0; // Trie does not have the word, cannot delete the word
}

void printAString(char* anyWord) {
    printf("%s\n",anyWord);
}

void printAllHelper(t_node* root, char* anyWord, int len) {
    if (!root) {
        return;
    }

    if (root -> character != ' ') { // not the empty root node
        anyWord[len] = root -> character;
        len++;
        if (root ->isWord) {
            anyWord[len] = '\0';
            printAString(anyWord);
        }
    }else if (root -> isWord) { //for printing when prefix itself is a word
        anyWord[len] = '\0';
        printAString(anyWord);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root -> children[i] != NULL) {
            printAllHelper(root->children[i], anyWord, len);
        }
    }
}

void printAll(t_node* root) {
    char* anyWord = (char*)malloc(sizeof(char)* ANY_WORD_SIZE);
    printAllHelper(root, anyWord, 0);
}

void findNearestFullWord(t_node* root, char* prefix){
    t_node* prefixNode = searchPrefix(root, prefix);
    char* builderWithPrefix = (char*)malloc(sizeof(char)* ANY_WORD_SIZE);
    strcpy(builderWithPrefix, prefix); // copy the prefix to the builder
    printAllHelper(prefixNode, builderWithPrefix, strlen(prefix)-1);
}

int main(){
    t_node* trie = makeTrieNode(' ');

    char* t1 = "apple";
    char* t2 = "application";
    char* t3 = "apocalypse";
    char* t4 = "app";
    char* t5 = "pop";
    char* t6 = "pope";
    char* t7 = "poplin";
    char* t8 = "popliteal";
    char* t9 = "zebra";
    char* t10 = "zest";
    char* t11 = "test";
    char* t12 = "string";
    char* t13 = "you";
    char* t14 = "stringy";
    char* t15 = "arcade";
    char* t16 = "use";

    char* prefix1 = "appl";
    char* prefix2 = "app";
    char* prefix3 = "ze";
    char* prefix4 = "pop";


    insert(trie, t1);
    insert(trie, t2);
    insert(trie, t3);
    insert(trie, t4);
    insert(trie, t5);
    insert(trie, t6);
    insert(trie, t7);
    insert(trie, t8);
    insert(trie, t9);
    insert(trie, t10);
    insert(trie, t11);
    insert(trie, t12);
    insert(trie, t13);
    insert(trie, t14);
    insert(trie, t15);
    insert(trie, t16);

    printf("The words in trie are:\n");
    printAll(trie);
    printf("================================================\n");

    printf("Nearst full words from \"%s\" are: \n", prefix1);
    findNearestFullWord(trie, prefix1);
    printf("================================================\n");
    printf("Nearst full words from \"%s\" are: \n", prefix2);
    findNearestFullWord(trie, prefix2);
    printf("================================================\n");
    printf("Nearst full words from \"%s\" are: \n", prefix3);
    findNearestFullWord(trie, prefix3);
    printf("================================================\n");
    printf("Nearst full words from \"%s\" are: \n", prefix4);
    findNearestFullWord(trie, prefix4);
    printf("================================================\n");

    delete(trie, t1);
    printf("\n");
    printf("After deleting \"%s\", search it again:\n", t1);
    search(trie, t1);
    printf("================================================\n");\

    delete(trie, t2);
    printf("\n");
    printf("After deleting \"%s\", search it again:\n", t2);
    search(trie, t2);
    printf("================================================\n");
    
    printf("The words in trie are:\n");
    printAll(trie);
    printf("================================================\n");



    
    return 1;
}
