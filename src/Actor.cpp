#include "Actor.hpp"

Actor::Actor(int x, int y, int ch, const TCODColor &col):x(x) y(y) ch(ch) col(col);
void Actor::render() const{
   TCODConsole::root->putChar(x,y,ch);
   TCODConsole::root->setChar(x,y,col);
};
