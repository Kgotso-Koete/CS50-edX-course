/*
 *
 * Title: ceasar.c
 *
 * Author: Kgotso Koete (kgkoete@gmail.com)
 *
 * Programme purpose: Caesar’s cipher encryption
 *
 * Date: 07 Sep 2016
 */
 
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
                        

int main(int argc, string argv[])
{
    // asks the user for their key to be input in command line
    string key_input = argv[1] ;    
    bool key_val = false ;
    int valid_key = 0 ;
   
    do
    {
        if (argc != 2)
        {
            printf("Please provide a valid key \n") ;
            return 1 ;
        }
        else
        {
            // convert the user provided string to an integer
            valid_key = atoi (key_input) ;
            key_val = true ;
        }
    }    
    while (key_val == false) ;
  
  
    /*
    * encrypt the message based on formula
    */
    string message = GetString() ;
    int input_length = strlen(message) ;
    
    for(int i = 0 ; i < input_length ; i++)
    {
        // checks if string is alphabetic in order to process
        if (isalpha(message[i]))
        {
            // process lower case charachters
            if (islower(message[i]))
            {
                printf ("%c", ((((message[i] - 97) + valid_key) % 26) + 97)) ;
            }
            // process upper case charachters
            else 
            {
                printf ("%c", ((((message[i] - 65) + valid_key) % 26) + 65)) ;
            }
        }       

        // print all non-alphabetic charachters without encryption
        else 
        {
            printf ("%c", message[i]) ;
        }
    }
    printf("\n") ;
    
}