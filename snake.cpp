#include "snake.h"

Snake::Snake(int x, int y, int val, int dir)
{
    this->pos_x = x;
    this->pos_y = y;
    this->value = val;
    this->dir = dir;
}

void Snake::makeMove()
{
    switch(dir)
    {
        case 0:{pos_y++;} break; //when it goes down the y value rises
        case 1:{pos_x--;} break;
        case 2:{pos_y--;} break;
        case 3:{pos_x++;} break;
    }
}

void Snake::increaseByFood()
{
    value++;
}
