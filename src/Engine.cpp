#include "Engine.hpp"

Engine::Engine(){
  TCODConsole::initRoot(ANCHO_MAPA,ALTO_MAPA,"Mi primer Rouguelite",false);
  map = new Map(ANCHO_MAPA, ALTO_MAPA);
  //Jugador
  player = new Actor(25, 25, '@', TCODColor::yellow);
  actors.push(player);
  //Añadir un NPC:
  Actor* npc = new Actor(40, 25, 'O', TCODColor::white);
  actors.push(npc);

}

Engine::~Engine(){
  delete map;
  actors.clearAndDelete();
}


void Engine::update(){
  TCOD_key_t key;
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
  switch(key.vk) {
      case TCODK_UP :
        if(!map->isWall(player->x, player->y-1)){
            player->y--;
        }
        break;
      case TCODK_DOWN :if(!map->isWall(player->x, player->y+1)){
            player->y++;
        }; break;
      case TCODK_LEFT : if(!map->isWall(player->x-1, player->y)){
            player->x--;
        }; break;
      case TCODK_RIGHT : if(!map->isWall(player->x+1, player->y)){
            player->x++;
        }; break;
      default:break;
  }
}


void Engine::render(){
  TCODConsole::root->clear();
  //Mapa
  map->render();
  //Actores
  for(Actor* actorAux : actors){
    actorAux ->render();
  }
  //re-renderizo el jugador:
  player->render();
  TCODConsole::flush();
}
