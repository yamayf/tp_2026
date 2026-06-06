#include "Polygon.h"
#include <algorithm>
#include <string>

bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator==(const Polygon& a, const Polygon& b) {
    if (a.points.size() != b.points.size()) return false;
    return std::equal(a.points.begin(), a.points.end(), b.points.begin());
}

std::istream& operator>>(std::istream& in, Point& p) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c1 = 0, c2 = 0, c3 = 0;
    int x = 0, y = 0;
    if (!(in >> c1 >> x >> c2 >> y >> c3) || c1 != '(' || c2 != ';' || c3 != ')') {
        in.setstate(std::ios::failbit);
    } else {
        p.x = x; p.y = y;
    }
    return in;
}

std::istream& operator>>(std::istream& in, Polygon& p) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    size_t count = 0;
    if (!(in >> count)) return in;
    std::vector<Point> temp;
    for (size_t i = 0; i < count; ++i) {
        Point pt;
        if (!(in >> pt)) {
            in.setstate(std::ios::failbit);
            return in;
        }
        temp.push_back(pt);
    }
    p.points = std::move(temp);
    return in;
}
