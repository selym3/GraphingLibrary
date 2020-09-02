#include "../headers/Vec2.hpp"

using namespace mp;

#include <cmath>

Vec2::Vec2(double x, double y): x{x}, y{y} {}
Vec2::Vec2(double xy): Vec2(xy, xy) {}
Vec2::Vec2(): x{}, y{} {}

double Vec2::dot(const Vec2& rhs) const { return x * rhs.x + y * rhs.y; }
double Vec2::length() const { return std::sqrt(dot(*this)); }

Vec2& Vec2::operator+=(const Vec2& rhs) { x+=rhs.x;y+=rhs.y;return *this; }
Vec2& Vec2::operator-=(const Vec2& rhs) { x-=rhs.x;y-=rhs.y;return *this; }
Vec2& Vec2::operator*=(const Vec2& rhs) { x*=rhs.x;y*=rhs.y;return *this; }
Vec2& Vec2::operator/=(const Vec2& rhs) { x/=rhs.x;y/=rhs.y;return *this; }