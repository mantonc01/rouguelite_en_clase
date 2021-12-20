#include "main.hpp"


#pragma once
#define FOVRADIOUS_INICIAL 10

#define ANCHO_PANTALLA 80
#define ALTO_PANTALLA 50

class Engine{
public:

  enum GameStatus {
    STARTUP,  // Estado inicial, preparar el juego.
    IDLE,  // Estás parado, no hay nada que procesar
    NEW_TURN,  // Te movistes, hay que procesar.
    VICTORY,  // Has ganado
    DEFEAT  // Has perdido
  } gameStatus;  // Declaramos una variable


  Map* map;
  TCODList<Actor*> actors;
  Actor* player;
  int fovRadius;

  int screenWidth;
  int screenHeight;
  TCOD_key_t lastKey;

  Engine(int screenWidth, int screenHeight);
  ~Engine();
  void update();
  void render() ;
  void sendToBack(Actor *actor);
};

extern Engine engine;
