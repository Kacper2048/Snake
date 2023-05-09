#include "snake.h"
#include "food.h"

class SnakeMap
{
    private:
    bool game_state = false;
    int xSize;
    int ySize;
    int **array = nullptr;

    public:
    Snake * snake = nullptr;
    Food * food = nullptr;

    SnakeMap(int, int);
    ~SnakeMap();

    void decreaseFieldValue(); //decrease value of field about one
    void moveSnake();//make move every signal is generated
    void changeDirection(int); //change direction and make move without waiting for signal
    void checkState();
    int ** getRawMap(){return array;}
    bool getGameState(){return game_state;}
};

