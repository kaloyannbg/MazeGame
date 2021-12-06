#include "includes.h"

char **startBoard(char **board, int rows, int cols)
{
    board = (char **)calloc(rows, sizeof(char *));

    int j = 0;
    for (int i = 0; i < rows; i++)
    {
        board[i] = (char *)calloc(cols, sizeof(char));

        for (j = 0; j < cols; j++)
        {
            board[i][j] = ' ';
        }
    }

    return board;
}

void printCoordinatesAndInformation(int currX, int currY)
{
    printf("  ************************************************ \n");
    printf("  *        Maze Game from Kaloyan Angelov        * \n");
    printf("  ************************************************ \n");
    printf("  * A -> left | D -> right | W -> up | S -> down * \n");
    printf("  *                 X: %d - y: %d                  * \n", currX, currY);
    printf("  ************************************************ \n\n");
}

void moveChip(char **board, int rows, int cols, int *currX, int *currY, char newPos)
{
    board[*currX][*currY] = 'o';
}

void changeBoard(char **board, int rows, int cols, int currX, int currY)
{
    int j = 0;
    for (int i = 0; i < rows; i++)
    {
        int randZeroToNine = rand() % 10;
        // printf("%d | ", randZeroToNine);
        for (j = 0; j < cols; j++)
        {
            if (i == currX && j == currY)
            {
                continue;
            }
            board[i][j] = ' ';
            if (j % 2 == 1)
            {
                board[i][j] = '|';
            }
            if (i == rand() % 10 && j % 2 == 1)
            {
                board[i][j] = ' ';
            }

        }
    }
}

void printBoard(char **board, int rows, int cols)
{
    printf("       ");
    for (int i = 1; i <= cols; i++)
    {
        printf("%c   ", 64 + i);
    }
    printf("\n");
    for (int i = 0; i < rows; i++)
    {
        printf("  %2d | ", i);
        for (int j = 0; j < cols; j++)
        {
            printf("%c | ", board[i][j]);
        }
        printf("\n");
    }
}

int isWin(char **board, int rows, int cols, int *x, int *y, int newPos)
{
    if (newPos == '0')
    {
        return -2;
    }
    else if (newPos == 'd' || newPos == 'D')
    {

        if (board[(*x)][(*y) + 1] == '|')
        {
            // printf("\n -- You hit the wall and you lose! -- \n");
            return -1;
        }

        if ((*y) >= (cols - 1))
        {
            return 1;
        }
        else
        {
            (*y)++;
        }
    }
    else if (newPos == 's' || newPos == 'S')
    {
        if ((*x) >= (rows - 1))
        {
            printf("\n --  You reached max lower board -- \n");
            printf(" -- ");
            system("pause");
            return 0;
            return 0;
        }
        else
        {
            (*x)++;
        }
    }
    else if (newPos == 'a' || newPos == 'A')
    {
        if ((*y) <= 0)
        {
            //  printf("\n --  You reached left board -- \n");
            return 0;
        }
        else
        {
            (*y)--;
        }
    }
    else if (newPos == 'w' || newPos == 'W')
    {
        if ((*x) <= 0)
        {
            printf("\n -- You reached max upper board -- \n");
            printf(" -- ");
            system("pause");
            return 0;
        }
        else
        {
            (*x)--;
        }
    }
}

void clearScreen()
{
    system("clear");
}

int main()
{
    srand(time(NULL));
    int rows = 10;
    int cols = 10;

    clearScreen();
    char **board = startBoard(board, rows, cols);
    printBoard(board, rows, cols);
    int x = 0, y = 0;
    int newPos = 0;
    int isWinning = isWin(board, rows, cols, &x, &y, newPos);

    while (isWinning != -2 || isWinning != -1 || isWinning != 1)
    {
        clearScreen();
        printCoordinatesAndInformation(x, y);
        moveChip(board, rows, cols, &x, &y, newPos);
        changeBoard(board, rows, cols, x, y);
        printBoard(board, rows, cols);
        printf("\n -- Enter new position: ");
        newPos = getch();
        fflush(stdin);
        int isWinning = isWin(board, rows, cols, &x, &y, newPos);
        if (isWinning == -2)
        {
            printf(" -- Bye! -- ");
            break;
        }
        else if (isWinning == -1)
        {
            printf(" -- You Lose! -- ");
            break;
        }
        else if (isWinning == 1)
        {
            printf(" -- You win! -- ");
            break;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        free(board[i]);
    }

    free(board);

    return 0;
}