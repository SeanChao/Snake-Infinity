#ifndef POINT_H
#define POINT_H
class Point {
   private:
    // the cordinate of the Point
    int x;
    int y;

   public:
    Point();
    Point(int x, int y);
    ~Point();
    
    int getX();
    int getY();
};
#endif  // POINT_H