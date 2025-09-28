#include<iostream>
using namespace std;

const int C = 5;
const int rows = 5;
void inputBoard(int game_arr[][C], int rows)
{
    cout << "Enter 1s and 0s into the board" << endl;
    for (int i = 0; i < rows; i++)
    { cout << "Enter row "<< i+1 << endl;
        for (int j = 0; j < C; j++)
        {
            cin >> game_arr[i][j];
        }
    }
    cout << endl;
    cout << "Printing Game Board" << endl;
    cout << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << "[";
        for (int j = 0; j < C; j++)
        {
            if (j > 0)
            {
                cout << ", ";
            }
            cout << game_arr[i][j];
        }
        cout << "]" << endl;
    }
    cout << endl;
}

bool findPossibility(int game_arr[][C], int rows)
{
    bool a = true;
    for (int i = 0; i < 1; i++)
    {
        for (int j = 1; j<C; j++)
        {
            if (game_arr[i][j] == 0)
            {
                continue;
            }
            else if (game_arr[i][j] >= game_arr[i][j-1])
            {
                game_arr[i][j] = game_arr[i][j-1];
            }
        }
    }
    for (int i = 1; i < rows; i++)
     {
         for (int j = 0; j<1; j++)
         {
             if (game_arr[i][j] == 0)
             {
                 continue;
             }
             else if (game_arr[i-1][j] < game_arr[i][j])
             {
                 game_arr[i][j] = game_arr[i-1][j];
             }
         }
     }
    for (int i = 1; i < rows; i++)
    {
        for (int j = 1; j < C; j++)
        {
            if(game_arr[i][j]==0)
            {
                continue;
            }
            if(game_arr[i][j-1]==0 && game_arr[i-1][j]==0)
            {
                game_arr[i][j] = 0;
            }
            else if(game_arr[i][j-1]==1 && game_arr[i-1][j]==1)
            {
                game_arr[i][j] = 1;
            }
            else if (game_arr[i-1][j] > game_arr[i][j-1])
            {
                game_arr[i][j] = 1;
            }
            else if(game_arr[i][j -1] > game_arr[i-1][j])
            {
                game_arr[i][j] = 1;
            }
        }
    }
    if (game_arr[4][4] == 1)
    {
        a = true;
    }
    else
    {
        a = false;
    }
    return a;
}
   


int main ()
{

    int gameBoard [rows][C];
    int i, j;
    for (i = 0; i<rows; i++)
    {
        for (j = 0; j<C; j++)
            gameBoard[i][j] = 0;
    }
    inputBoard(gameBoard, rows);
    if (findPossibility(gameBoard, rows) != 0)
    {
        cout << "Yes, there is possibility for the player to reach the end of the game." << endl;
    }
    else
    {
        cout << "No, there is no possibility for the player to reach the end of the game." << endl;
    }
    return 0;
}
