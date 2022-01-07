#include <stdio.h>
#include <stdarg.h>
#include "main.hpp"

static const int PANEL_HEIGHT=7;
static const int BAR_WIDTH=20;
static const int MSG_X=BAR_WIDTH+2;
static const int MSG_HEIGHT=PANEL_HEIGHT-1;

Gui::Gui() {
	con = new TCODConsole(engine.screenWidth,PANEL_HEIGHT);
}

Gui::~Gui() {
	delete con;
	log.clearAndDelete();
}

void Gui::render() {
	// limpia la consola GUI
	con->setDefaultBackground(TCODColor::black);
	con->clear();

	// DIBUJA LA BARRA DE SALUD
	renderBar(1,1,BAR_WIDTH,"HP",engine.player->destructible->hp,
		engine.player->destructible->maxHp,
		TCODColor::lightRed,TCODColor::darkerRed);

  // blit la consola GUI en la consola raíz
  TCODConsole::blit(con,0,0,engine.screenWidth,PANEL_HEIGHT,
   TCODConsole::root,0,engine.screenHeight-PANEL_HEIGHT);

	// dibuja el registro de mensajes
	int y=1;
	float colorCoef=0.4f;
	for (Message **it=log.begin(); it != log.end(); it++) {
		Message *message=*it;
		con->setDefaultForeground(message->col * colorCoef);
		con->print(MSG_X,y,message->text);
		y++;
		if ( colorCoef < 1.0f ) {
			colorCoef+=0.3f;
		}
	}

	// renderiza el ratón
	renderMouseLook();

	// blit la consola GUI en la consola raíz
	TCODConsole::blit(con,0,0,engine.screenWidth,PANEL_HEIGHT,
		TCODConsole::root,0,engine.screenHeight-PANEL_HEIGHT);
}

void Gui::renderBar(int x, int y, int width, const char *name,
	float value, float maxValue, const TCODColor &barColor,
	const TCODColor &backColor) {
	// llena el fondo
	con->setDefaultBackground(backColor);
	con->rect(x,y,width,1,false,TCOD_BKGND_SET);

	int barWidth = (int)(value / maxValue * width);
	if ( barWidth > 0 ) {
		// dibuja la barra
		con->setDefaultBackground(barColor);
		con->rect(x,y,barWidth,1,false,TCOD_BKGND_SET);
	}
	// imprime el texto en la parte superior de la barra
	con->setDefaultForeground(TCODColor::white);
	con->printEx(x+width/2,y,TCOD_BKGND_NONE,TCOD_CENTER,
		"%s : %g/%g", name, value, maxValue);
}

Gui::Message::Message(const char *text, const TCODColor &col) :
	text(strdup(text)),col(col) {
}

Gui::Message::~Message() {
	free(text);
}

void Gui::renderMouseLook() {
	if(! engine.map->isInFov(engine.mouse.cx, engine.mouse.cy)) {
		//si el raton está fuera del fov no hay nada que representar
		return;
	}
	char buf[128]="";
	bool first=true;
	for (Actor **it=engine.actors.begin(); it != engine.actors.end(); it++) {
		Actor *actor=*it;
		// busca actores debajo del cursor del mouse
		if (actor->x == engine.mouse.cx && actor->y == engine.mouse.cy ) {
			if (! first) {
				strcat(buf,", ");
			} else {
				first=false;
			}
			strcat(buf,actor->name);
		}
	}
	// muestra la lista de actores debajo de los cursores del mouse o
	con->setDefaultForeground(TCODColor::lightGrey);
	con->print(1,0,buf);
}

void Gui::message(const TCODColor &col, const char *text, ...) {
	// construye el texto
	va_list ap;
	char buf[128];
	va_start(ap,text);
	vsprintf(buf,text,ap);
	va_end(ap);

	char *lineBegin=buf;
	char *lineEnd;
	do {
		// hace espacio para el nuevo mensaje
		if ( log.size() == MSG_HEIGHT ) {
			Message *toRemove=log.get(0);
			log.remove(toRemove);
			delete toRemove;
		}

		// detecta el final de la linea
		lineEnd=strchr(lineBegin,'\n');
		if ( lineEnd ) {
			*lineEnd='\0';
		}

		// agrega un nuevo mensaje al registro
		Message *msg=new Message(lineBegin, col);
		log.push(msg);

		// ir a la siguiente linea
		lineBegin=lineEnd+1;
	} while ( lineEnd );
}
