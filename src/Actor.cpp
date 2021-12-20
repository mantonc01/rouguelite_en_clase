#include "main.hpp"

Actor::Actor(int x, int y, int ch, std::string name, const TCODColor &col): x(x), y(y), ch(ch), name(name), col(col), blocks(true),attacker(NULL),destructible(NULL),ai(NULL){
};

Actor::~Actor(){
  //Deberíamos eliminar la memoria:
  if ( attacker ) delete attacker;
  if ( destructible ) delete destructible;
  if ( ai ) delete ai;
}

void Actor::render( ) const{
  TCODConsole::root->putChar(x,y,ch);
  TCODConsole::root->setCharForeground(x,y,col);
};


void Actor::update() {
  if(ai ){
    ai->update(this);
  }
};



