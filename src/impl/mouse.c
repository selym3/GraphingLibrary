#include "../headers/mouse.h"

Mouse GetMouse() { return (Mouse){ {0, 0, 0}, {0, 0, 0}}; }
void UpdateMouse(Mouse *mouse, Vec2 pos, int l, int m, int r)
{
    mouse->l_buttons[0] = mouse->buttons[0];
    mouse->buttons[0] = l;

    mouse->l_buttons[1] = mouse->buttons[1];
    mouse->buttons[1] = m;

    mouse->l_buttons[2] = mouse->buttons[2];
    mouse->buttons[2] = r;

    mouse->l_pos = mouse->pos;
    mouse->pos = pos;
}

int GetButton(Mouse *mouse, Button button) { return mouse->buttons[button]; }
int GetButtonHeld(Mouse *mouse, Button button) { return mouse->buttons[button] && mouse->l_buttons[button]; }
int GetButtonPressed(Mouse *mouse, Button button) { return mouse->buttons[button] && !(mouse->l_buttons[button]); }

Vec2 GetMousePos(Mouse *mouse) { return mouse->pos; }
Vec2 GetMouseChange(Mouse *mouse) { return Vec2_Sub(mouse->pos, mouse->l_pos); }