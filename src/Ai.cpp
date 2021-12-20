#include "main.hpp"

void PlayerAi::update(Actor *owner) {
  if ( owner->destructible && owner->destructible->isDead() ) {
      return;
  }

  int dx = 0;
  int dy = 0;

  switch(engine.lastKey.vk) {
      case TCODK_UP : dy = -1; break;
      case TCODK_DOWN : dy = 1; break;
      case TCODK_LEFT : dx = -1; break;
      case TCODK_RIGHT : dx = 1; break;
      default:break;
  }

  //Actualizar nuestro jugador:
  if(dy != 0 || dx != 0){
    engine.gameStatus = Engine::NEW_TURN;
    if (moveOrAttack(owner, owner->x+dx,owner->y+dy)) {
      engine.map->computeFov();
    }
  }
}


/**
 * Devuelve falso si no se puede mover (pared u enemigo).
 * Si vas contra un enemigo, entonces haces un mensaje de ataque.
 * Si no hay pared ni enemigo, entonces actualizamos la posición de este actor (this) a x e y que pasamos.
 */
bool PlayerAi::moveOrAttack(Actor *owner, int targetx, int targety) {
  if(engine.map->isWall(targetx, targety)){
    return false;
  }
  //Recorremos todos los actores.
  for(Actor* actorAux : engine.actors){
    //Hay que interactuar si son destructibles y además estan en la posición donde nos vamos a mover
    if(actorAux->destructible &&  actorAux->x == targetx && actorAux->y == targety){
      if (!actorAux->destructible->isDead()){
        owner->attacker->attack(owner, actorAux);
        return false; //No seguimos checkeando, ya te has topado con un enemigo y le atacas
      } else{
        std::cout<<"Hay un cadáver de "<<actorAux->name<<" aquí"<<std::endl;
      }
    }
  }

  owner->x=targetx;
  owner->y=targety;
  return true;
}


//MONSTRUO:

void MonsterAi::update(Actor *owner) {
  if ( owner->destructible && owner->destructible->isDead() ) {
      return;
  }
  //Si el enemigo está en el Fov, se dirige (y ataca) al jugador.
  if ( engine.map->isInFov(owner->x,owner->y) ) {
    moveCount = TRACKING_TURNS; //Reseteamos turnos cada vez que estemos en fov.
  }

  if(moveCount >0){
    moveOrAttack(owner, engine.player->x,engine.player->y);
    moveCount --;
  }

}


void MonsterAi::moveOrAttack(Actor *owner, int targetx, int targety) {
  int dx = targetx - owner->x;
  int dy = targety - owner->y;
  //Movimiento lateral si el principal está bloqueado:
  int stepdx = (dx > 0 ? 1:-1);
  int stepdy = (dy > 0 ? 1:-1);
  float distance=sqrtf(dx*dx+dy*dy);

  if ( distance >= 2 ) { //Si estamos separados
  //Lo dividimos entre la distancia para que los valores sean 1 ó -1
  dx = (int)(round(dx/distance));
  dy = (int)(round(dy/distance));
    //Nos acercamos si es posible:
    if ( engine.map->canWalk(owner->x+dx,owner->y+dy) ) {
      owner->x += dx;
      owner->y += dy;
    } else if ( engine.map->canWalk(owner->x+stepdx,owner->y) ) {
      owner->x += stepdx;
    } else if ( engine.map->canWalk(owner->x,owner->y+stepdy) ) {
      owner->y += stepdy;
    }
  } else if ( owner->attacker ) { //Si no, ataca al jugador
      owner->attacker->attack(owner,engine.player);
  }

}
