// declares a dictionary

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
#define LENGTH 45
#define ALPHABETLENGTH 26

typedef struct TrieNode* Trie;

struct TrieNode {
  bool endNode;
  char letter;
  Trie children [26];
};

Trie newEmptyDict();
Trie addWord(Trie root, char word[LENGTH + 1]);
bool check(Trie tr, const char *word);
void freeDict(Trie tr);

#endif // DICTIONARY_H
