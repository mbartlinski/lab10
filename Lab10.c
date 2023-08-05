#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 26

// Trie structure
struct Trie
{	
    int count;
    struct Trie* children[ALPHABET];

};

struct Trie* init(){
    struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
    node->count = 0;
    for(int i = 0; i < ALPHABET; i++)
        node->children[i] = NULL;
        return node;
}
// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie* curr = pTrie;
    for(int i = 0; i < strlen(word); i++){
        int index = word[i] - 'a';
        if(curr->children[index] == NULL)
            curr->children[index] = init();
        curr = curr->children[index];
    }
    curr->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* curr = pTrie;
    for(int i = 0; i < strlen(word); i++){
        int index = word[i] - 'a';
        if(!curr->children[index])
        return 0;
        curr = curr->children[index];
    }
    return curr -> count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie){
        for(int i = 0; i < ALPHABET; i++){
            if (pTrie -> children[i])
            deallocateTrie(pTrie -> children[i]);
        }
        free(pTrie);
    }
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *root = init(); // Call init to create the root node
    return root;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file %s\n", filename);
        return 0;
    }

    int numWords = 0;
    char word[ALPHABET];

    int a;
    fscanf(file, "%d\n", &a);

    while (fgets(word, ALPHABET, file))
    {
        // Remove the trailing newline character
        int len = strlen(word);
        if (word[len - 2] == '\r')
            word[len - 2] = '\0';

        // Allocate memory for the word and copy it to pInWords array
        pInWords[numWords] = (char *)malloc(strlen(word) + 1);
        strcpy(pInWords[numWords], word);

        numWords++;
    }

    fclose(file);
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
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}