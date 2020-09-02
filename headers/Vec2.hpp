#ifndef __VEC2_HPP__
#define __VEC2_HPP__

namespace mp
{

    struct Vec2
    {
        double x, y;

        Vec2(double x, double y);
        Vec2(double xy);
        Vec2();

        Vec2(const Vec2&)=default;
        Vec2& operator=(const Vec2&)=default;

        double dot(const Vec2&) const;
        double length() const;

        Vec2& operator+=(const Vec2&);
        friend Vec2 operator+(Vec2 lhs, const Vec2& rhs) { return lhs += rhs; }

        Vec2& operator-=(const Vec2&);
        friend Vec2 operator-(Vec2 lhs, const Vec2& rhs) { return lhs -= rhs; }
        
        Vec2& operator*=(const Vec2&);
        friend Vec2 operator*(Vec2 lhs, const Vec2& rhs) { return lhs *= rhs; }
        
        Vec2& operator/=(const Vec2&);
        friend Vec2 operator/(Vec2 lhs, const Vec2& rhs) { return lhs /= rhs; }
        
    };

}; // namespace mp


#endif