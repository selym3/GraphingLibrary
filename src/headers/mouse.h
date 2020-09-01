#ifndef __MOUSE_H__
#define __MOUSE_H__ 

#include "./vector.h"

typedef struct Mouse
{
    int buttons[3];
    int l_buttons[3];

    Vec2 pos;
    Vec2 l_pos;
} Mouse;

typedef enum Button
{
    LEFT = 0, MIDDLE = 1, RIGHT = 2
} Button;

Mouse GetMouse();
void UpdateMouse(Mouse *, Vec2, int, int, int);

int GetButton(Mouse *, Button);
int GetButtonHeld(Mouse *, Button);
int GetButtonPressed(Mouse *, Button);

Vec2 GetMousePos(Mouse *);
Vec2 GetMouseChange(Mouse *);

#endif