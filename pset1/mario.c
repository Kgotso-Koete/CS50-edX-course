/*
    Title: mario.c
    
    Author: Kgotso Koete (kgkoete@gmail.com)
    
    Date: 3 Sep 2016
    
    Content: Submission of pset 1/mario.c
*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask the user for the height of the pyramid
    int height = 0 ;
    
    do
    {
        printf("Please enter a height for the pyramid: \n");
        height = GetInt();
    }  
    
    while (height < 0 || height > 23);
    
/* Outer for loop repeats the printing of rows while
the inner for loops print the space and hash symbols based
based on height and row count
*/
    
    //prints the pyramid based on user input
    for (int row_count = 0; row_count < height ; row_count++)
    {
        // prints spaces. 7 spaces in row 1
        for (int spaces = 0; spaces < (height - row_count -1) ; spaces++)
        {
        printf(" ");
        }
        //prints the hash symbols. 2 hash symbols in row 2
        for (int hash = 0 ; hash < (row_count + 2) ; hash++)
        {
        printf("#");
        }
        //prints the new lines
        {
        printf("\n");
        }
    }
}