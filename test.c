#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int num; // number of occurrences of the word
    struct Trie *children[26]; // children nodes, one for each letter
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = malloc(sizeof(struct Trie));

    //pTrie->children = (struct Trie *) malloc(sizeof(struct Trie*) * 26);
    pTrie->num = 0;
    for (int i = 0; i < 26; i++) {
        pTrie->children[i] = NULL;
    }
    return pTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int i;
    struct Trie *pNode = pTrie;
    for (i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

      //seg faults right here in vs code
        if (pNode->children[index] == NULL) {
          pNode->children[index] = createTrie();
          // pNode->children[index] = malloc(sizeof(struct Trie));
        }
        pNode->num++;
        pNode = pNode->children[index];
    }
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int i;
    struct Trie *pNode = pTrie;
    for (i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (pNode->children[index] == NULL) {
            return 0;
        } else if (pNode->children[index]->num == 0) {
            return 0;
        }
        pNode = pNode->children[index];
    }
    return pNode->num;
}


// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    int numWords = 0;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return 0;
    }
    char word[256];
    int a;
    fscanf(fp, "%d\n", &a);
    while (fgets(word, sizeof(word), fp)) {
        word[strlen(word) - 1] = '\0'; 
        pInWords[numWords++] = strdup(word);
    }
    fclose(fp);
    return numWords;
}


int main(void)
{
    char *inWords[256];

    //read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    
    }
    
    struct Trie *pTrie = createTrie();
    
    for (int i = 0; i < numWords; i++) {
        
        insert(pTrie, inWords[i]);
    }
    
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}
