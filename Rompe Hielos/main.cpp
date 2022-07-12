///Proyecto Final Juego.
///Materia: Laboratorio en Computación 2.
///Profesor/es: Maximiliano Wenner y Daniel Kloster.
///Integrantes: Pablo Alderete y Facundo Piana Sampietro.
///Nombre del juego: Rompe Hielos.

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <windows.h>

using namespace std;
using namespace sf;

#include "clsSonidos.h"
#include "clsFrutas.h"
#include "clsNumeros.h"
#include "clsBonus.h"
#include "clsPlataforma.h"
#include "clsPlayer.h"
#include "clsPuntajes.h"
#include "clsMenu.h"
#include "clsEnemigos.h"
#include "clsGame.h"

int main(){
    Game j;

    srand(time(NULL));

    j.gameLoop();

    return 0;

}
