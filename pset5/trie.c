#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define ALPHABET_SIZE (26) // Alphabet index number
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') // Converts word current character into index
 
// trie node struct
struct new_node
{
    struct new_node *children[ALPHABET_SIZE];
    bool is_word; // is_word is true if the node represents end of a word
};
 
// Returns new trie node (initialized to NULL)
struct new_node *getNode(void)
{
    struct new_node *parent_node = NULL; // initialise new node to NULL
    parent_node = (struct new_node *)malloc(sizeof(struct new_node)); // allocate memory
 
    if (parent_node) // if the parent is not NULL (filled with a char) then
    {
        parent_node->is_word = false ; // initialise the parent word status to false
 
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            parent_node->children[i] = NULL; // make sure all children are NULL
        }
    }
    return parent_node;
}
 
// If not present, inserts word into trie
void insert(struct new_node *root, const char *word)
{
    int word_length = strlen(word); // calculate the length of the word
    int index;
 
    struct new_node *parent_tracker = root; // create a new parent
 
    for (int letter = 0; letter < word_length; letter ++) 
    { 
        index = CHAR_TO_INDEX(word[letter]); // convert letter to alphabet index
        
        if (!parent_tracker->children[index]) // if child letter is empty, create node
        {
            parent_tracker->children[index] = getNode();
        }
 
        parent_tracker = parent_tracker->children[index];
    }
    parent_tracker->is_word = true;  // mark last node as last leaf
}
 
// Returns true if word is present in trie
bool search(struct new_node *root, const char *word)
{
    int letter;
    int length = strlen(word);
    int index;
    
    struct new_node *parent_tracker = root;
 
    for (letter = 0; letter < length; letter++)
    {
        index = CHAR_TO_INDEX(word[letter]);
 
        if (!parent_tracker->children[index])
        {
            return false;
        }
 
        parent_tracker = parent_tracker->children[index];
    }
 
    return (parent_tracker != NULL && parent_tracker->is_word);
}
 
// Driver
int main()
{
    // Input words (use only 'a' through 'z' and lower case)
    char dictionary[][8] = {"the", "a", "there", "answer", "any",
                     "by", "bye", "their"};
 
    char output[][32] = {"Not present in trie", "Present in trie"};
 
    // MAIN INSTRUCTIONS TO INITIALISE THE DICTIONARY
    struct new_node *root = getNode();
 
    for (int words = 0; words < ARRAY_SIZE(dictionary); words++) // Construct trie
    {
        insert(root, dictionary[words]);
    }
 
    // Search for different words
    printf("%s --- %s\n", "the", output[search(root, "the")] );
    printf("%s --- %s\n", "these", output[search(root, "these")] );
    printf("%s --- %s\n", "their", output[search(root, "their")] );
    printf("%s --- %s\n", "thaw", output[search(root, "thaw")] );
    printf("\n") ;
    return 0;
}