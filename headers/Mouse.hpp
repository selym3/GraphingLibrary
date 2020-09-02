#ifndef __MOUSE_HPP__
#define __MOUSE_HPP__

#include "Vec2.hpp"

namespace mp
{
    struct Mouse
    {
        enum Button
        {
            LEFT = 0, MIDDLE, RIGHT
        };

        Mouse();
        ~Mouse();

        void Update(mp::Vec2 pos, bool l, bool m, bool r);
        
        bool Get(Button button) const;
        bool GetHeld(Button button) const;
        bool GetPressed(Button button) const;
        const mp::Vec2& GetPos() const;
        mp::Vec2 GetChange() const; 

    private:
        bool buttons[3];
        bool l_buttons[3];

        mp::Vec2 pos;
        mp::Vec2 l_pos;
    };

};

#endif