#include "Map.hpp"
#include "libtcod.hpp"
#include "Engine.hpp"


Map::Map(int width, int height): width(width), height(height){
  //Habrá que inicializar el tiles:
  tiles = new Tile[width*height];

  //Probar con un dig:
  dig(40,40,2,2);

};

Map::~Map(){
  delete[] tiles;
};
bool Map::isWall(int x, int y) const{
  //Ir a la posición y marcar que es pared
  return !tiles[x+y*width].canWalk;
};
void Map::render() const{
  static const TCODColor darkGround(50,50,150);
  static const TCODColor darkWall(0,0,100);

  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++)
    {
      if(isWall(i,j)){
          TCODConsole::root->setCharBackground(i,j,darkWall);
      } else{
          TCODConsole::root->setCharBackground(i,j,darkGround);
      }
    }
  }
};


void Map::dig(int x_inicial, int y_inicial, int x_final, int y_final){
    //Swapear si inicial > final
    if(x_inicial > x_final){
      int aux = x_inicial;
      x_inicial = x_final;
      x_final = aux;
    }

    if(y_inicial > y_final){
      int aux = y_inicial;
      y_inicial = y_final;
      y_final = aux;
    }

    //Por último, marcamos el agujero:
    for(int x = x_inicial; x < x_final; x++){
      for(int y = y_inicial; y < y_final; y++){
        setWalkable(x,y);
      }
    }
};

void Map::createRoom(bool first, int x1, int y1, int x2, int y2){
  dig(x1,y1,x2,y2);
  if(first){
    //Movemos el actor principal
    engine.player->x = (x1+x2)/2;
    engine.player->y = (y1+y2)/2;
  }
};



void Map::setWall(int x, int y){
  tiles[x+y*width].canWalk = false;
};


void Map::setWalkable(int x, int y){
  tiles[x+y*width].canWalk = true;
};
