
class Snake
{
    private:
        int pos_x = 0;
        int pos_y = 0;
        int value = 0;
        const int value_start = 0;
        const int value_x = 0;
        const int value_y = 0;
        int dir = 0; //=0 down 1-left 2-up 3-right

    public:
        Snake(int, int, int, int);

        void setX(int x){this->pos_x = x;}
        void setY(int y){this->pos_y = y;}
        void setValue(int q){this->value = q;}
        void setDir(int q){this->dir = q;}

        void makeMove();
        void increaseByFood();
        void restart();

        int getX(){return this->pos_x;}
        int getY(){return this->pos_y;}
        int getValue(){return this->value;}
        int getDir(){return this->dir;}
};
