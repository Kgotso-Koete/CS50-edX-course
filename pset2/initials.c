/*
 *
 * Title: intitials.c
 *
 * Author: Kgotso Koete (kgkoete@gmail.com)
 *
 * Programme purpose: Prints the initials of a user's name
 *
 * Date: 07 Sep 2016
 */
 
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // asks the user for their name and stores the value
    string user_name = GetString() ;
   
    // prints capitalized version of the name
    {
        printf("%c", toupper(user_name[0])) ;
    }
    
        // loop through all the charachters of the name
        for ( int i = 0, n = strlen(user_name); i < n; i++)
        {
            // checks for space to print following charachter
            if ( user_name[i] == ' ') 
            {
                // prints the charachter after the space
                printf("%c", toupper(user_name[i + 1])) ; 
            }
        }
        printf("\n") ;
}