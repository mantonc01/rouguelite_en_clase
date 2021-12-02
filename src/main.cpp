#include "libtcod.hpp"
#include "Actor.hpp"
int main() {

   //int playerx=40,playery=25;//nuestro actor posicion eje coordenadas
  Actor player(25,25,'@',TCODColor::yellow);

   TCODConsole::initRoot(80,50,"Mi primer Rouguelite",false);//tamaño de la consola
   while ( !TCODConsole::isWindowClosed() ) {
       TCOD_key_t key;
       TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);//configuración de las teclas
       switch(key.vk) {
           case TCODK_UP : player.y--; break;
           case TCODK_DOWN : player.y++; break;
           case TCODK_LEFT : player.x--; break;
           case TCODK_RIGHT : player.x++; break;
           default:break;
       }
       TCODConsole::root->clear();//se limpia la interfaz
       //TCODConsole::root->putChar(player.x,player.y,'@');//se pone el personaje en la posicion
       player.render();
       TCODConsole::flush();
   }
   return 0;
}
