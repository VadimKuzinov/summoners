#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>


struct Point;
std::istream& operator>>(std::istream&, Point&);
std::ostream& operator<<(std::ostream&, const Point&);


struct Point {
    double x;
    double y;

    constexpr static double eps = 1e-6;
    constexpr static double pi = 3.14159265358979323846;

    static Point withIntCfs(const Point& p) {
        return {static_cast<double>(lround(p.x)), static_cast<double>(lround(p.y))};
    }

    static double distance(const Point& p1, const Point& p2) {
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }

    static Point normalized(const Point& p) {
        if (p.x == 0 && p.y == 0) {
            return p;
        }
        auto len = distance(p, Point{0, 0});
        return {p.x / len, p.y / len};
    }

    operator std::string() const {
        return std::to_string(x) + " " + std::to_string(y);
    }
};


inline bool operator==(const Point& p1, const Point& p2) {
    return std::abs(p1.x - p2.x) < Point::eps && std::abs(p1.y - p2.y) < Point::eps;
}

inline Point operator-(const Point& p1, const Point& p2) {
    return {p1.x - p2.x, p1.y - p2.y};
}

inline Point operator+(const Point& p1, const Point& p2) {
    return {p1.x + p2.x, p1.y + p2.y};
}

inline Point operator*(const Point& p, double cf) {
    return {p.x * cf, p.y * cf};
}

namespace std {
    template <>
    struct hash<Point> {
        std::size_t operator()(const Point& p) const {
            return hash<double>()(p.x) ^ hash<double>()(p.y);
        }
    };
}

