
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Food
{

    private:
        int pos_x = 0;
        int pos_y = 0;
        int xSize = 0;
        int ySize = 0;

    public:
        Food(int xSize, int ySize)//xSize and ySize get sizes of map
        {
            this->xSize = xSize;
            this->ySize = ySize;

            pos_x = rand() % xSize;
            pos_y = rand() % ySize;
        }

        void setX(int x){this->pos_x = x;}
        void setY(int y){this->pos_y = y;}

        int getX(){return this->pos_x;}
        int getY(){return this->pos_y;}

        void randPosXY()
        {
              /* generate secret number between 1 and 10: */
              pos_x = rand() % xSize;
              pos_y = rand() % ySize;
        }
};

