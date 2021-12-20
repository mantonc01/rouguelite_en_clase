#include "main.hpp"
Engine engine(ANCHO_PANTALLA,ALTO_PANTALLA);

int main() {

  while ( !TCODConsole::isWindowClosed() ) {
      engine.update();
      engine.render();
  }
  return  0;
}
