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
    
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
};
#endif  // POINT_H