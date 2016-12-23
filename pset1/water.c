/*
    Title: water.c
    
    Author: Kgotso Koete (kgkoete@gmail.com)
    
    Date: 3 Sep 2016
    
    Content: Submission of pset 1/water.c
*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("How long was your shower? \n");
    int mins = GetInt();
    
    // convert shower minutes to bottles of water consumed
    int bottles_cons = (12 * mins);
    
    printf("You used %i bottles in %i minutes\n", bottles_cons , mins);
}