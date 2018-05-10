/*THE MINESWEEPER GAME*/

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "time.h"
#define MAXSIZE 25
#define MAXMINES 99

int SIZE ; // SIZE length of the board
int MINES ; // number of mines on the board
int SCORE ; // Score (No. of non Mine Squares the user found)


// A Function that checks whether a square (row, col) is a valid or not
bool squareIsValid(int row, int col)
{
    // Returns true if row number and column number is in range
    return (row >= 0) && (row < SIZE) && (col >= 0) && (col < SIZE);
}

// A Function that checks whether a square (row, col) has a mine or not.
bool squareIsMine (int row, int col, char board[][MAXSIZE])
{
    if (board[row][col] == '*')
        return (true);
    else
        return (false);
}
 
// A Function to get the user's move
void  enterLocation(int *x, int *y)
{
    // Take the input move
    printf("Enter your move (row, column) -> ");
    scanf("%d %d", x, y);
    return;
}
// A Function to print the current Field
void printField(char displayedField[][MAXSIZE])
{
    int i, j;
 
    printf ("    ");
 
    for (i=0; i<SIZE; i++)
        printf ("%d ", i);
 
    printf ("\n\n");
 
    for (i=0; i<SIZE; i++)
    {
        if(i<10)
        printf ("%d   ", i);
        else
        printf ("%d  ", i);
 
        for (j=0; j<SIZE; j++)
        {
            if(j<9)
            printf ("%c ", displayedField[i][j]);
            else
            printf ("%c  ", displayedField[i][j]);
        }
        printf ("\n");
    }
    return;
}

