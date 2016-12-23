/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */
#include <ctype.h> // to be used for the tolower function
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define ALPHABET_SIZE (26) // Alphabet index numbers
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') // Converts word current character into index


// Node Definition
typedef struct node
{
    bool is_word ; // status that signifies if a chain of nodes constitutes a word 
    struct node* children[27] ; // initialises 26 nodes for alphabets, 1 for apostrophe
}
new_node ;

// initialise the root node to be used in loading dict and checking words
new_node* root ;

// initialise size of the trie
unsigned int node_count = 0 ;

/**
 * Returns index of letter within trie array
 */
int get_index(const char letter)
{
    if (letter == '\'') 
    {
        return 26 ; // return 26 if last letter is a backslash    
    }
    else 
    {
        return tolower(letter) - 'a' ; // converts any letter to index between 0 and 25
    }
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // first start at the top of the tree by setting tracker to root
    new_node* tracker = root ;
    
    // loop through each letter in the input word and traverse the tree
    for (int letter = 0; word[letter] != '\0'; letter ++) 
    {
        // get the index of the word
        int index = get_index(word[letter]) ;
        
        // if the index slot is emphy (NULL), then word is not in dictionary
        if (tracker->children[index] == NULL) 
        {
            // if NULL word is mispelled
            return false;
        }
        
        // if not NULL, move to next letter
        tracker = tracker->children[index];
    }
    // At end of input word, check if is_word is true
    return tracker->is_word ;

}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // allocate memory to the root
    root = malloc(sizeof(new_node)) ;
    
    // initialise the total number of nodes to zero
    node_count = 0 ;
    
    // opening and reading the dictionary
    FILE* opened_file = fopen(dictionary, "r") ;
    if (opened_file == NULL)
    {
        return false;
    }
    
    // set the tracker to root
    new_node* tracker = root;
    
    // loop through each charachter in the dictionary
    for (int letter = fgetc(opened_file); letter != EOF; letter = fgetc(opened_file))
    {
        // mark the string of charachters as a word at start of new line
        if (letter == '\n') 
        {
            // change status of string to word
            tracker->is_word = true;
            
            // increase count of nodes
            node_count ++ ;
            
            // tracker is reset to root to traverse the trie
            tracker = root;
        }
        else 
        {
            // get letter index
            int index = get_index(letter);
        
            // if the children of the tracker is empty for that letter, create a ne node
            if (tracker->children[index] == NULL) 
            {
                // Create new node
                tracker->children[index] = (new_node*)malloc(sizeof(new_node));
            }
            // move the tracker to the next node
            tracker = tracker->children[index];
        }
    }
    
    // close the dictionary
    fclose(opened_file);
    
    // return true to indicate that the dictionary has successfully loaded
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return node_count;
}

/**
 * Check node children to see if they can be freed
 */
bool free_nodes(new_node* tracker)
{
    // iterate through each letter
    for (int letter = 0; letter < 27; letter ++)
    {
        // recursively make each child a tracker and free its children
        if (tracker->children[letter] != NULL) 
        {
            free_nodes(tracker->children[letter]) ;
        }
    }
    
    // finally, free the tracker once all children are free
    free(tracker);
    
    // return true to confirm that all nodes have been freed from memory
    return true;
}


/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
   // free the root and all children nodes
    return free_nodes(root);
}
