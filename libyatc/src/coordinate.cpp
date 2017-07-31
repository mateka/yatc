#include <yatc/coordinate.h>


namespace yatc {
    coordinate::coordinate(const type x, const type y)
        : m_data{x, y}
    {}

    coordinate& coordinate::operator+=(const coordinate& other) {
        x() += other.x();
        y() += other.y();
        return *this;
    }

    coordinate& coordinate::operator-=(const coordinate& other) {
        return *this += -other;
    }

    void coordinate::rotate(const rotation dir) {
        // Use 2D rotation matrix with angle set to 90 degrees,
        // when rotating counter clockwise and -90 degrees
        // when rotating clockwise.
        const auto xc = x();
        const auto yc = y();
        x() = (dir == rotation::ccw ? -1:  1) * yc;
        y() = (dir == rotation::ccw ?  1: -1) * xc;
    }

    coordinate operator-(const coordinate& c) {
        return coordinate(-c.x(), -c.y());
    }

    coordinate operator+(coordinate a, const coordinate& b) {
        return a += b;
    }

    coordinate operator-(coordinate a, const coordinate& b) {
        return a -= b;
    }

    bool operator==(const coordinate& a, const coordinate& b) {
        return a.x() == b.x() && a.y() == b.y();
    }

    bool operator!=(const coordinate& a, const coordinate& b) {
        return !(a == b);
    }

    coordinate rotate(coordinate c, const rotation dir) {
        c.rotate(dir);
        return c;
    }

    std::ostream& operator<<(std::ostream& os, const coordinate& c) {
        return os
            << "<" << static_cast<int>(c.x()) << ", "
            << static_cast<int>(c.y()) << ">";
    }
}