// A Function to count the number of mines in the adjacent squares
int countAdjacentMines(int row, int col, int mines[][2], 
                      char realField[][MAXSIZE])
{
 
    int i;
    int count = 0;
 
    /*
        Count all the mines in the 8 adjacent Squares

                  N.W N  N.E
                  |  |  |
                W-Square-E
                 |  |  |
                S.W S S.E
 
        Square-->Current Square (row, col)
        N -->  North            (row-1, col)
        S -->  South            (row+1, col)
        E -->  East             (row, col+1)
        W -->  West             (row, col-1)
        N.E--> North-East   (row-1, col+1)
        N.W--> North-West   (row-1, col-1)
        S.E--> South-East   (row+1, col+1)
        S.W--> South-West   (row+1, col-1)
    */
 
    //             1st Square (North)                         
 
        // Only process this cell if this is a valid one
        if (squareIsValid (row-1, col) == true)
        {
               if (squareIsMine (row-1, col, realField) == true)
               count++;
        }
 
    //             2nd Square (South)                         
 
        // check if this this Square is a valid one
        if (squareIsValid (row+1, col) == true)
        {
               if (squareIsMine (row+1, col, realField) == true)
               count++;
        }
 
    //             3rd Square (East)                         
 
        // check if this this Square is a valid one
        if (squareIsValid (row, col+1) == true)
        {
            if (squareIsMine (row, col+1, realField) == true)
               count++;
        }
 
    //             4th Square (West)                         
 
        // check if this this Square is a valid one
        if (squareIsValid (row, col-1) == true)
        {
               if (squareIsMine (row, col-1, realField) == true)
               count++;
        }
 
    //             5th Square (North-East)                         
 
        // check if this this Square is a valid one
        if (squareIsValid (row-1, col+1) == true)
        {
            if (squareIsMine (row-1, col+1, realField) == true)
               count++;
        }
 
     //             6th Square (North-West)                         
 
        // check if this this Square is a valid one
        if (squareIsValid (row-1, col-1) == true)
        {
             if (squareIsMine (row-1, col-1, realField) == true)
               count++;
        }
 
     //             7th Square (South-East)                         
 
        // check if this this Square is a valid one
        if (squareIsValid (row+1, col+1) == true)
        {
               if (squareIsMine (row+1, col+1, realField) == true)
               count++;
        }
 
    //             8th Square (South-West)                         
 
        // check if this this Square is a valid one
        if (squareIsValid (row+1, col-1) == true)
        {
            if (squareIsMine (row+1, col-1, realField) == true)
               count++;
        }
 
    return (count);
}
int CalculateScore(char displayedField[][MAXSIZE])
{
    int i,j;
    int openedSquares=0;
    for (i=0; i<SIZE; i++)
    {
        for (j=0; j<SIZE; j++)
        {
            if(displayedField[i][j] != '-')
            {
                openedSquares++;
                
            }
        }
    }
    SCORE=openedSquares-MINES;

}
// A Recursive Fucntion to play the Minesweeper Game
bool playMinesweeperUntil(char displayedField[][MAXSIZE], char realField[][MAXSIZE],
            int mines[][2], int row, int col, int *movesLeft)
{
 
    // Base Case of Recursion
    if (displayedField[row][col] != '-')
	{
	    return (false); 
 	}
    int i, j;
 
    // You opened a mine! You are going to lose
    if (realField[row][col] == '*')
    {
        displayedField[row][col]='*';
 
        for (i=0; i<MINES; i++)
            displayedField[mines[i][0]][mines[i][1]]='*';
 
        printField (displayedField);
        CalculateScore(displayedField);
        printf ("\nYou stepped on a MINE!\n");
		printf("You opened %d Square Fields Without stepping on a mine!",SCORE);
        return (true) ; //=gameOver
    }
 
    else
     {
        // Calculate the number of adjacent mines and put it on the displayedField
        int count = countAdjacentMines(row, col, mines, realField);
        (*movesLeft)--;
        
        displayedField[row][col] = count + '0';
 
        if (!count)
        {
            /*
            Recurrance for all 8 adjacent Square
 
                 N.W N  N.E
                  |  |  |
                W-Square-E
                 |  |  |
                S.W S S.E
 
            Square-->Current Square (row, col)
            N -->  North            (row-1, col)
            S -->  South            (row+1, col)
            E -->  East             (row, col+1)
            W -->  West             (row, col-1)
            N.E--> North-East   (row-1, col+1)
            N.W--> North-West   (row-1, col-1)
            S.E--> South-East   (row+1, col+1)
            S.W--> South-West   (row+1, col-1)
            */
 
            //             1st Square (North)                         
            // Only process this cell if this is a valid one
            if (squareIsValid (row-1, col) == true)
            {
                   if (squareIsMine (row-1, col, realField) == false)
                   {
                        
                    playMinesweeperUntil(displayedField, realField, mines, row-1, col, movesLeft);
                   }
            }
 
            //             2nd Square (South)                         
 
            // Only process this cell if this is a valid one
            if (squareIsValid (row+1, col) == true)
            {
                   if (squareIsMine (row+1, col, realField) == false)
                   {
                        
                    playMinesweeperUntil(displayedField, realField, mines, row+1, col, movesLeft);
                   }
            }
 
            //             3rd Square (East)                         
 
            // Only process this cell if this is a valid one
            if (squareIsValid (row, col+1) == true)
            {
                if (squareIsMine (row, col+1, realField) == false)
                {
                     
                    playMinesweeperUntil(displayedField, realField, mines, row, col+1, movesLeft);
                }
                    
                }
 
            //             4th Square (West)                         
 
            // Only process this cell if this is a valid one
            if (squareIsValid (row, col-1) == true)
            {
                   if (squareIsMine (row, col-1, realField) == false)
                    {
                         
                        playMinesweeperUntil(displayedField, realField, mines, row, col-1, movesLeft);
                               
                    }
                        
                    }
 
            //             5th Square (North-East)                         
 
            // Only process this cell if this is a valid one
            if (squareIsValid (row-1, col+1) == true)
            {
                if (squareIsMine (row-1, col+1, realField) == false)
                {
                     
                    playMinesweeperUntil(displayedField, realField, mines, row-1, col+1, movesLeft);
                
                }
            }
 
             //             6th Square (North-West)                         
 
            // Only process this cell if this is a valid one
            if (squareIsValid (row-1, col-1) == true)
            {
                 if (squareIsMine (row-1, col-1, realField) == false)
                {
                     
                    playMinesweeperUntil(displayedField, realField, mines, row-1, col-1, movesLeft);
                    
                }
            } 
             //             7th Square (South-East)                         
 
            // Only process this cell if this is a valid one
            if (squareIsValid (row+1, col+1) == true)
            {
                 if (squareIsMine (row+1, col+1, realField) == false)
                {
                     
                    playMinesweeperUntil(displayedField, realField, mines, row+1, col+1, movesLeft);
                
                }
            }
 
            //             8th Square (South-West)                         
 
            // Only process this cell if this is a valid one
            if (squareIsValid (row+1, col-1) == true)
            {
                if (squareIsMine (row+1, col-1, realField) == false)
                {
                     
                    playMinesweeperUntil(displayedField, realField, mines, row+1, col-1, movesLeft);
                    
                }
            }
        }
 
        return (false);
    }
}
// A Function to place the mines randomly on the board
void placeMines(int mines[][2], char realField[][MAXSIZE])
{
    bool mark[MAXSIZE*MAXSIZE];
 
    memset (mark, false, sizeof (mark));
 
    // Continue until all random mines have been created.
    for (int i=0; i<MINES; )
     {
        int random = rand() % (SIZE*SIZE);
        int x = random / SIZE;
        int y = random % SIZE;
 
        // Add the mine if no mine is placed at this position
        if (mark[random] == false)
        {
            // Row Index of the Mine. Stores random x position within SIZE
            mines[i][0]= x;			
            // Column Index of the Mine.  Stores random y position within SIZE
            mines[i][1] = y;
 
            // Place the mine
            realField[mines[i][0]][mines[i][1]] = '*';
            mark[random] = true;
            i++;
        }
    }
 
    return;
}
// A Function to Create a Minesfield
void initialise(char realField[][MAXSIZE], char displayedField[][MAXSIZE])
{
    // Initiate the random number generator so that the same no. doesn't occur
    srand(time (NULL));
 
    // Assign all the Square as mine-free
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            displayedField[i][j] = realField[i][j] = '-';
        }
    }
 
    return;
}
// A Function to play Minesweeper game
void playMinesweeper ()
{
    // Initially the game is not over
    bool gameOver = false;
 
    // Actual Field and Field Displayed for Minesweeping
    char realField[MAXSIZE][MAXSIZE], displayedField[MAXSIZE][MAXSIZE];
    //squares left for Minesweeping
    int movesLeft = SIZE * SIZE - MINES, x, y;
    int mines[MAXMINES][2]; // stores (x,y) coordinates of all mines.
 
      initialise (realField, displayedField);
 
    // Place the Mines randomly
    placeMines (mines, realField);

    // Game is not over until a mine is opened 
 
    int currentMove= 0;
    while (gameOver == false)
     {
        printf ("Current Status of the Field: \n");
        printField (displayedField);
        
        //Get the location of the move
         enterLocation (&x, &y);
        currentMove ++;
 
        gameOver = playMinesweeperUntil (displayedField, realField, mines, x, y, &movesLeft);

        if ((gameOver == false) && (movesLeft == 0))
         {
            CalculateScore(displayedField);
            printf ("\nYou won !\n");
			printf("You opened all %d Square Fields without stepping on a mine!\n",SCORE);
            gameOver = true;
         }
    }
    return;
}
// A Function to choose the difficulty level of the game
void chooseDifficultyLevel ()
{
    char choice;
    printf(" ****   Enter Game Level: Easy? Intermediate? Hard? or Custom?(E/I/H/C) ****\n");
    scanf("%c",&choice);

     switch(choice)
    {
        case 'E':
            SIZE=9;
	    	MINES = 10;
            break;
            
        case 'I':
            SIZE=16;
           	MINES = 40;
			break;
			
        case 'H':
           SIZE=24;
    		MINES = 99;
            break;
            
        case 'C':
            printf("Enter Size of the Field:\n ");
            scanf("%d",&SIZE);
            printf("Enter no. of Mines in the Field:\n");
            scanf("%d",&MINES);
            break;
            
        default:
            printf("Without playing you stepped on a MINE!");
        exit(0);
    }

 
    return;
}


//time_t time(time_t *timer); is a Function included in time.h 
//which returns Gives the current time, in seconds,
// elapsed since 00:00:00 GMT, January 1, 1970,
// and stores that value in the location pointed to by timer.
main()
{
    time_t start, end;
    start = time(NULL);
  
    printf(" ****          Welcome To Minesweeper Game.                ****\n");
    printf(" ****          Watch it you might step into one.           ****\n");
    chooseDifficultyLevel ();
    playMinesweeper ();

    end = time(NULL)-start;
    printf("\nYou cleared %d Square field in %ld seconds.\n",SCORE, end);
 }