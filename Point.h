/* Class of Point */
class Point {
    public:
        Point();
        Point(int, int);
        int GetX();
        int GetY();
        void SetX(int x);
        void SetY(int y);
    private:
        int x, y;
};