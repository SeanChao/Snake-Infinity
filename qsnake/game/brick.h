#include "point.h"
#include <vector>

class Brick {
   private:
    std::vector<Point> brick_point;

   public:
    Brick(int cell_number);
    ~Brick();
    bool inBrick(const Point &p) const;

    std::vector<Point>* getBrick();
};