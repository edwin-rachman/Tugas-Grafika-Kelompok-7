#include "IntersectionMap.h"
#include "Line.h"
#include <vector>
#include <stack>
using namespace std;

IntersectionMap::IntersectionMap() {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    intersects = new bool[0];
}
IntersectionMap::IntersectionMap(const IntersectionMap& map) {
    x = map.x;
    y = map.y;
    width = map.width;
    height = map.height;
    intersects = new bool[width * height];
    for (int i = 0; i < width * height; i++) {
        intersects[i] = map.intersects[i];
    }
}

IntersectionMap::~IntersectionMap() {
    delete[] intersects;
}

IntersectionMap& IntersectionMap::operator=(const IntersectionMap& map) {
    delete[] intersects;
    x = map.x;
    y = map.y;
    width = map.width;
    height = map.height;
    intersects = new bool[width * height];
    for (int i = 0; i < width * height; i++) {
        intersects[i] = map.intersects[i];
    }
}

bool IntersectionMap::setPoint(int x, int y) {
    int t_x = x - this->x;
    int t_y = y - this->y;
    if ((t_x >= 0) && (t_y >= 0) && (t_x < width) && (t_y < height)) {
        int idx = t_x + (t_y * width);
        // intersects[idx] = !intersects[idx];
        intersects[idx] = true;
        return intersects[idx];
    }
    return false;
}

bool IntersectionMap::getPoint(int x, int y) {
    int t_x = x - this->x;
    int t_y = y - this->y;
    if ((t_x >= 0) && (t_y >= 0) && (t_x < width) && (t_y < height)) {
        int idx = t_x + (t_y * width);
        return intersects[idx];
    }
    return false;
}

void IntersectionMap::floodFill() {
    stack<Point> next;
    // Find origin.
    for (int y = 0; y < height; y++) {
        bool prev = false;
        int count = 0;
        int t_x = 0;
        for (int x = 0; x < width; x++) {
            int i = x + y * width;
            if ((!prev) && (intersects[i])) {
                t_x = x - 1;
                count++;
            }
            prev = intersects[i];
        }
        if ((count >= 2) && ((t_x >= 0) && (y >= 0) && (t_x < width) && (y < height))) {
            next.push(Point(t_x, y));
        }
    }
    // Depth first flood filling.
    while (!next.empty()) {
        Point curr = next.top();
        next.pop();
        int i = curr.getX() + (curr.getY() * width);
        if (!intersects[i]) {
            intersects[i] = true;
            Point up(curr.getX(), curr.getY() + 1);
            if ((up.getX() >= 0) && (up.getY() >= 0) && (up.getX() < width) && (up.getY() < height)) {
                i = up.getX() + (up.getY() * width);
                if (!intersects[i]) {
                    next.push(up);
                }
            }
            Point down(curr.getX(), curr.getY() - 1);
            if ((down.getX() >= 0) && (down.getY() >= 0) && (down.getX() < width) && (down.getY() < height)) {
                i = down.getX() + (down.getY() * width);
                if (!intersects[i]) {
                    next.push(down);
                }
            }
            Point left(curr.getX() - 1, curr.getY());
            if ((left.getX() >= 0) && (left.getY() >= 0) && (left.getX() < width) && (left.getY() < height)) {
                i = left.getX() + (left.getY() * width);
                if (!intersects[i]) {
                    next.push(left);
                }
            }
            Point right(curr.getX() + 1, curr.getY());
            if ((right.getX() >= 0) && (right.getY() >= 0) && (right.getX() < width) && (right.getY() < height)) {
                i = right.getX() + (right.getY() * width);
                if (!intersects[i]) {
                    next.push(right);
                }
            }
        }
    }
}

void IntersectionMap::calculateIntersections(std::vector<Line *> lines) {
    if (!lines.empty()) {
        // Calculate boundary.
        int min_x, min_y, max_x, max_y;
        std::vector<Line *>::iterator it = lines.begin();
        min_x = (*it)->minBoundary().getX();
        min_y = (*it)->minBoundary().getY();
        max_x = (*it)->maxBoundary().getX();
        max_y = (*it)->maxBoundary().getY();
        for (it++; it != lines.end(); it++) {
            if (min_x > (*it)->minBoundary().getX()) {
                min_x = (*it)->minBoundary().getX();
            }
            if (min_y > (*it)->minBoundary().getY()) {
                min_y = (*it)->minBoundary().getY();
            }
            if (max_x < (*it)->maxBoundary().getX()) {
                max_x = (*it)->maxBoundary().getX();
            }
            if (max_y < (*it)->maxBoundary().getY()) {
                max_y = (*it)->maxBoundary().getY();
            }
        }
        x = min_x;
        y = min_y;
        width = max_x - min_x + 1;
        height = max_y - min_y + 1;
        delete[] intersects;
        intersects = new bool[width * height];
        for (int i = 0; i < width * height; i++) {
            intersects[i] = false;
        }
        for (it = lines.begin(); it != lines.end(); it++) {
            // Apply bresenham to get the intersection point.
            int d_x = (*it)->getPointDestination().getX() - (*it)->getPointOrigin().getX();
            int d_y = (*it)->getPointDestination().getY() - (*it)->getPointOrigin().getY();
            // if (d_y == 0) {
            //     setPoint((*it)->getPointOrigin().getX(), (*it)->getPointOrigin().getY());
            //     setPoint((*it)->getPointDestination().getX(), (*it)->getPointDestination().getY());
            //     continue;
            // }
            int d_x_abs = std::abs(d_x);
            int d_y_abs = std::abs(d_y);
            int sign_d_x = d_x > 0 ? 1 : -1;
            int sign_d_y = d_y > 0 ? 1 : -1;
            int x = d_y_abs >> 1;
            int y = d_x_abs >> 1;
            int p_x = (*it)->getPointOrigin().getX();
            int p_y = (*it)->getPointOrigin().getY();

            setPoint(p_x, p_y);
            if (d_x_abs >= d_y_abs) {
                for (int i = 0; i < d_x_abs; ++i) {
                    y += d_y_abs;
                    if (y >= d_x_abs) {
                        y -= d_x_abs;
                        p_y += sign_d_y;
                    }
                    p_x += sign_d_x;
                    setPoint(p_x, p_y);
                }
            }
            else {
                for (int i = 0; i < d_y_abs; ++i) {
                    x += d_x_abs;
                    if (x >= d_y_abs) {
                        x -= d_y_abs;
                        p_x += sign_d_x;
                    }
                    p_y += sign_d_y;
                    setPoint(p_x, p_y);
                }
            }
        }
    } else {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
        delete[] intersects;
        intersects = new bool[0];
    }
}

int IntersectionMap::getX() {
    return x;
}
int IntersectionMap::getY() {
    return y;
}
int IntersectionMap::getWidth() {
    return width;
}
int IntersectionMap::getHeight() {
    return height;
}