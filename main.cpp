//main.cpp
//Hossein Mohebbi
//
//multiplayer connect 4 game

//libraries
#include <iostream>
using namespace std;

struct PlayerInformation
{
    char Name[100];
    char piece;
};

//functions
bool isFour (char board[][10], PlayerInformation activePlayer); //function that gets values from array and struct and returns bool
int restart (char board[][10]); //function that gets values from array and returns bool
int columnChoice(char board[][10], PlayerInformation activePlayer); //function that gets values from array and struct and returns int
int maxFilled(char board[][10]);//function that gets values from array and returns int
void checkBelow (char board[][10], PlayerInformation activePlayer, int dropChoice); //function that gets values from array and struct and an int and returns nothing
void displayBoard (char board[][10]);//function that gets values from array and returns nothing
void PlayerWin ( PlayerInformation activePlayer );//function that gets from struct and returns nothing

int main()
{
    //variables
    PlayerInformation playerOne, playerTwo; //make two variables, playerOne and playerTwo from struct
    char board[9][10]; //create a 2D array
    int dropChoice = 0; //make a variable called dropChoice of type int
    int full = 0; //make a variable called full of type int
    int again = 1; //make a variable called again of type int
    bool win; //make a variable called win of type bool

    cout << "This program is a multiplayer connect 4 game!" << endl;//intro statement

    cout << "Player 1, please type in your name: "; //get name from playerOne
    cin  >> playerOne.Name;
    cout<<endl;
    playerOne.piece = 'X'; //set playerOne's piece to Y

    cout << "Player 2, please type in your name: "; //get name from playerOne
    cin  >> playerTwo.Name;
    cout<<endl;
    playerTwo.piece = 'O';//set playerTwo's piece to O

    displayBoard(board);//function that prints the base board
    cout<<endl;
    cout<<endl;

    do
    {
        cout<<endl;
        cout<<endl;
        //moves for playerOne
        dropChoice = columnChoice(board, playerOne);//function that gets column choice from playerOne
        checkBelow(board, playerOne, dropChoice);//checks pieces under choice to ensure its empty
        displayBoard(board);//reprints base board
        cout<<endl;
        cout<<endl;

        win = isFour(board, playerOne); //use function to check if connect 4 has been made
        if (win) //if so...
        {
            PlayerWin(playerOne);//playerOne has won
            again = restart(board);//ask to restart

            if (again != 1)//if no
            {
                break;//exit loop and game ends
            }
        }

        //moves for playerTwo
        dropChoice = columnChoice(board, playerTwo);//function that gets column choice from playerOne
        checkBelow(board, playerTwo, dropChoice);//checks pieces under choice to ensure its empty
        displayBoard(board);//print board
        win = isFour(board, playerTwo);//function to see if playerTwo won
        if (win)//if so...
        {
            PlayerWin(playerTwo);//playerTwo is winner
            again = restart(board);//ask to reset board

            if (again != 1)//if no
            {
                break;//exit loop and end game
            }
        }
        full = maxFilled(board);//check to see if board is filled
        if (full == 7)//if maximum is reached at 7
        {
            cout << "It's a draw!" << endl;
            again = restart(board);//ask to restart game

            if (again != 1)//if no
            {
                break;//exit loop and end game
            }
        }

    }
    while (again == 1);//condition for loop to keep looping, user must always want again

    return 0;
}

int columnChoice(char board[][10], PlayerInformation activePlayer)//function to get user's choice
{
    int dropChoice = 0;

    while (dropChoice < 1 || dropChoice > 7)//while loop to ensure column choice is between 1-7
    {
        cout << activePlayer.Name << ", it's your turn, ";
        cout << "Choose one of the labelled columns (1-7): ";
        cin  >> dropChoice;//get choice

        while (board[1][dropChoice] == 'X' || board[1][dropChoice] == 'O')//while loop to ensure that when column is filled user chooses other one
        {
            cout << "That column is full, please choose another column: ";
            cin  >> dropChoice;//get choice
        }
    }

    return dropChoice;
}

