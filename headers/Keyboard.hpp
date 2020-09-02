#ifndef __KEYBOARD_HPP__
#define __KEYBOARD_HPP__

#define KEY(X) (SDL_SCANCODE_##X)

#include <cstdint>

#include <SDL2/SDL_scancode.h>

namespace mp
{

    struct Keyboard
    {
        Keyboard();

        bool Get(SDL_Scancode key) const;
        void Set(const Uint8 * key_set);

    private:
        const Uint8 *keys;
        const Uint8 *l_keys;
    };

}

#endif