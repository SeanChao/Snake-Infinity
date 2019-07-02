#include "snake.h"

class Land {
   private:
    const int WIDTH;
    const int HEIGHT;
    Snake *snake;

   public:
    Land(int width = 20, int height = 20);
    ~Land();
};


