#include "../headers/Keyboard.hpp"
using namespace mp;
Keyboard::Keyboard() : keys{NULL} {}
bool Keyboard::Get(SDL_Scancode key) const { return keys ? keys[key] : false; }
void Keyboard::Set(const Uint8 *key_set)
{
    l_keys = keys;
    keys = key_set;
}