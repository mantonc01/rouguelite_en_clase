#include "main.hpp"



#pragma once

#define ANCHO_MAPA 80
#define ALTO_MAPA 43

struct Tile {
   bool explored; //Está explorado?
   Tile() : explored(false) {}
};


class Map {
public :
  int width, height;


  Map(int width, int height);
  ~Map();
  bool isWall(int x, int y) const;
  void render() const;

  void dig(int x_inicial, int y_inicial, int x_final, int y_final);
  void createRoom(bool first, int x1, int y1, int x2, int y2);

  bool isInFov(int x, int y) const;
  bool isExplored(int x, int y) const;
  void computeFov();
  bool canWalk(int x, int y) const;
  void addMonster(int x, int y);


protected :
  Tile *tiles;
  TCODMap *map;

  void setWall(int x, int y);
  void setWalkable(int x, int y ); //Para hacer dig!
};

