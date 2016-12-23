/*
 *
 * Title: fifteen.c
 *
 * Author: Kgotso Koete (kgkoete@gmail.com)
 *
 * Programme purpose: Game of fifteen implementation
 *
 * Date: 16 Sep 2016
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int dimension ;

int x;
int y;


// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    dimension = atoi(argv[1]);
    if (dimension < DIM_MIN || dimension > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }
    // initialixing x and y here so 0 does not reset every time you call move function
    else
    {
        x = (dimension - 1);
        y = (dimension - 1);
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int row = 0; row < dimension; row++)
        {
            for (int column = 0; column < dimension; column++)
            {
                fprintf(file, "%i", board[row][column]);
                if (column < dimension - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    bool even = false;
    int size = dimension*dimension ;
    if (size % 2 == 0)
    {
        even = true ;
    }
    // row count
    for (int row = 0; row < dimension; row++)
    {   // column count
        for (int column = 0; column < dimension; column++)
        {
            board[row][column] = size - 1 ;
            size -- ;
        }       
    }
    
    // '_' or ASCII 95 will represent blank tile
    board[dimension-1][dimension-1] = 0 ;
    
    if (even)
    {    
        board[dimension-1][dimension-2] = 2 ;
        board[dimension-1][dimension-3] = 1 ;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int row = 0; row < dimension; row++)
    {
        for (int column = 0; column < dimension; column++)
        {
            if (board[row][column] == 0)
            {
                printf(" _ ") ;
            }
            
            else if (board[row][column] > 9)
            {
                printf("%i ", board[row][column]) ;
            }
            else 
            {
                printf("%2i ",board[row][column]) ;
            }
        } 
    printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO 
    // search board for user tile
    // iterate through rows to find tile
    for (int row = 0; row < dimension; row++) 
    {
        // iterate through columns to find tile
        for (int column = 0; column < dimension; column++) 
        {
            // if user entered tile that exists on the board
            if(tile == board[row][column]) 
            {
                // initialize variable for 0 
                int blankspace = 0;       
 
                // test if tile is adjacent to blankspace
                if (((x == (row - 1)) && (column == y)) ||  ((x == (row + 1)) && (column == y)) ||
                ((row == x) && (y == (column - 1))) || ((row == x) && (y == (column + 1))))
                {
                    // printf("before:  tile %d, blankspace %d\n", tile, blankspace)
 
                    // swap tile with blankspace if tile is adjacent to blankspace
                    board[x][y] = tile;
                    board[row][column] = blankspace;
                    x=row;
                    y=column;
 
                    // printf("The position of the tile is board[%d][%d] = %2d.  Tile is %d\n", i, j, board[i][j], tile);
                    // printf("Blankspace position is: board[%d][%d] = %d\n", x, y, blankspace);
 
                    return true;
                }   
            } 
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // check if board is sorted
    int n = 1;
    
    // check to see if last tile is blank and return false if it is not
    if (board[dimension - 1][dimension - 1] != 0)
    {
        return false ;
    }
    
    // set up for loops to check if numbers are in ascending order beginning with 1
    for (int row = 0; row < dimension; row++)
    {
        for (int column = 0; column < dimension; column++)
        {
            // check last grid position first, if blank, return true
            if (row == dimension - 1 && column == dimension - 1)
                return true ;
                
            // check the numbers on the rest of the tiles
            if (n != board[row][column])
                return false ;
            n++ ;                        
        }
    }
    return false ;
}