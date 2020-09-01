#include "../headers/camera.h"

Vec2 ToCamera(Camera *camera, Vec2 point) { return Vec2_Mul(Vec2_Sub(point, camera->pan), camera->zoom); }
Vec2 FromCamera(Camera *camera, Vec2 point) { return Vec2_Add(Vec2_Div(point, camera->zoom), camera->pan); }

SDL_FRect ToCameraR(Camera *camera, SDL_FRect r)
{
    Vec2 new_pos = ToCamera(camera, (Vec2){r.x, r.y});
    Vec2 new_bottom = ToCamera(camera, (Vec2){r.x + r.w, r.y + r.h});

    Vec2 size = Vec2_Sub(new_bottom, new_pos);

    return (SDL_FRect){new_pos.x, new_pos.y, size.x, size.y};
}

SDL_FRect FromCameraR(Camera *camera, SDL_FRect r)
{
    Vec2 new_pos = FromCamera(camera, (Vec2){r.x, r.y});
    Vec2 new_bottom = FromCamera(camera, (Vec2){r.x + r.w, r.y + r.h});

    Vec2 size = Vec2_Sub(new_bottom, new_pos);

    return (SDL_FRect){new_pos.x, new_pos.y, size.x, size.y};
}

void ResetCamera(Camera *camera) { camera->pan.x = 0; camera->pan.y = 0; camera->zoom.x = 1; camera->zoom.y = 1; }
void UpdatePan(Camera *camera, Vec2 offset) { camera->pan = Vec2_Sub(camera->pan, Vec2_Div(offset, camera->zoom)); }
void UpdateZoom(Camera *camera, Vec2 mul_zoom) { camera->zoom = Vec2_Mul(camera->zoom, mul_zoom); }