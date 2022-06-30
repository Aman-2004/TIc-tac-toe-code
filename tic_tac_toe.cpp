#include <bits/stdc++.h>
using namespace std;

struct Board // FOR RUNNING GAME
{
    // creating a board of 3 x 3
    char board[3][3];
    Board()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = ' ';
            }
        }
    }

    // to get cell value what is present int that cell
    char gc(int x, int y)
    {
        return board[x][y];
    }

    // to set cell value to current player move
    void sc(int x, int y, char player)
    {
        board[x][y] = player;
    }

    // to check wether game has ended or not by (check end)
    char check_end()
    {
        // checking rows
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
            {
                return board[i][0];
            }
        }

        // checking columns
        for (int i = 0; i < 3; i++)
        {
            if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')
            {
                return board[0][i];
            }
        }

        // checking 1st diagonal
        if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ')
        {
            return board[0][0];
        }

        // checking 2nd diagonal
        if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ')
        {
            return board[0][2];
        }

        /* if none of the above works that means nobody has won the game yet
         so either there are moves left to play on board or draw*/
        int cnt = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                    cnt++;
            }
        }
        if (cnt == 0)
        {
            // if no empty space left then its a draw as nobody won from above statements
            return 'D';
        }
        else
        {
            // if spaces are left then we must continue the game
            return 'C';
        }
    }

    // now we need to print the board
    void print_board()
    {
        cout << "\n     0     1     2   \n";
        cout << "   _________________ \n";
        cout << "  |     |     |     |\n";
        cout << "0 |  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  |\n";
        cout << "  |_____|_____|_____|\n";
        cout << "  |     |     |     |\n";
        cout << "1 |  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  |\n";
        cout << "  |_____|_____|_____|\n";
        cout << "  |     |     |     |\n";
        cout << "2 |  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  |\n";
        cout << "  |_____|_____|_____|\n";
    }
};

// to find other player
inline char otherPlayer(char player)
{
    // otherPlayer('X') = 'O'; otherPlayer('O') = 'X';
    return player ^ 'X' ^ 'O';
}

// recurrtion states
char staterec(Board board, char player, bool printWinMove)
{
    // board.print_board();

    // checking if the board is already ended or not
    char is_alread_end = board.check_end();
    if (is_alread_end != 'C')
    {
        // if allend is equal to current player who play now then current player win else he lose
        if (is_alread_end == player)
        {
            return 'W';
        }
        else if (is_alread_end == 'D')
        {
            return 'D';
        }
        else
        {
            return 'L';
        }
    }
    else
    {
        // possible moves
        int pm = 0;
        // losing moves
        int lm = 0;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // choices
                /* if any place is empty we can play there hence that counts in possible moves
                checking if for that possible moves all states are losing states then current player
                will win by setting the cell to player and let the rec play further */

                if (board.gc(i, j) == ' ')
                {
                    // check
                    pm++;
                    board.sc(i, j, player);

                    // cout<<"Set "<<i<<","<<j<<" : "<<player<<endl;

                    char new_result = staterec(board, otherPlayer(player), 0);

                    // setting it back
                    board.sc(i, j, ' ');

                    // cout<<"Unset "<<i<<","<<j<<" : "<<player<<endl;

                    // this below win state is for other player for me it was a losing move
                    if (new_result == 'W')
                    {
                        lm++;
                    }

                    // if new result is l for other then we can win and will win hence immediately return w
                    else if (new_result == 'L')
                    {
                        // only printing 1st winning moves so introduced 3rd variable
                        if (printWinMove)
                            cout << i << " " << j << endl;
                        return 'W';
                    }
                }
            }
        }
        // checking if all possible moves are losing moves then we are going to lose else draw
        if (pm == lm)
        {
            return 'L';
        }
        else
        {
            // if u cannot win atleast draw it
            // this means if ever new result came out to be draw thats why lm<pm
            return 'D';
        }
    }
}

//CREATING INPUT STATE
Board createInput()
{
    string s;
    Board board;
    cout << "Enter Board Config :\n";
    for (int i = 0; i < 3; i++)
    {
        getline(cin, s);
        board.sc(i, 0, s[0]);
        board.sc(i, 1, s[1]);
        board.sc(i, 2, s[2]);
    }
    return board;
}

int main()
{
    Board temp = createInput();
    cout << "Input current move (X/O): ";
    char ch;
    cin >> ch;
    temp.print_board();
    cout << staterec(temp, ch, 1);
}
// test case replace - with space in test cases
// x--
// -0-
// ---
//from here x can draw atleast

// x--
// ---
// --0
//from here x will always win by placing at (0,2)








