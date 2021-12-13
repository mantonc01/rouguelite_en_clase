#include "libtcod.hpp"
#include "Actor.hpp"
#include "Map.hpp"
#include "Engine.hpp"

int main() {
Engine engine;
   while ( !TCODConsole::isWindowClosed() ) {
       engine.update();
       engine.render();
   }
   return 0;
}
