#include "Character.h"

#include <curses.h>

namespace Cinder {

Character::Character(char _ch, Color _color, Color _bgColor) :
    ch(_ch),
    color(_color),
    bgColor(_bgColor) {}

void Character::display() {
    // TODO: colors
    addch(ch);
}

} // namespace Cinder
