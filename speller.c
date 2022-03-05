/* scanner.c, Dennis Wu & Robin Moret, 5 March 2022
 *
 * This programm uses an implementation of a dictionary in the form of a trie
 * It takes input according to the rules descriebd in the assignment
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

// remove non-alphabetic characters and convert to lower case
void trimWord(char *word) {
  int k = 0;
  for (int i = 0; i < (int)strlen(word); i++) {
    if (isalpha(word[i])) {
      word[k] = tolower(word[i]);
      k++;
    }
  }
  word[k] = '\0';
}

int main(int argc, char *argv[]) {

  char word[LENGTH + 1] = "";

  // step 1: read in the dictionary
  Trie dictionary = newEmptyDict();
  while (scanf("%45s", word) && word[0] != '!') {
    trimWord(word);
    addWord(dictionary, word);
  }

  // step 2: read in text
  int counter = 0; // number of unknown words

  int index = 0;
  int c = EOF;
  while ((c = getchar()) && c != EOF) {
    if (isalpha(c)) {
      if (c >= 65 && c <= 90) {
        c += 32;
      }

      word[index] = c;
      index++;
    } else {
      word[index] = '\0';
      // printf("Word input: %s\n", word);
      if (index && !check(dictionary, word)) {
        counter++;
        printf("%s\n", word);
      }
      index = 0;
    }
  }

  // step 3: print number of unknown words
  printf("%d\n", counter);

  freeDict(dictionary);
  return 0;
}
