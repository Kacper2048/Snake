#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "snake_map.h"
#include <vector>

class Draw
{
    private:
        int k = 20;
        QGraphicsPixmapItem *itemHead = nullptr;
        QGraphicsPixmapItem *itemMap = nullptr;
        std::vector<QGraphicsPixmapItem *> itemBody;
        QGraphicsPixmapItem *itemFood = nullptr;
        QPixmap * tex_head = nullptr;
        QPixmap * tex_food = nullptr;
        QPixmap * tex_map = nullptr;
        QPixmap * tex_body = nullptr;
        SnakeMap * raw_board = nullptr; //raw board contains everything what we need
                                        //The main purpoes of Draw class is just to put on the screen what is going on inside
        QGraphicsScene *scene = nullptr;
        int **ptr;
        int xSize;
        int ySize;
        int val_food = 3;
    public:

        Draw(int x, int y)
        {
            this->xSize = x;
            this->ySize = y;

            raw_board = new SnakeMap(x/k,y/k);
            ptr = raw_board->getRawMap();

            scene = new QGraphicsScene();

            tex_head = new QPixmap("C:/Users/spaj/Desktop/snake.png");
            tex_food = new QPixmap("C:/Users/spaj/Desktop/food.png");
            tex_body = new QPixmap("C:/Users/spaj/Desktop/pix.png");
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

            itemHead->setPos(raw_board->snake->getX()*k,raw_board->snake->getY()*k);
            scene->addItem(itemHead);

            ptr[raw_board->snake->getY()][raw_board->snake->getX()] = raw_board->snake->getValue();

            itemBody[0]->setPos(raw_board->snake->getX()*k,(raw_board->snake->getY()-1)*k);
            itemBody[1]->setPos(raw_board->snake->getX()*k,(raw_board->snake->getY()-1)*k);
            scene->addItem(itemBody[0]);
            scene->addItem(itemBody[1]);

            itemFood->setPos(raw_board->food->getX()*k,raw_board->food->getY()*k);
            scene->addItem(itemFood);
            qDebug() << "Return 5 key released!";
        }

        ~Draw()
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

        QGraphicsScene      *   getScene()    {return scene;}
        QGraphicsPixmapItem *   getItemMap()  {return itemMap;}
        QGraphicsPixmapItem *   getItemHead() {return itemHead;}
        QGraphicsPixmapItem *   getItemFood() {return itemFood;}

        //void clearMap(){scene->clear();}

        void redraw()
        {
        }

        void updateDir(int dir)
        {
            raw_board->changeDirection(dir);
            raw_board->checkState();

            if(val_food < raw_board->snake->getValue())
            {
                val_food = raw_board->snake->getValue();
                itemBody.push_back(new QGraphicsPixmapItem(*tex_body));
                itemBody[itemBody.size()-1]->setPos(raw_board->snake->getX()*k,raw_board->snake->getY()*k);
                scene->addItem(itemBody[itemBody.size()-1]);
                itemFood->setPos(raw_board->food->getX()*k,raw_board->food->getY()*k);
            }

            if(raw_board->getGameState())
            {
                raw_board->decreaseFieldValue();
                ptr[raw_board->snake->getY()][raw_board->snake->getX()] = raw_board->snake->getValue();

                int index = 0;
                for(int y = 0; y < ySize/k; y++)
                {
                    for(int x = 0; x < xSize/k; x++)
                    {
                        if(ptr[y][x] > 0 && ptr[y][x] < raw_board->snake->getValue())
                        {
                            itemBody[index]->setPos(x*k,y*k);
                            index++;
                        }
                    }
                }

                itemHead->setPos(raw_board->snake->getX()*k,raw_board->snake->getY()*k);
            }
            else
            {
                qDebug() << "CHUJJJJJJJJJ";
            }




        }

        void updateMove()
        {
            raw_board->moveSnake();
        }
};

