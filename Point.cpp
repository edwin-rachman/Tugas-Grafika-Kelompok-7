#include "Point.h"

Point::Point() {
    this-> x = 0;
    this-> y = 0;
}

Point::Point(int x, int y) {
    this-> x = x;
    this-> y = y;
}

int Point::GetX() {
    return this->x;
}

int Point::GetY() {
    return this->y;
}

void Point::SetX(int x) {
    this-> x = x;
}

void Point::SetY(int y) {
    this-> y = y;
}