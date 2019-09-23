#include "point.h"
#include <vector>

class Brick {
   private:
    std::vector<Point> brick_point;

   public:
    Brick(int cell_number);
    ~Brick();

    std::vector<Point>* getBrick();
};