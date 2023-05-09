#include "snake_map.h"

SnakeMap::SnakeMap(int x, int y)
{

    xSize = x;
    ySize = y;

    srand (time(NULL));

    food = new Food(x,y);
    snake = new Snake(x/2,y/2,lenSnake,0);

    game_state = true;
    array = new int*[y]{};
    for(int i=0;i<y;i++)
    {
        array[i] = new int[x]{};
    }

     //places body on virtual map
    for(int i=1; i<snake->getValue();i++) //snake can't be placed near edges because then will be leak of memory
    {
        array[snake->getY()-i][snake->getX()] = snake->getValue()-i;
    }

    array[snake->getY()][snake->getX()] = snake->getValue(); //places head on virtual map
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
        snake->setY(ySize-1);
    }
    if(snake->getY() >= ySize)
    {
        snake->setY(0);
    }

}

void SnakeMap::changeDirection(int dir) //change direction and make move without waiting for signal
{
    snake->setDir(dir);
}

void SnakeMap::checkState()
{
    if(snake->getX() == food->getX() && snake->getY() == food->getY())
    {
        food->randPosXY();
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

void SnakeMap::updateMap()
{
    this->decreaseFieldValue();
    array[snake->getY()][snake->getX()] = snake->getValue();

}

void SnakeMap::restartMap()
{
    game_state = true;
    snake->restart();

    for(int y=0;y<ySize;y++)
    {
        for(int x=0;x<ySize;x++)
        {
            if(array[y][x] > 0)
            {
                array[y][x] = 0;
            }
        }
    }

    array[snake->getY()][snake->getX()] = snake->getValue();

}
