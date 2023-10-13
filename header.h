#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define alp 26

typedef struct trieNode{
    char u;
    int value; 
    struct trieNode *children[alp];
    bool isEndWord;
} trieNode;

typedef struct trie{
    trieNode *root;
} trie;

typedef struct keyValueNode {
    char key[100];
    int value;
} keyValueNode;

// основные функции

trie *trie_create();
void trie_insert(trie *tr, char *key, int value);
trieNode *trie_lookup(trie *tr, char *key);
trie *trie_delete(trie *tr, char *key);
void trie_print(trie *tr, int level);

// побочные функции

trieNode *trie_node_create(char u);
int char_to_index(char u);
trieNode *get_child(trieNode *node, char u);
void set_child(trieNode *node, char u, trieNode *child);
bool trie_delete_helper(trieNode *node, char *key, int depth);
void trie_print_helper(trieNode *node, char *buffer, int level);

// связанный список

void trie_map_helper(trieNode *node, char *buffer, keyValueNode *output, int level, int *count);
keyValueNode *trie_get_ordered_map(trie *tr, int *count);