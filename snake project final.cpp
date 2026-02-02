#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

const int width = 40;
const int height = 20;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class SnakeGame
{
private:
    bool gameOver;
    Direction dir;

    int x, y;          
    int foodX, foodY;  
    int score;

    int tailX[100], tailY[100];
    int tailLength;

public:
    SnakeGame()
    {
        Setup();
    }

    void Setup()
    {
        gameOver = false;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        foodX = rand() % (width - 2) + 1;
        foodY = rand() % (height - 2) + 1;
        score = 0;
        tailLength = 0;
    }

    void Draw()
    {
        system("cls");

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0)
                    cout << "#";

                if (i == y && j == x)
                    cout << "O";        
                else if (i == foodY && j == foodX)
                    cout << "F";      
                else
                {
                    bool printTail = false;
                    for (int k = 0; k < tailLength; k++)
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << "o"; 
                            printTail = true;
                            break;
                        }
                    }
                    if (!printTail)
                        cout << " ";
                }

                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        cout << "Score: " << score << endl;
        cout << "Controls: W A S D | X = Exit" << endl;
    }

    void Input()
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            default:
                break;
            }
        }
    }

    void Logic()
    {

        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;

        for (int i = 1; i < tailLength; i++)
        {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
        
        switch (dir)
        {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
        }

        if (x < 0 || x >= width || y < 0 || y >= height)
            gameOver = true;

        for (int i = 0; i < tailLength; i++)
            if (tailX[i] == x && tailY[i] == y)
                gameOver = true;

        if (x == foodX && y == foodY)
        {
            score += 10;
            foodX = rand() % (width - 2) + 1;
            foodY = rand() % (height - 2) + 1;
            tailLength++;
        }
    }

    void Run()
    {
        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
            Sleep(100); 
        }

        system("cls");
        cout << "======================" << endl;
        cout << "     GAME OVER        " << endl;
        cout << "======================" << endl;
        cout << "Final Score: " << score << endl;
    }
};

int main()
{
    SnakeGame game;
    game.Run();
    return 0;
}
