#include "libtcod.hpp"
#include "Map.hpp"
#include "Actor.hpp"


#pragma once

class Engine{
public:
  Map* map;
  TCODList<Actor*> actors;
  Actor* player;

  Engine();
  ~Engine();
  void update();
  void render();
};

extern Engine engine;
