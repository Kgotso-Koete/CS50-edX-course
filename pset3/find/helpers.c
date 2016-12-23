/*
 *
 * Title: helper.c
 *
 * Author: Kgotso Koete (kgkoete@gmail.com)
 *
 * Programme purpose: Implementation of search and sort functions included as headers to main (find)
 *
 * Date: 16 Sep 2016
 */
       
#include <cs50.h>

#include "helpers.h"

// function declarations 
bool lin_srch(int value, int values[], int n);
void bbl_sort(int values[], int n) ;
bool binary_search(int value, int values[], int n) ;

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (value < 0)
    {
        return false ;
    }
    else
    {
        return binary_search (value, values, n);
    }
}

/**
 * Sorts array of n values
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    bbl_sort(values, n);
    return;
}


// implementation oflinear search to be used in function call above
bool lin_srch(int value, int values[], int n)
{
    for (int i = 0 ; i < n ; i++)
    {
        if (values[i] == value)
        {
            return true;
        }
    }
    return false;
}


// implementation of binary search
bool binary_search(int value, int values[], int n)
{
    int ending = n - 1;
    int beggining = 0;

    while (ending >= beggining)
    {
        int middle = (beggining + ending) / 2;
        if (values[middle] == value)
            return true;
        else if (values[middle] > value)
            ending = middle - 1;
        else
            beggining = middle + 1;
    }

    return false;
}


// implementation of bubble sort used in function call above
void bbl_sort(int values[], int n)
{
    bool iter ;
    
    do
    {
        iter = false ;
        for (int i = 0; i < n - 1 ; i++)
        {
            if (values[i] > values[i + 1])
            {
                int temp_val = values[i] ;
                values[i] = values[i + 1] ;
                values[i + 1] = temp_val ;
                iter = true ;
            }
        }
    } 
    while (iter) ;
    return ;
}
