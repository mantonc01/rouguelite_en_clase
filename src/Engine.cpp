#include "main.hpp"

Engine::Engine(int screenWidth, int screenHeight): fovRadius(FOVRADIOUS_INICIAL), gameStatus(STARTUP),
   screenWidth(screenWidth),screenHeight(screenHeight) {
  TCODConsole::initRoot(screenWidth,screenHeight,"Mi primer Rouguelite",false);

  //Jugador
  player = new Actor(25, 25, '@',"player", TCODColor::yellow);
  player->destructible=new PlayerDestructible(30,2,"Tu cadaver");
  player->attacker=new Attacker(5);
  player->ai = new PlayerAi();
  actors.push(player);



  map = new Map(ANCHO_MAPA, ALTO_MAPA);
  map->computeFov();
}

Engine::~Engine( ){
  delete map;
  actors.clearAndDelete();
}


void Engine::update(){

  if(gameStatus == STARTUP){
    map->computeFov();
  }
  //Siempre que pasamos por un nuevo update, pasamos a estar en idle.
  gameStatus = IDLE;

  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL);
  player->update(); //Aquí a veces se pasa al estado NEW_TURN (cuando se mueve)

  //Actualizar el resto de actores:
  if(gameStatus == NEW_TURN){
    for(Actor* actorAux : actors){
      if(actorAux != player){
        actorAux->update();
      }
    }
    gameStatus = IDLE;
  }
}


void Engine::render(){
  TCODConsole::root->clear();
  //Mapa
  if(gameStatus == NEW_TURN){
    map->computeFov();
  }
  map->render();
  //Actores
  for(Actor* actorAux : actors){
    if(map->isInFov(actorAux->x,actorAux->y)){
      actorAux ->render();
    }

  }
  //re-renderizo el jugador:
  player->render();

  //Renderizamos la GUI:
  TCODConsole::root->print(1,screenHeight-2, "HP(%s) : %d/%d",player->name.c_str(),(int)player->destructible->hp,(int)player->destructible->maxHp);
  TCODConsole::flush();
}


void Engine::sendToBack(Actor *actor) {
   actors.remove(actor);
   actors.insertBefore(actor,0);
}
