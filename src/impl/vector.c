#include "../headers/vector.h"

Vec2 Vec2_Add(Vec2 lhs, Vec2 rhs) { return (Vec2){lhs.x + rhs.x, lhs.y + rhs.y}; }
Vec2 Vec2_Sub(Vec2 lhs, Vec2 rhs) { return (Vec2){lhs.x - rhs.x, lhs.y - rhs.y}; }
Vec2 Vec2_Mul(Vec2 lhs, Vec2 rhs) { return (Vec2){lhs.x * rhs.x, lhs.y * rhs.y}; }
Vec2 Vec2_Div(Vec2 lhs, Vec2 rhs) { return (Vec2){lhs.x / rhs.x, lhs.y / rhs.y}; }