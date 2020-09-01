#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "vector.h"
#include <SDL2/SDL.h>

typedef struct Camera
{
    Vec2 pan, zoom;
} Camera;

Vec2 ToCamera(Camera *, Vec2);
Vec2 FromCamera(Camera *, Vec2);

SDL_FRect ToCameraR(Camera *, SDL_FRect);
SDL_FRect FromCameraR(Camera *, SDL_FRect);

void UpdatePan(Camera *, Vec2);
void UpdateZoom(Camera *, Vec2);
void ResetCamera(Camera *);

#endif