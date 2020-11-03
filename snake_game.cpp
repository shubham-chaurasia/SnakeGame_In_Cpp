#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// Variables .
bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruitx, fruity, score;
int tailx[100], taily[100];
int nTail;
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;

// this is setup of game 
void Setup()

{

    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}

// this is drawing of game
void Draw()
{
    system("cls");

    // this loop is for upper part of the frame of game .
    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "#";
            }
            if (i == y && j == x)
            {
                cout << "O";
            }
            else if (i == fruity && j == fruitx)
            {
                cout << "*";
            }

            else
            {
                bool print = false;

                // this loop is for the tail of the snake 
                for (int k = 0; k < nTail; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
            }

            if (j == width - 1)
            {
                cout << "#";
            }
        }
        cout << endl;
    }

    // this loop is for lower part of the fame of the game .
    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;
    cout << "score : " << score << endl;
}

// this function is for taking values from keyborads 
void Input()
{

    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 'z':
            dir = DOWN;
            break;
        case 'x':
            gameover = true;
            break;
        default:
            break;
        }
    }
}

// this is the logic of game 
void Logic()
{
    int prevX = tailx[0];
    int prevY = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = prev2x;
        prevY = prev2y;
    }

    switch (dir)
    {
    case UP:
        y--;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // if (x > width || x < 0 || y > height || y < -1)
    // {
    //     gameover = true;
    // }

    // the upper comment is  for the snake to die from wall .
   
    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;
    for (int i = 0; i < nTail; i++)
    {
        if (tailx[i] == x && taily[i] == y)
        {
            gameover = true;
        }
    }

    if (x == fruitx && y == fruity)
    {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        nTail++;
    }
}

// here all functions are called.
int main()
{

    Setup();
    while (!gameover)
    {
        Draw();
        Input();
        Logic();
        // Sleed(10);speed can be controled by this  
    }

    return 0;
}