void checkBelow (char board[][10], PlayerInformation activePlayer, int dropChoice)//checking below piece
{
    int rowLength = 6;//make variable called rowLength, reps the 6 rows
    int turn = 0;

    do//create do loop that continues until turn is 1
    {
        if (board[rowLength][dropChoice] != 'X' && board[rowLength][dropChoice] != 'O')//condition for when row and drop choice are empty position
        {
            board[rowLength][dropChoice] = activePlayer.piece;//piece can take that position
            turn = 1;//set turn to 1 since possible position found and exits loop
        }
        else//otherwise
        {
            rowLength--;//take one away from rowLength
        }
    }
    while (turn != 1);
}

void displayBoard (char board[][10])//printing board
{
    int rows = 6; //variable for rows set to 6
    int columns = 7; //variable for columns set to 7

    cout << " 1234567 " <<endl;//identifying positions

    for(int i = 1; i <= rows; i++)//for loop counting the rows
    {
        cout << "|";//sidebar
        for(int j = 1; j <= columns; j++)//for loop counting the columns
        {
            if(board[i][j] != 'X' && board[i][j] != 'O')//condition for spots with no pieces
            {
                board[i][j] = '~';//print symbol representing empty space
            }

            cout << board[i][j];//print
        }
        cout << "|" << endl;//sidebar
    }
}

bool isFour (char board[][10], PlayerInformation activePlayer)//function to see if connect 4
{
    char XorO;
    bool win = false;

    XorO = activePlayer.piece;//the current players piece

    //nested loops
    for(int i = 8; i >= 1; i--)//count down from 8 to 1
    {
        for(int j = 9; j >= 1; j--)//count down from 9 to 1
        {

            //diagonal connect 4 of identical pieces
            if(board[i][j] == XorO && board[i-1][j-1] == XorO && board[i-2][j-2] == XorO && board[i-3][j-3] == XorO)
            {
                win = true;//yes to win
            }

            //second diagonal connect 4 of identical pieces
            if( board[i][j] == XorO && board[i][j-1] == XorO && board[i][j-2] == XorO && board[i][j-3] == XorO)
            {
                win = true;//yes to win
            }

            //vrtical connect 4 of identical pieces
            if( board[i][j] == XorO && board[i-1][j] == XorO && board[i-2][j] == XorO && board[i-3][j] == XorO)
            {
                win = true;//yes to win
            }

            //third diagonal connect 4 of identical pieces
            if( board[i][j] == XorO && board[i-1][j+1] == XorO && board[i-2][j+2] == XorO && board[i-3][j+3] == XorO)
            {
                win = true;//yes to win
            }

            //horizontal connect 4 of identical pieces
            if ( board[i][j] == XorO && board[i][j+1] == XorO && board[i][j+2] == XorO && board[i][j+3] == XorO)
            {
                win = true;//yes to win
            }
        }

    }

    return win;
}

int maxFilled(char board[][10])//function that determines if board is filled
{
    int full = 0;
    for (int i = 1; i <= 7; i++)//for loop from 1 - 7, reps columns
    {
        if (board[1][i] != '~')//if top row column is not empty
        {
            full++;//add to full by 1
        }
    }

    return full;
}

void PlayerWin (PlayerInformation activePlayer)//unction that gives winning announcement
{
    cout << activePlayer.Name << ", YOU JUST WON!" << endl;
}

int restart (char board[][10])//function for restarting game
{
    int restart;

    cout << "Would you like to play again? Enter 1 for yes and 2 for No: ";
    cin  >> restart;
    if (restart == 1)//if yes
    {
        //reprinting empty board
        for(int i = 1; i <= 6; i++)
        {
            for(int j = 1; j <= 7; j++)
            {
                board[i][j] = '~';
            }
        }
    }
    else//otherwise say game ended
    {
        cout << "Game Ended" << endl;
    }
    return restart;
}


