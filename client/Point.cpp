#include "Point.h"


std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << '{' << p.x << ',' << ' ' << p.y << '}';
    return os;
}

