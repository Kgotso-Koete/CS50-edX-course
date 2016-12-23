/*
    Title: greedy.c
    
    Author: Kgotso Koete (kgkoete@gmail.com)
    
    Date: 4 Sep 2016
    
    Content: Submission of pset 1/greedy.c
*/

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    
    // asks the user for amount of change owed and stores the value
    float change_requested = 0 ;
    int change_owed = 0 ;
    // stores the number of coins counted and given to the user
    int coins_given = 0 ;
    
    do
    {
    printf("How much change in Dollars do we owe you? \n");
    change_requested = GetFloat();
    }
    while (change_requested <= 0);

    // Given amount is convert to cents
    change_owed = (int)round(change_requested*100);


    // Gives coins only if quarters can be given as change
    int quarter = 25;
    int quarters_given = 0;
    
    if (change_owed >= 0 )
    {
            quarters_given = change_owed / quarter;
            change_owed = change_owed % quarter;
            coins_given = coins_given + quarters_given;
    }
    
    // Gives coins only if dimes can be given as change
    int dime = 10;
    int dimes_given = 0;
    
    if (change_owed >= 0 )
    {
            dimes_given = change_owed / dime;
            change_owed = change_owed % dime;
            coins_given = coins_given + dimes_given;
    }
    
    // Gives coins only if dimes can be given as change
    int nicel = 5;
    int nicels_given = 0;
    
    if (change_owed >= 0 )
    {
            nicels_given = change_owed / nicel;
            change_owed = change_owed % nicel;
            coins_given = coins_given + nicels_given;
    }
    
    // Gives coins only if dimes can be given as change
    int penny = 1;
    int pennies_given = 0;
    
    if (change_owed >= 0 )
    {
            pennies_given = change_owed / penny;
            change_owed = change_owed - pennies_given;
            coins_given = coins_given + pennies_given;
    }
   
   
    //Required output:
    printf("You were given %i coins consisting of:\n", coins_given);
    printf("    %i quarters\n", quarters_given);
    printf("    %i dimes\n", dimes_given);
    printf("    %i nicels\n", nicels_given);
    printf("    %i pennies\n", pennies_given);
    printf("We owe you %i pennies\n", change_owed);
}

    
