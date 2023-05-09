#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "snake_map.h"
#include <vector>

class Draw
{
    private:
         int k = 40; //size of one block on map
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
        int actual_food = 0;
        int gameTime = 0;
        int eatenFood = 0;
        int totalPoints = 0;
        int speed = 1;

    public:

        Draw(int x, int y);
        ~Draw();

        QGraphicsScene      *   getScene()    {return scene;}
        QGraphicsPixmapItem *   getItemMap()  {return itemMap;}
        QGraphicsPixmapItem *   getItemHead() {return itemHead;}
        QGraphicsPixmapItem *   getItemFood() {return itemFood;}


        int   getTime()    {return gameTime;}
        int   getFood()  {return eatenFood;}
        int   getPoints() {return totalPoints;}


       void   incrementTime()   {gameTime++;}
       void   incrementFood()   {eatenFood++;}
       int   calcPoints()       {return totalPoints = eatenFood * 10* speed - gameTime * 1.5;}
       void   setSpeed(int x)   {speed = x;}


        void clearMap() {scene->clear();}
        bool getState();
        void restart();
        void updateDir(int dir);
        void updateMove();
        void rotateHead();
        void autoMove();
};

