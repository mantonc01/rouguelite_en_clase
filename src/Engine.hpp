#include "libtcod.hpp"
#include "Map.hpp"
#include "Actor.hpp"


#pragma once
#define FOVRADIOUS_INICIAL

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

extern Engine engine; // como el singleton
