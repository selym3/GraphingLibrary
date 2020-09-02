#include "../headers/Camera.hpp"

using namespace mp;

Camera::Camera(Vec2 pan, Vec2 zoom): pan{pan}, zoom{zoom}, original_pan{pan}, original_zoom{zoom} {}
Camera::Camera(): Camera({0,0}, {1,1}) {}

void Camera::Reset() { this->pan = original_pan; this->zoom = original_zoom; }

Vec2 Camera::operator()(const Vec2& in) const { return (in - pan) * zoom; }
Vec2 Camera::operator[](const Vec2& out) const { return (out / zoom) + pan; }

SDL_FRect Camera::operator()(const SDL_FRect& in) const 
{
    Vec2 new_pos = (*this)(Vec2(in.x, in.y));
    Vec2 new_size = (*this)(Vec2({in.x + in.w, in.y + in.h}));

    new_size -= new_pos;

    return (SDL_FRect){(float) new_pos.x,(float)  new_pos.y,(float)  new_size.x,(float)  new_size.y};
}

SDL_FRect Camera::operator[](const SDL_FRect& in) const 
{
    Vec2 new_pos = (*this)[Vec2(in.x, in.y)];
    Vec2 new_size = (*this)[Vec2({in.x + in.w, in.y + in.h})];

    new_size -= new_pos;

    return (SDL_FRect){(float) new_pos.x,(float)  new_pos.y,(float)  new_size.x,(float)  new_size.y};
}