#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct Vec2
{
    double x, y;
} Vec2;

Vec2 Vec2_Add(Vec2 lhs, Vec2 rhs);
Vec2 Vec2_Sub(Vec2 lhs, Vec2 rhs);
Vec2 Vec2_Mul(Vec2 lhs, Vec2 rhs);
Vec2 Vec2_Div(Vec2 lhs, Vec2 rhs);

#endif