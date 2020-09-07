#include <iostream>
#include <inttypes.h>
#include <cstring>



/*
100
1-10
P1 P2  
1  3 

P2 x 
P1 (MAXOBJ + 1) - x

Pile1 pile2
N1     N2  ....
*/


#define N 10
#define PILEA 1U
#define PILEB 2U
#define BOTH 3U

#define FP 0x00U  //uint8_t 
#define SP 0xFFU

uint8_t dp[N + 1][N + 1];
uint8_t firstPlayersMoves[N];
uint8_t secondPlayerFirstMove;
uint8_t move;
uint8_t firstPlayerMoveCounter;

void winReceipeCreator()
{
    memset(dp, 0, sizeof(uint8_t) * (N + 1) * (N + 1));
    for (int pa = 0; pa < N + 1; pa += 2)
    {
        for (int pb = 1; pb < N + 1; pb += 2)
        {
            dp[pa][pb] = PILEA;
        }
    }
    for (int pa = 1; pa < N + 1; pa += 2)
    {
        for (int pb = 0; pb < N + 1; pb++)
        {
            if (pb % 2 == 0)
            {
                dp[pa][pb] = PILEB;
            }
            else
            {
                dp[pa][pb] = BOTH;
            }
        }
    }
}

void displayMatrix()
{
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            switch (dp[i][j])
            {
            case PILEA:
                std::cout << "A ";
                break;
            case PILEB:
                std::cout << "B ";
                break;
            case BOTH:
                std::cout << "C ";
                break;
            default:
                std::cout << "* ";
                break;
            }
        }
        std::cout << "\n";
    }
}

void retrieveWinStrategy()
{
    move = FP;
    firstPlayerMoveCounter = 0;
    int i = N;
    int j = N;
    while (i>=0 || j>=0)
    {
        if (move == FP)
        {
            switch (firstPlayersMoves[firstPlayerMoveCounter])
            {
            case PILEA:
                j--;
                break;
            case PILEB:
                i--;
                break;
            case BOTH:
                j--;
                i--;
                break;
            }
            firstPlayerMoveCounter++;
        }
        else
        {
            switch (dp[i][j])
            {
            case PILEA:
                std::cout << "Remove from Pile A\n";
                j--;
                break;
            case PILEB:
                std::cout << "Remove from Pile B\n";
                i--;
                break;
            case BOTH:
                std::cout << "Remove from Pile Both\n";
                j--;
                i--;
                break;
            }
        }
        move = 0xFF ^ move;
    }

    if (move == FP)
    {
        std::cout << "Second Player Wins Always\n";
    }
    else
    {
        std::cout << "Second Player Wins Always\n";
    }
}

int main()
{
    winReceipeCreator();
    displayMatrix();
    uint8_t temp[] = {BOTH, BOTH,BOTH,BOTH,BOTH};
    memcpy(firstPlayersMoves, temp, 13);
    retrieveWinStrategy();
}
