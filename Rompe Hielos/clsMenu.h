#ifndef CLSMENU_H_INCLUDED
#define CLSMENU_H_INCLUDED

///CLASE DEL MENU PRINCIPAL
class Menu{
private:
    Sprite *sprite, *hammer;
    Texture *textura, *h;
    bool mover;
    int opciones, cPersonaje=0;
    Clock stop;
    Font *fuente;
    Text *textoJugador, *textoPresionar;

public:
    ///CONSTRUCTOR
    Menu(int tipoMenu);

    ///GETS
    Sprite getSprite(){return *sprite;}
    Sprite getHammer(){return *hammer;}
    int getOpciones(){return opciones;}

    ///SETS
    void setOpciones(int op){opciones=op;}

    ///METODOS
    void hammerMove(int);
    void seleccionarPersonaje(Player *, int, RenderWindow *);

    ///DESTRUCTOR
    ~Menu();
};

///CONSTRUCTOR
Menu::Menu(int tipoMenu){
    h = new Texture;
    h -> loadFromFile("Imagenes/Menu.png");
    IntRect rect(12*4.9,12*10.9,12,12);
    hammer = new Sprite(*h, rect);
    hammer -> setScale(3,3);

    textura = new Texture;

    mover=false;
    opciones=0;

    fuente = new Font();
    fuente -> loadFromFile("Fuentes Tipografia/arcade_ya/ARCADE_N.ttf");

    textoJugador = new Text();
    textoPresionar = new Text();
    textoJugador -> setFont(*fuente);
    textoPresionar -> setFont(*fuente);

    textoJugador -> setPosition(252,10);
    textoPresionar -> setString("PRESIONE 'SHIFT' PARA SELECCIONAR");
    textoPresionar -> setPosition(50, 550);

    textoPresionar -> setScale(0.7,0.7);


    if(tipoMenu==1){
    textura -> loadFromFile("Imagenes/MenuReal.png");
    sprite = new Sprite(*textura);
    sprite -> setScale(3,2.9);
    sprite -> setPosition(-8,-30);

    hammer -> setPosition(190,369);
    }
    else if(tipoMenu==2){
    textura -> loadFromFile("Imagenes/MenuPausa.png");
    sprite = new Sprite(*textura);
    sprite -> setScale(0.315,0.3);
    sprite -> setPosition(-8,-5);

    hammer -> setPosition(190,247);

    }
    else{
    textura -> loadFromFile("Imagenes/MenuPersonajes.png");
    sprite = new Sprite(*textura);
    sprite -> setScale(2,2);
    sprite -> setPosition(0,20);
    }
}

///DESTRUCTOR
Menu::~Menu(){
    delete textura;
    delete sprite;
    delete h;
    delete hammer;
}

///MOVIMIENTO DEL PUNTERO DEL MARTILLO (PARA SELECCIONAR LA OPCION QUE DESEAMOS JUGAR)
void Menu::hammerMove(int tipoMenu){
    if(tipoMenu==1){

        if( Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if (mover==false){
                if (hammer->getPosition().y==369){
                    hammer -> setPosition(190,417);
                }
                mover=true;
            }
            else{
                if (hammer->getPosition().y==417){
                    hammer -> setPosition(190,455);
                }
                mover=false;
            }
        }

        if( Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if (mover==false){
                if (hammer->getPosition().y==455){
                    hammer -> setPosition(190,417);
                }
                mover=true;
            }

            else{
                if (hammer->getPosition().y==417){
                    hammer -> setPosition(190,369);
                }
                mover=false;
            }
        }
    }
    else if(tipoMenu==2){
        if( Keyboard::isKeyPressed(sf::Keyboard::Down)&&mover==false){
            hammer -> setPosition(255,325);
            mover=true;
        }

        if( Keyboard::isKeyPressed(sf::Keyboard::Up)&&mover==true){
            hammer -> setPosition(190,247);
            mover=false;
        }
    }

        if( Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            if(tipoMenu==1){
                if(hammer -> getPosition().y == 369){
                    opciones=1;
                }
                else if(hammer -> getPosition().y == 417){
                    opciones=2;
                }
                else{
                    opciones=3;
                }
            }
            else{
                if(mover==false){
                opciones=1;
                }
                else{
                opciones=2;
                }
            }
        }

}

///MOVIMIENTO MENU PERSONAJES
void Menu::seleccionarPersonaje(Player *jugador, int modo, RenderWindow *ventana1){
   if(modo==1){
    textoJugador -> setString("JUGADOR 1");
   }
   else{
    if(jugador[0].getPersonaje()==0){
        textoJugador -> setString("JUGADOR 1");
    }
    else{
        textoJugador -> setString("JUGADOR 2");
    }
   }


    ventana1->draw(*textoJugador);
    ventana1->draw(*textoPresionar);

    if( Keyboard::isKeyPressed(sf::Keyboard::Right) && stop.getElapsedTime().asMilliseconds()>250){
        if(cPersonaje==5){
            cPersonaje=0;
        }
        else{
            cPersonaje++;
        }
        stop.restart();
    }

    if( Keyboard::isKeyPressed(sf::Keyboard::Left) && stop.getElapsedTime().asMilliseconds()>250){
        if(cPersonaje==0){
            cPersonaje=5;
        }
        else{
            cPersonaje--;
        }
        stop.restart();
    }


        if(cPersonaje==0){
            sprite->setPosition(0,20);
        }
        else if(cPersonaje==1){
            sprite->setPosition(-762,20);
        }
        else if(cPersonaje==2){
            sprite->setPosition(-1524,20);
        }
        else if(cPersonaje==3){
            sprite->setPosition(-2286,20);
        }
        else if(cPersonaje==4){
            sprite->setPosition(-3048,20);
        }
        else if(cPersonaje==5){
            sprite->setPosition(-3810,20);
        }


        if(Keyboard::isKeyPressed(sf::Keyboard::RShift)){
            if(jugador[0].getPersonaje()==0){
                if(cPersonaje==0){
                    jugador[0].setPersonaje(1);
                }
                else if(cPersonaje==1){
                    jugador[0].setPersonaje(2);
                }
                else if(cPersonaje==2){
                    jugador[0].setPersonaje(3);
                }
                else if(cPersonaje==3){
                    jugador[0].setPersonaje(4);
                }
                else if(cPersonaje==4){
                    jugador[0].setPersonaje(5);
                }
                else if(cPersonaje==5){
                    jugador[0].setPersonaje(6);
                }
                stop.restart();
                cPersonaje=0;
            }

            if(modo==2){
                if(jugador[0].getPersonaje()!=0 && jugador[1].getPersonaje()==0 && stop.getElapsedTime().asMilliseconds()>500){
                    if(cPersonaje==0){
                        jugador[1].setPersonaje(1);
                    }
                    else if(cPersonaje==1){
                        jugador[1].setPersonaje(2);
                    }
                    else if(cPersonaje==2){
                        jugador[1].setPersonaje(3);
                    }
                    else if(cPersonaje==3){
                        jugador[1].setPersonaje(4);
                    }
                    else if(cPersonaje==4){
                        jugador[1].setPersonaje(5);
                    }
                    else if(cPersonaje==5){
                        jugador[1].setPersonaje(6);
                    }
                }
            }
        }

}

#endif // CLSMENU_H_INCLUDED
