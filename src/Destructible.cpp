#include "main.hpp"


Destructible::Destructible(float maxHp, float defense, std::string corpseName) :
   maxHp(maxHp),hp(maxHp),defense(defense),corpseName(corpseName) {
}

float Destructible::takeDamage(Actor *owner, float damage) {
   damage -= this->defense;
   if ( damage > 0 ) {
       this->hp -= damage;
       if ( this->hp <= 0 ) {
           die(owner);
       }
   } else {
       damage=0;
   }
   return damage;
}


void Destructible::die(Actor *owner) {
   // transform the actor into a corpse!
   owner->ch='%';
   owner->col=TCODColor::darkRed;
   owner->name=corpseName;
   owner->blocks=false;
   // make sure corpses are drawn before living actors
   engine.sendToBack(owner);
}


//MONSTRUO
MonsterDestructible::MonsterDestructible(float maxHp, float defense, std::string corpseName) :
   Destructible(maxHp,defense,corpseName) {
}

void MonsterDestructible::die(Actor *owner) {
   std::cout<<owner->name<<" ha muerto."<<std::endl;
   Destructible::die(owner);
}


//JUGADOR
PlayerDestructible::PlayerDestructible(float maxHp, float defense, const char *corpseName) :
   Destructible(maxHp,defense,corpseName) {
}


void PlayerDestructible::die(Actor *owner) {
   std::cout<<"¡¡¡Has perdido!!!"<<std::endl;
   Destructible::die(owner);
   engine.gameStatus=Engine::DEFEAT;
}
