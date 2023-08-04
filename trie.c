#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie
{
    struct Trie *children[26];
    int isWord;
    int count;
};

struct Trie* createTrie() {
    struct Trie* newTrie = malloc(sizeof(struct Trie));
    for (int i = 0; i < 26; i++)
        newTrie -> children[i] = NULL;
    newTrie -> count = 0;
    return newTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL)
        return;

    struct Trie* current = pTrie;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current -> children[index] == NULL)
            current -> children[index] = createTrie();
        current = current -> children[index];
    }
    current -> count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL)
        return 0;

    struct Trie* current = pTrie;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current -> children[index] == NULL)
            return 0; // word not found
        current = current -> children[index];
    }
    return current -> count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
        return NULL;

    for (int i = 0; i < 26; i++)
        if (pTrie -> children[i] != NULL)
            pTrie -> children[i] = deallocateTrie(pTrie -> children[i]);

    free(pTrie);
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return -1;

    int numWords;
    fscanf(file, "%d", &numWords);

    // Read each word from the file and store it in the array
    for (int i = 0; i < numWords; i++) {
        pInWords[i] = malloc(sizeof(char));
        fscanf(file, "%s", pInWords[i]);
    }

    fclose(file);

    // Return the number of words in the dictionary
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i = 0; i < 5; i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}