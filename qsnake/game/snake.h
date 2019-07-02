#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"

class Snake {
   public:
    enum Direction { UP, DOWN, LEFT, RIGHT };
    Snake(/* args */);
    ~Snake();
    void move(Direction direction);
    void grow();
    Point* getBodyVertex(); // return the array of all the vertex of the snake
    int getBodyVertexSize();
    
   private:
    Point* body_vertex;     // an array to store all the vertex of the snake
    int vertex_counter;     // the size of body_vertex
};

#endif  // SNAKE_H