#include "header.h"

trieNode *trie_node_create(char u) {
    trieNode *node = (trieNode *)malloc(sizeof(trieNode));

    node->u = u;
    node->value = -1;
    node->isEndWord = false;

    for (int i = 0; i < alp; i++) {
        node->children[i] = NULL;
    }

    return node;
}

trie *trie_create() {
    trie *tr = (trie *)malloc(sizeof(trie));

    tr->root = trie_node_create('\0');

    return tr;
}

int char_to_index(char u) { 
    return u - 'a';
}

trieNode *get_child(trieNode *node, char u) {
    return node->children[char_to_index(u)];
}

void set_child(trieNode *node, char u, trieNode *child) {
    node->children[char_to_index(u)] = child;
}

void trie_insert(trie *tr, char *key, int value)
{
    trieNode *cur_node = tr->root;
    for (int i = 0; i < strlen(key); i++) {
        trieNode *child = get_child(cur_node, key[i]);
        if (child == NULL) {
            child = trie_node_create(key[i]);
            set_child(cur_node, key[i], child);
        }
        cur_node = child;
    }
    cur_node->value = value;
    cur_node->isEndWord = true;
}

trieNode *trie_lookup(trie *tr, char *key) {
    trieNode *cur_node = tr->root;

    for (int i = 0; i < strlen(key); i++) {
        trieNode *child = get_child(cur_node, key[i]);
        if (child == NULL)
        {
            return NULL;
        }
        cur_node = child;
    }

    if (cur_node->value == -1) {
        return NULL;
    }

    return cur_node;
}

bool trie_delete_helper(trieNode *node, char *key, int depth) {
    if (depth == strlen(key)) {
        if (!node->isEndWord) {
            return false;
        }

        node->isEndWord = false;

        for (int i = 0; i < alp; i++) {
            if (node->children[i]) {
                return false;
            }
        }

        return true;
    }

    int idx = char_to_index(key[depth]);

    if (!node->children[idx]) {
        return false;
    }

    bool should_delete = trie_delete_helper(node->children[idx], key, depth + 1);

    if (should_delete) {
        free(node->children[idx]);
        node->children[idx] = NULL;

        for (int i = 0; i < alp; i++) {
            if (node->children[i]) {
                return false;
            }
        }

        if (!node->isEndWord) {
            return true;
        }
    }

    return false;
}

trie *trie_delete(trie *tr, char *key) {
    trie_delete_helper(tr->root, key, 0);
    return tr;
}

void trie_print_helper(trieNode *node, char *buffer, int level) {
    if (node->isEndWord) {
        buffer[level] = '\0';
        printf("%s -> %d\n", buffer, node->value);
    }

    for (int i = 0; i < alp; i++) {
        if (node->children[i]) {
            buffer[level] = node->children[i]->u;
            trie_print_helper(node->children[i], buffer, level + 1);
        }
    }
}

void trie_print(trie *tr, int level) {
    char buffer[100];
    trie_print_helper(tr->root, buffer, level);
}

void trie_map_helper(trieNode *node, char *buffer, keyValueNode *output, int level, int *count) {
    if (node->isEndWord) {
        buffer[level] = '\0';
        strcpy(output[*count].key, buffer);
        output[*count].value = node->value;
        *count += 1;
    }

    for (int i = 0; i < alp; i++) {
        if (node->children[i]) {
            buffer[level] = node->children[i]->u;
            trie_map_helper(node->children[i], buffer, output, level + 1, count);
        }
    }
}

keyValueNode *trie_get_ordered_map(trie *tr, int *count) {
    keyValueNode *output = (keyValueNode *)malloc(sizeof(keyValueNode) * 100);

    char buffer[100];
    *count = 0;

    trie_map_helper(tr->root, buffer, output, 0, count);

    return output;
}