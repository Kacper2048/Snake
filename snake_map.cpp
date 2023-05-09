#include "snake_map.h"

SnakeMap::SnakeMap(int x, int y)
{
    xSize = x;
    ySize = y;

    srand (time(NULL));

    food = new Food(x,y);
    snake = new Snake(x/2,y/2,3,0);

    game_state = true;
    array = new int*[y]{};
    for(int i=0;i<y;i++)
    {
        array[i] = new int[x]{};
    }
}

SnakeMap::~SnakeMap()
{
    for(int i=0;i<ySize;i++)
    {
        delete [] array[i];
    }
    delete [] array;
}

void SnakeMap::decreaseFieldValue() //decrease value of field about one
{
    for(int y=0;y<ySize;y++)
    {
        for(int x=0;x<ySize;x++)
        {
            if(array[y][x] > 0)
            {
                array[y][x]--;
            }
        }
    }
}

void SnakeMap::moveSnake()//make move every signal is generated
{
    snake->makeMove();
    if(snake->getX() >= xSize)
    {
        snake->setX(0);
    }
    if(snake->getX() < 0)
    {
        snake->setX(xSize-1);
    }
    if(snake->getY() < 0)
    {
        snake->setX(ySize-1);
    }
    if(snake->getY() >= ySize)
    {
        snake->setX(0);
    }
}

void SnakeMap::changeDirection(int dir) //change direction and make move without waiting for signal
{
    snake->setDir(dir);
    snake->makeMove();

    if(snake->getX() >= xSize)
    {
        snake->setX(0);
    }
    if(snake->getX() < 0)
    {
        snake->setX(xSize-1);
    }
    if(snake->getY() < 0)
    {
        snake->setY(ySize-1);
    }
    if(snake->getY() >= ySize)
    {
        snake->setY(0);
    }
}

void SnakeMap::checkState()
{
    if(snake->getX() == food->getX() && snake->getY() == food->getY())
    {
        snake->increaseByFood();
        do
        {
            food->randPosXY();
        }while(array[food->getY()][food->getX()] > 0);

    }
    else if(array[snake->getY()][snake->getX()] > 0)
    {
       game_state = false;
    }
}
