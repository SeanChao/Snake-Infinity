#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"

class Snake {
   public:
    enum Direction { UP, DOWN, LEFT, RIGHT };
    Snake(/* args */);
    ~Snake();
    void setDirection(Direction direction);
    void move();
    void grow();
    Direction getDirection() const;
    Point* getBodyVertex() const;   // return the array of all the vertex of the snake
    int getBodyVertexSize() const;
    bool getDigestFood() const;
    bool inBody(const Point &p);

   private:
    int step;               // the step of every movement
    Direction direction;    // the snake's current movement direction
    Point* body_vertex;     // an array to store all the vertex of the snake
    int vertex_size;        // the size of body_vertex
    bool digestFood;        // whether to handle the food eaten just now
    Point sloughed_tail;    // the tail of last move
    int score;              // the score of the snake

    void clear();           // reset the game
};

#endif  // SNAKE_H