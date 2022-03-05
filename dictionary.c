// implements a dictionary

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "dictionary.h"

Trie newEmptyDict(){
    Trie node;
    node = malloc(sizeof(struct TrieNode));
    assert(node != NULL);
    for(int i = 0; i < ALPHABETLENGTH; i++){
      node->children[i] = NULL;
    }
    node->endNode = false;
    return node;
}

void freeDict(Trie tr){
  if(tr == NULL){
    return;
  }
  for(int i = 0; i < ALPHABETLENGTH; i++){
    freeDict(tr->children[i]);
  }
  free(tr);
}

bool check(Trie root, const char* word){
  Trie k = root;
  int index = 0;
  while (word[index] != '\0'){
    char x = word[index];
    index++;
    //k has no child containing x
    if(k->children[x - 'a'] == NULL){
      return false;
    }
    k = k->children[x - 'a'];
  }

  //if trieDup is a leaf
  if (k->endNode == true){
      return true;
  }
  return false;
}

Trie addWord (Trie root, char word[LENGTH + 1]){
  if(!check(root, word)){
    Trie trieDup = root;
    for(int i = 0; word[i] != '\0'; i++){
      int alphabetIndex = (int) word[i] - 'a';
      if (trieDup->children[alphabetIndex] == NULL){
        trieDup->children[alphabetIndex] = newEmptyDict(word[i]);
      }
      trieDup = trieDup->children[alphabetIndex];

    }
    trieDup->endNode = true;

    return root;
  }
  return root;
}

// dict *newEmptyDict() {
//   dict *d = malloc(sizeof(dict));
//   if (d == NULL) {
//     return NULL;
//   }
//   d->numWords = 0;
//   d->maxWords = 1;
//   d->words = malloc(sizeof(char*) * d->maxWords);
//   return d;
// }

// // add word to the dictionary if it is is not already known
// void addWord(char word[LENGTH + 1], dict *d) {
//   if (!check(word, d)) {
//     // if we need more space before adding the word, double the size
//     if (d->numWords == d->maxWords) {
//       d->words = realloc(d->words,(sizeof(char*)) * (d->maxWords * 2));
//       if (d->words == NULL) {
//         printf("Out of memory.\n");
//         exit(-1);
//       }
//       d->maxWords = d->maxWords * 2;
//     }
//     // now we actually add the word
//     d->words[d->numWords] = malloc(sizeof(char) * (LENGTH + 1));
//     strcpy(d->words[d->numWords],word);
//     d->numWords++;
//   }
// }

// // check whether word is in dictionary
// bool check(const char *word, dict *d) {
//   for (int i = 0; i < d->numWords; i++) {
//     if (strcmp(d->words[i],word) == 0) {
//       return true;
//     }
//   }
//   return false;
// }

// void freeDict(dict *d) {
//   for (int i = 0; i < d->numWords; i++) {
//     free(d->words[i]);
//   }
//   free(d->words);
//   free(d);
// }
