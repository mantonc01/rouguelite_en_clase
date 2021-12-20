#include "main.hpp"

#pragma once

class Actor {
public :
  int x,y; // position on map
  int ch; // ascii code
  std::string name;
  TCODColor col; // color

  bool blocks; //Se puede andar por encima?
  Attacker* attacker; // El componente de ataque
  Destructible* destructible; // El componente destructible
  Ai* ai; // El componente de actualización


  Actor(int x, int y, int ch, std::string name,  const TCODColor &col);
  ~Actor();
  void render( ) const;
  void update() ;

};


