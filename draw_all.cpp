#include "draw_all.h"

Draw::Draw(int x, int y)
{
    this->xSize = x;
    this->ySize = y;

    raw_board = new SnakeMap(x/k,y/k);
    ptr = raw_board->getRawMap();

    scene = new QGraphicsScene();

    tex_head = new QPixmap("C:/Users/spaj/Desktop/snake40.png");
    tex_food = new QPixmap("C:/Users/spaj/Desktop/food40.png");
    tex_body = new QPixmap("C:/Users/spaj/Desktop/body40.png");
    tex_map = new QPixmap("C:/Users/spaj/Desktop/lawn.png");

    itemHead = new QGraphicsPixmapItem(*tex_head);
    itemFood = new QGraphicsPixmapItem(*tex_food);

    for(int i=0;i<raw_board->snake->getValue()-1;i++)
    {
        itemBody.push_back(new QGraphicsPixmapItem(*tex_body));
    }

    itemMap = new QGraphicsPixmapItem(*tex_map);

    scene->clear();
    scene->addItem(itemMap);

    for(int i=0;i<raw_board->snake->getValue()-1;i++)//add bodyblocks to scene
    {
        itemBody[i]->setPos(raw_board->snake->getX()*k,(raw_board->snake->getY()-(i+1))*k);
        scene->addItem(itemBody[i]);
    }

    itemHead->setTransformOriginPoint(QPoint(20,20));
    itemHead->setPos(raw_board->snake->getX()*k,raw_board->snake->getY()*k);
    scene->addItem(itemHead);

    itemFood->setPos(raw_board->food->getX()*k,raw_board->food->getY()*k);
    scene->addItem(itemFood);
}

Draw::~Draw()
{
    delete raw_board;
    delete itemHead;
    delete itemMap;
    delete itemFood;
    delete tex_head;
    delete tex_food;
    delete tex_map;
    delete scene;
}

void Draw::restart()
{
     raw_board->restartMap();

     gameTime = 0;
     eatenFood = 0;
     actual_food = 0;
     totalPoints = 0;
     speed = 1;

     for(int i=0;i<itemBody.size(); i++)//add bodyblocks to scene
     {
         itemBody[i]->hide();
     }

     int index = 0;
     for(int i=0;i<raw_board->snake->getValue()-1;i++)//add bodyblocks to scene
     {
         itemBody[i]->show();
         itemBody[i]->setPos(raw_board->snake->getX()*k,(raw_board->snake->getY()-(i+1))*k);
     }

     itemFood->setPos(raw_board->food->getX()*k,raw_board->food->getY()*k);
     this->rotateHead();
     itemHead->setPos(raw_board->snake->getX()*k,raw_board->snake->getY()*k);

}

void Draw::updateDir(int dir)
{
    raw_board->changeDirection(dir);
    this->rotateHead();
}

void Draw::updateMove()
{
    raw_board->moveSnake();
    raw_board->checkState();

    if(actual_food < raw_board->snake->getValue()-3) //add new body block to the map
    {
        qDebug() << "CYCE";
        actual_food=raw_board->snake->getValue()-3;
        eatenFood++;
    }


    if(val_food < raw_board->snake->getValue()) //add new body block to the map
    {
        val_food = raw_board->snake->getValue();
        itemBody.push_back(new QGraphicsPixmapItem(*tex_body));
        itemBody[itemBody.size()-1]->setPos(raw_board->snake->getX()*k,raw_board->snake->getY()*k);
        scene->addItem(itemBody[itemBody.size()-1]);
    }

    switch(raw_board->getGameState())
    {
        case true:
        {
            raw_board->updateMap();
            int index = 0;
            for(int y = 0; y < ySize/k; y++)
            {
                for(int x = 0; x < xSize/k; x++)
                {
                    if(ptr[y][x] > 0 && ptr[y][x] < raw_board->snake->getValue())
                    {
                        itemBody[index]->show();
                        itemBody[index]->setPos(x*k,y*k);
                        index++;
                    }
                }
            }
            itemFood->setPos(raw_board->food->getX()*k,raw_board->food->getY()*k);
            itemHead->setPos(raw_board->snake->getX()*k,raw_board->snake->getY()*k);
        }
        break;
        case false:
        {
            qDebug() << "KONIEC GRY";
        }
    }
}

bool Draw::getState()
{
    bool var = raw_board->getGameState();
    return var;
}

void Draw::rotateHead()
{
    switch(raw_board->snake->getDir())
    {
        case 0:{itemHead->setRotation(0);} break; //when it goes down the y value rises
        case 1:{itemHead->setRotation(90);} break;
        case 2:{itemHead->setRotation(180);} break;
        case 3:{itemHead->setRotation(270);} break;
        itemHead->setPos(raw_board->snake->getX()*k,raw_board->snake->getY()*k);
    }
}

void Draw::autoMove()
{
    this->updateMove();
}
