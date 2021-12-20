#include "main.hpp"

#pragma once

class Ai {
public :
   virtual void update(Actor *owner)=0;
};

//AI para jugadores:
class PlayerAi : public Ai {
public :
   void update(Actor *owner);

protected :
   bool moveOrAttack(Actor *owner, int targetx, int targety);
};


//AI para monstruos
//Cuántos turnos fuera del fov nos persiguen
static const int TRACKING_TURNS=3;


class MonsterAi : public Ai {
public :
  void update(Actor *owner);

protected :
  int moveCount;
  void moveOrAttack(Actor *owner, int targetx, int targety);
};
