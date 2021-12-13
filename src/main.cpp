#include "libtcod.hpp"
#include "Actor.hpp"
#include "Map.hpp"
#include "Engine.hpp"

Engine engine;

int main() {

  while ( !TCODConsole::isWindowClosed() ) {
      engine.update();
      engine.render();
  }
  return 0;
}
