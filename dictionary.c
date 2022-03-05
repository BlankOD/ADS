// implements a dictionary iin the form of a trie

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// allocates memory for a new empty Trie node
Trie newEmptyDict() {
  Trie node;
  node = malloc(sizeof(struct TrieNode));
  assert(node != NULL);
  for (int i = 0; i < ALPHABETLENGTH; i++) {
    node->children[i] = NULL;
  }
  node->endNode = false;
  return node;
}

// frees the Trie (dictionary)
void freeDict(Trie tr) {
  if (tr == NULL) {
    return;
  }
  for (int i = 0; i < ALPHABETLENGTH; i++) {
    freeDict(tr->children[i]);
  }
  free(tr);
}

// returns true if the word is in the trie, false if not
bool check(Trie root, const char *word) {
  Trie k = root;
  int index = 0;
  while (word[index] != '\0') {
    char x = word[index];
    index++;
    // k has no child containing x
    if (k->children[x - 'a'] == NULL) {
      return false;
    }
    k = k->children[x - 'a'];
  }

  // if trieDup is a leaf
  if (k->endNode == true) {
    return true;
  }
  return false;
}

// Adds a word to the Trie if it is not already in it
Trie addWord(Trie root, char word[LENGTH + 1]) {
  if (!check(root, word)) {
    Trie trieDup = root;
    for (int i = 0; word[i] != '\0'; i++) {
      int alphabetIndex = (int)word[i] - 'a';
      if (trieDup->children[alphabetIndex] == NULL) {
        trieDup->children[alphabetIndex] = newEmptyDict(word[i]);
      }
      trieDup = trieDup->children[alphabetIndex];
    }

    trieDup->endNode = true;

    return root;
  }
  return root;
}
