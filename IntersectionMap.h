#ifndef INTERSECTIONMAP_H
#define INTERSECTIONMAP_H

#include <vector>
#include "Line.h"

class IntersectionMap {
private:
    int x;
    int y;
    int width;
    int height;
    bool * intersects;
public:
    IntersectionMap();
    IntersectionMap(const IntersectionMap& map);
    ~IntersectionMap();
    IntersectionMap& operator=(const IntersectionMap& map);
    bool setPoint(int x, int y);
    bool getPoint(int x, int y);
    void calculateIntersections(std::vector<Line *> lines);
    void floodFill();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
};

#endif
