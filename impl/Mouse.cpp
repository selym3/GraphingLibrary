#include "../headers/Mouse.hpp"

using namespace mp;

Mouse::Mouse() {}
Mouse::~Mouse() {}

void Mouse::Update(Vec2 pos, bool l, bool m, bool r) 
{
    this->l_pos = this->pos;
    this->pos = pos;

    l_buttons[0] = buttons[0];
    buttons[0] = l;

    l_buttons[1] = buttons[1];
    buttons[1] = m;

    l_buttons[2] = buttons[2];
    buttons[2] = r;
}

bool Mouse::Get(Mouse::Button button) const { return buttons[button]; }
bool Mouse::GetPressed(Mouse::Button button) const { return buttons[button] && !l_buttons[button]; }
bool Mouse::GetHeld(Mouse::Button button) const { return buttons[button] && l_buttons[button]; }
const Vec2& Mouse::GetPos() const { return pos; }
Vec2 Mouse::GetChange() const { return pos - l_pos; }