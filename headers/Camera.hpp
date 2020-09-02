#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "Vec2.hpp"

#include <SDL2/SDL.h>

namespace mp
{

    struct Camera
    {
        mp::Vec2 pan;
        mp::Vec2 zoom;

        const mp::Vec2 original_pan;
        const mp::Vec2 original_zoom;

        Camera();
        Camera(mp::Vec2, mp::Vec2);

        void Reset();

        mp::Vec2 operator()(const mp::Vec2& in) const;
        SDL_FRect operator()(const SDL_FRect& in) const;

        mp::Vec2 operator[](const mp::Vec2& out) const;
        SDL_FRect operator[](const SDL_FRect& out) const;
    };

}

#endif