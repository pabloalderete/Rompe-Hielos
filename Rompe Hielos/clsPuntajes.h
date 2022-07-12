#ifndef CLSPUNTAJES_H_INCLUDED
#define CLSPUNTAJES_H_INCLUDED

///CLASE DEL MENU PUNTAJES
class Puntajes{
private:
    Sprite *sprite, *spriteAnimacion;
    Texture *textura, *texturaAnimacion;
    int puntosFrutas=300, puntosBloques=10, puntosEnemigos=800, puntajeTotal=0, puntajeMaximo=0, puntajePartida=0;
    int cantFrutas=0, cantBloques=0, cantEnemigos=0;
    int cAnimacion[2]={0,0};
    bool acumularPuntaje=false, dibujarP=false, dibujarPM=false;
    int cifrasPuntaje, cifrasCantFrutas, cifrasCantBloques, cifrasPuntajeMaximo, contadorCifras=0;
    Numeros *vCifrasPuntaje, *vCifrasBloques, *vCifrasFrutas, *vCifrasEnemigos, *vCifrasPuntajeMaximo;
    Font *fuente;
    Text *textoBonus, *textoPuntosB;

public:
    ///CONSTRUCTOR
    Puntajes();

    ///GETS
    Sprite getSprite(){return *sprite;}
    int getPtsFrutas(){return puntosFrutas;}
    int getPtsBloques(){return puntosBloques;}
    int getPtsEnemigos(){return puntosEnemigos;}
    int getCantFrutas(){return cantFrutas;}
    int getCantBloques(){return cantBloques;}
    int getCantEnemigos(){return cantEnemigos;}
    int getPuntajeTotal(){return puntajeTotal;}
    int getPuntajeMaximo(){return puntajeMaximo;}
    int getPuntajePartida(){return puntajePartida;}

    ///SETS
    void setPtsFrutas(int pf){puntosFrutas=pf;}
    void setPtsBloques(int pb){puntosBloques=pb;}
    void setPtsEnemigos(int pe){puntosEnemigos=pe;}
    void setPuntajeTotal(int pt){puntajeTotal=pt;}
    void setCantFrutas(int cf){cantFrutas=cf;}
    void setCantBloques(int cb){cantBloques=cb;}
    void setCantEnemigos(int ce){cantEnemigos=ce;}
    void setPuntajeMaximo(int pm){puntajeMaximo=pm;}
    void setPuntajePartida(int pp){puntajePartida=pp;}
    void setAcumularPuntaje(bool ap){acumularPuntaje=ap;}
    void setDibujarPuntaje(bool dp){dibujarP=dp;}
    void setDibujarPuntajeM(bool dpm){dibujarPM=dpm;}

    ///METODOS
    bool grabarPuntaje();
    bool leerPuntaje();
    int contarCifrasPuntaje(int);
    void calcularPuntaje();
    void dibujarPuntaje(RenderWindow *, int);
    void maximoPuntaje(RenderWindow *);
    void seleccionarMenuPuntajes(RenderWindow *, int, Player *, int);
    void animacionPuntajes(RenderWindow *, int, Player *, int);

    ///DESTRUCTOR
    ~Puntajes();
};

///CONSTRUCTOR
Puntajes::Puntajes(){
    textura = new Texture;
    textura -> loadFromFile("Imagenes/MenuReal.png");
    sprite = new Sprite(*textura);
    sprite -> setScale(2.8,2.7);

    texturaAnimacion = new Texture;
    texturaAnimacion -> loadFromFile("Imagenes/Sprites.png");
    spriteAnimacion = new Sprite[2];

    for(int i=0; i<2; i++){
    spriteAnimacion[i].setTexture(*texturaAnimacion);
    spriteAnimacion[i].setScale(3,3);
    }

    fuente = new Font();
    fuente -> loadFromFile("Fuentes Tipografia/arcade_ya/ARCADE_N.ttf");

    textoBonus = new Text[2];
    textoPuntosB = new Text;

    for(int i=0; i<2; i++){
    textoBonus[i].setFont(*fuente);
    textoBonus[i].setScale(0.7,0.7);
    }

    textoPuntosB->setFont(*fuente);
    textoPuntosB->setScale(0.7,0.7);
    textoPuntosB->setString("+2000!");
}

///DESTRUCTOR
Puntajes::~Puntajes(){
    delete textura;
    delete sprite;
    delete texturaAnimacion;
    delete spriteAnimacion;
    delete fuente;
    delete textoBonus;
}

///GUARDA LOS PUNTOS EN EL ARCHIVO
bool Puntajes::grabarPuntaje(){
    FILE *p;
    bool grabo;
    p=fopen ("Puntajes.dat", "wb");
    if (p==NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO :(" << endl;
        return false;
    }

    if(puntajeTotal>puntajeMaximo){
        puntajeMaximo=puntajeTotal;
        grabo=fwrite (&puntajeMaximo, sizeof (int), 1, p);
    }
    else{
        grabo=fwrite (&puntajeMaximo, sizeof (int), 1, p);
    }

    cantBloques=cantFrutas=cantEnemigos=0;

    fclose (p);
    return grabo;
}

///LEE LOS PUNTOS DEL ARCHIVO
bool Puntajes::leerPuntaje(){
    FILE *p;
    bool leyo;
    p=fopen ("Puntajes.dat", "rb");
    if (p==NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO :(" << endl;
        return false;
    }
    leyo=fread (&puntajeMaximo, sizeof (int), 1, p);
    fclose (p);
    return leyo;
}

///CUENTA CUANTAS CIFRAS TIENE EL PUNTAJE
int Puntajes::contarCifrasPuntaje(int numero){
    int cifras=0;
    while(numero!=0){
    numero = numero/10;
    cifras++;
    }

    return cifras;
}

///CALCULA EL PUNTAJE TOTAL EN SI
void Puntajes::calcularPuntaje(){
    if(acumularPuntaje==false){
        puntajePartida=(puntosBloques*cantBloques)+(puntosFrutas*cantFrutas)+(puntosEnemigos*cantEnemigos);
        puntajeTotal+=puntajePartida;
        puntajePartida=0;
        acumularPuntaje=true;
    }

}

///DIBUJA PUNTAJE TOTAL Y CONTADORES DE PUNTOS
void Puntajes::dibujarPuntaje(RenderWindow *ventana1, int posX){

    ///PUNTAJE TOTAL
    if(dibujarP==false){
    int auxPuntaje=puntajeTotal, cifra=puntajeTotal;

    cifrasPuntaje=contarCifrasPuntaje(puntajeTotal);
    vCifrasPuntaje = new Numeros[cifrasPuntaje];

    int acum=(25*cifrasPuntaje)+posX;

    for(int i=cifrasPuntaje-1;i>=0;i--){
        cifra=auxPuntaje%10;
        auxPuntaje=(auxPuntaje-cifra)/10;
        vCifrasPuntaje[i].seleccionNumero(cifra,acum,485);
        acum-=25;
    }

    ///BLOQUES
    int cifraBloques=cantBloques, auxBloques=cantBloques;

    cifrasCantBloques= contarCifrasPuntaje(cantBloques);

    if(cifrasCantBloques>1){
        vCifrasBloques = new Numeros[cifrasCantBloques];

        int acum2=(25*cifrasCantBloques)+(posX+157);

        for(int i=cifrasCantBloques-1;i>=0;i--){
            cifraBloques=auxBloques%10;
            auxBloques=(auxBloques-cifraBloques)/10;
            vCifrasBloques[i].seleccionNumero(cifraBloques,acum2,345);
            acum2-=25;
        }
    }
    else{
        vCifrasBloques = new Numeros;

        vCifrasBloques->seleccionNumero(cifraBloques,(posX+185),345);
        ventana1->draw(vCifrasBloques->getSprite());
    }


    ///FRUTAS

    int cifraFrutas=cantFrutas, auxFrutas=cantFrutas;

    cifrasCantFrutas= contarCifrasPuntaje(cantFrutas);

    if(cifrasCantFrutas>1){
        vCifrasFrutas = new Numeros[cifrasCantFrutas];

        int acum3=(25*cifrasCantFrutas)+(posX+157);

        for(int i=cifrasCantFrutas-1;i>=0;i--){
            cifraFrutas=auxFrutas%10;
            auxFrutas=(auxFrutas-cifraFrutas)/10;
            vCifrasFrutas[i].seleccionNumero(cifraFrutas,acum3,248);
            ventana1->draw(vCifrasFrutas[i].getSprite());
            acum3-=25;
        }
    }
    else{
        vCifrasFrutas = new Numeros;

        vCifrasFrutas->seleccionNumero(cifraFrutas,(posX+182),248);
        ventana1->draw(vCifrasFrutas->getSprite());
    }


    ///ENEMIGOS

    vCifrasEnemigos = new Numeros;

    vCifrasEnemigos->seleccionNumero(cantEnemigos,(posX+182),302);
    ventana1->draw(vCifrasEnemigos->getSprite());

    dibujarP=true;
    }

    for(int i=cifrasPuntaje-1;i>=0;i--){
        ventana1->draw(vCifrasPuntaje[i].getSprite());
    }

    if(cifrasCantBloques>1){
        for(int i=cifrasCantBloques-1;i>=0;i--){
            ventana1->draw(vCifrasBloques[i].getSprite());
        }
    }
    else{
        ventana1->draw(vCifrasBloques->getSprite());
    }

    if(cifrasCantFrutas>1){
        for(int i=cifrasCantFrutas-1;i>=0;i--){
            ventana1->draw(vCifrasFrutas[i].getSprite());
        }
    }
    else{
        ventana1->draw(vCifrasFrutas->getSprite());
    }

    ventana1->draw(vCifrasEnemigos->getSprite());

//    delete vCifrasEnemigos;
//    delete vCifrasBloques;
//    delete vCifrasFrutas;
//    delete vCifrasPuntaje;

}

///DIBUJA EL PUNTAJE MAXIMO EN EL MENU
void Puntajes::maximoPuntaje(RenderWindow *ventana1) {

 if(dibujarPM==false){

 int auxPuntajeMaximo, cifraMaximo;
 bool leyo=false;

 leyo=leerPuntaje();

 if(leyo==true){
    auxPuntajeMaximo=puntajeMaximo;
    cifraMaximo=puntajeMaximo;

    cifrasPuntajeMaximo=contarCifrasPuntaje(puntajeMaximo);
    vCifrasPuntajeMaximo = new Numeros[cifrasPuntajeMaximo];

    int acumMaximo=(25*cifrasPuntajeMaximo)+290;

    for(int i=cifrasPuntajeMaximo-1;i>=0;i--){
        cifraMaximo=auxPuntajeMaximo%10;
        auxPuntajeMaximo=(auxPuntajeMaximo-cifraMaximo)/10;
        vCifrasPuntajeMaximo[i].seleccionNumero(cifraMaximo,acumMaximo,523);
        acumMaximo-=25;
        }
    }
    else{
        vCifrasPuntajeMaximo = new Numeros[5];

        cifrasPuntajeMaximo=5;

        int acumMaximo=(25*5)+300;

        for(int i=4;i>=0;i--){
            vCifrasPuntajeMaximo[i].seleccionNumero(0,acumMaximo,523);
            acumMaximo-=25;
        }
    }
    dibujarPM=true;
    }


    for(int i=cifrasPuntajeMaximo-1;i>=0;i--){
    ventana1->draw(vCifrasPuntajeMaximo[i].getSprite());
    }

}

///SELECCIONA MENU PUNTAJES DEPENDIENDO MODO DE JUEGO Y PERSONAJE
void Puntajes::seleccionarMenuPuntajes(RenderWindow *ventana1, int modo, Player *jugador,  int ganarBonus){

    //POSICIONA MENU PUNTAJE SEGUN EL PERSONAJE
    if(modo==1){
        if(jugador[0].getPersonaje()==1){
        sprite -> setPosition(-720,-40);
        }
        else if(jugador[0].getPersonaje()==2){
        sprite -> setPosition(-1566,-40);
        }
        else if(jugador[0].getPersonaje()==3){
        sprite -> setPosition(-885,-755);
        }
        else if(jugador[0].getPersonaje()==4){
        sprite -> setPosition(-1705,-755);
        }
        else if(jugador[0].getPersonaje()==5){
        sprite -> setPosition(0,-755);
        }
        else if(jugador[0].getPersonaje()==6){
        sprite -> setPosition(-2580,-755);
        }
    }
    else{
        sprite -> setPosition(-2435,-40);
    }

    //ELIGE TEXTO SI GANAMOS O NO EL BONUS
    if(ganarBonus==1){
    textoBonus[0].setString("BONUS!");
    textoBonus[1].setString("SIN BONUS..");
    textoBonus[1].setScale(0.6,0.6);
    }
    else if(ganarBonus==2){
    textoBonus[1].setString("BONUS!");
    textoBonus[0].setString("SIN BONUS..");
    textoBonus[0].setScale(0.6,0.6);
    }
    else{
    textoBonus[0].setString("SIN BONUS..");
    textoBonus[0].setScale(0.6,0.6);
    textoBonus[1].setString("SIN BONUS..");
    textoBonus[1].setScale(0.6,0.6);
    }

    textoBonus[0].setPosition(190,170);

    if(modo==2){
    textoBonus[1].setPosition(500,170);
    }

    for(int i=0; i<2; i++){
        if(jugador[i].getPersonaje()==1){
        textoBonus[i].setColor(Color::Blue);
        }
        else if(jugador[i].getPersonaje()==2){
        textoBonus[i].setColor(Color::Red);
        }
        else if(jugador[i].getPersonaje()==3){
        textoBonus[i].setColor(Color::Yellow);
        }
        else if(jugador[i].getPersonaje()==4){
        textoBonus[i].setColor(Color::Green);
        }
        else if(jugador[i].getPersonaje()==5){
        textoBonus[i].setColor(Color::Magenta);
        }
        else if(jugador[i].getPersonaje()==6){
        textoBonus[i].setColor(Color::Cyan);
        }
    }


    ventana1->draw(*sprite);
    ventana1->draw(textoBonus[0]);
    if(modo==2){
    ventana1 -> draw(textoBonus[1]);
    }

    if(ganarBonus==1){
    textoPuntosB->setPosition(190, 200);
    ventana1 -> draw(*textoPuntosB);
    }
    else if(ganarBonus==2){
    textoPuntosB->setPosition(500, 200);
    ventana1 -> draw(*textoPuntosB);
    }

}

///ANIMACION GANAR O NO BONUS
void Puntajes::animacionPuntajes(RenderWindow *ventana1, int modo, Player *jugador,  int ganarBonus){
    float aux=-1, aux2=0,aux3=0,aux4=0;
    float orientacionAncho=0,orientacionAlto=0;
    Color colorTexto(255, 180, 0);
    textoPuntosB->setColor(colorTexto);


    spriteAnimacion[0].setPosition(105,135);

    if(modo==2){
    spriteAnimacion[1].setPosition(415,135);
    }

    ventana1->setFramerateLimit(10);

    //ANIMACIONES SEGUN PERSONAJE / SEGUN SE GANO O NO EL BONUS
    for(int i=0; i<2; i++){
        if(jugador[i].getPersonaje()==1){


        if(ganarBonus==1){
            if(cAnimacion[i]==0){
                if(i==0){
                orientacionAncho=17;
                aux=21.35;
                orientacionAlto=21;
                aux2=3;
                aux3=18;
                aux4=21;
                }
                else{
                orientacionAncho=15;
                aux=20.26;
                orientacionAlto=21;
                aux2=3;
                aux3=16;
                aux4=21;
                spriteAnimacion[1].setPosition(415,135);
                }
                cAnimacion[i]++;
            }
            else{
                if(i==0){
                orientacionAncho=23;
                aux=16.95;
                orientacionAlto=25;
                aux2=2.44;
                aux3=24;
                aux4=25;
                }
                else{
                orientacionAncho=16;
                aux=20.875;
                orientacionAlto=25;
                aux2=2.44;
                aux3=16;
                aux4=25;
                spriteAnimacion[1].setPosition(415,123);
                }
                cAnimacion[i]=0;
            }
        }
        else if(ganarBonus==2){
            if(cAnimacion[i]==0){
                if(i==0){
                orientacionAncho=15;
                aux=20.26;
                orientacionAlto=21;
                aux2=3;
                aux3=16;
                aux4=21;
                spriteAnimacion[0].setPosition(105,135);
                }
                else{
                orientacionAncho=17;
                aux=21.35;
                orientacionAlto=21;
                aux2=3;
                aux3=18;
                aux4=21;

                }
                cAnimacion[i]++;
            }
            else{
                if(i==0){
                orientacionAncho=16;
                aux=20.875;
                orientacionAlto=25;
                aux2=2.44;
                aux3=16;
                aux4=25;
                spriteAnimacion[0].setPosition(105,123);
                }
                else{
                orientacionAncho=23;
                aux=16.95;
                orientacionAlto=25;
                aux2=2.44;
                aux3=24;
                aux4=25;
                }
                cAnimacion[i]=0;
            }
        }
        else{
            if(cAnimacion[i]==0){
                orientacionAncho=15;
                aux=20.26;
                orientacionAlto=21;
                aux2=3;
                aux3=16;
                aux4=21;
                spriteAnimacion[0].setPosition(105,135);
                spriteAnimacion[1].setPosition(415,135);
                cAnimacion[i]++;
            }
            else{
                orientacionAncho=16;
                aux=20.875;
                orientacionAlto=25;
                aux2=2.44;
                aux3=16;
                aux4=25;
                spriteAnimacion[0].setPosition(105,123);
                spriteAnimacion[1].setPosition(415,123);
                cAnimacion[i]=0;
            }
        }

        }
        else if(jugador[i].getPersonaje()==2){

        if(ganarBonus==1){
            if(cAnimacion[i]==0){
                if(i==0){
                orientacionAncho=17;
        aux=3.7;
        orientacionAlto=21;
        aux2=3;
        aux3=18;
        aux4=21;
                }
                else{
                orientacionAncho=15;
        aux=0.26;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[1].setPosition(415,135);
                }
                cAnimacion[i]++;
            }
            else{
                if(i==0){
                orientacionAncho=23;
        aux=3.91;
        orientacionAlto=25;
        aux2=2.44;
        aux3=24;
        aux4=25;
                }
                else{
               orientacionAncho=16;
        aux=2.125;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[1].setPosition(415,123);
                }
                cAnimacion[i]=0;
            }
        }
        else if(ganarBonus==2){
            if(cAnimacion[i]==0){
                if(i==0){
                orientacionAncho=15;
        aux=0.26;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[0].setPosition(105,135);
                }
                else{
                orientacionAncho=17;
        aux=3.7;
        orientacionAlto=21;
        aux2=3;
        aux3=18;
        aux4=21;

                }
                cAnimacion[i]++;
            }
            else{
                if(i==0){
                orientacionAncho=16;
        aux=2.125;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[0].setPosition(105,123);
                }
                else{
                orientacionAncho=23;
        aux=3.91;
        orientacionAlto=25;
        aux2=2.44;
        aux3=24;
        aux4=25;
                }
                cAnimacion[i]=0;
            }
        }
        else{
            if(cAnimacion[i]==0){
                orientacionAncho=15;
        aux=0.26;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[0].setPosition(105,135);
        spriteAnimacion[1].setPosition(415,135);
                cAnimacion[i]++;
            }
            else{
                orientacionAncho=16;
        aux=2.125;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[0].setPosition(105,123);
        spriteAnimacion[1].setPosition(415,123);
                cAnimacion[i]=0;
            }

        }
        }
        else if(jugador[i].getPersonaje()==3){

            if(ganarBonus==1){
                if(cAnimacion[i]==0){
                    if(i==0){
                    orientacionAncho=17;
                    aux=71.17;
                    orientacionAlto=21;
                    aux2=3;
                    aux3=18;
                    aux4=21;

                    }
                    else{
                    orientacionAncho=15;
                    aux=76.73;
                    orientacionAlto=21;
                    aux2=3;
                    aux3=16;
                    aux4=21;
                    spriteAnimacion[1].setPosition(415,135);
                    }
                    cAnimacion[i]++;
                }
                else{
                    if(i==0){
                    orientacionAncho=23;
        aux=53.78;
        orientacionAlto=25;
        aux2=2.44;
        aux3=24;
        aux4=25;
                    }
                    else{
                    orientacionAncho=16;
        aux=73.8125;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[1].setPosition(415,123);
                    }
                    cAnimacion[i]=0;
                }
            }
            else if(ganarBonus==2){
                if(cAnimacion[i]==0){
                    if(i==0){
                    orientacionAncho=15;
        aux=76.73;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[0].setPosition(105,135);
                    }
                    else{
                    orientacionAncho=17;
        aux=71.17;
        orientacionAlto=21;
        aux2=3;
        aux3=18;
        aux4=21;

                    }
                    cAnimacion[i]++;
                }
                else{
                    if(i==0){
                    orientacionAncho=16;
        aux=73.8125;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[0].setPosition(105,123);
                    }
                    else{
                    orientacionAncho=23;
        aux=53.78;
        orientacionAlto=25;
        aux2=2.44;
        aux3=24;
        aux4=25;
                    }
                    cAnimacion[i]=0;
                }
            }
            else{
                if(cAnimacion[i]==0){
                    orientacionAncho=15;
        aux=76.73;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[0].setPosition(105,135);
        spriteAnimacion[1].setPosition(415,135);

                    cAnimacion[i]++;
                }
                else{
                    orientacionAncho=16;
        aux=73.8125;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[0].setPosition(105,123);
        spriteAnimacion[1].setPosition(415,123);
                    cAnimacion[i]=0;
                }
            }


        }
        else if(jugador[i].getPersonaje()==4){


        if(ganarBonus==1){
                if(cAnimacion[i]==0){
                    if(i==0){
                    orientacionAncho=17;
        aux=53.52;
        orientacionAlto=21;
        aux2=3;
        aux3=18;
        aux4=21;
                    }
                    else{
                    orientacionAncho=15;
        aux=56.73;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[1].setPosition(415,135);
                    }
                    cAnimacion[i]++;
                }
                else{
                    if(i==0){
                    orientacionAncho=23;
        aux=40.73;
        orientacionAlto=25;
        aux2=2.44;
        aux3=24;
        aux4=25;
                    }
                    else{
                    orientacionAncho=16;
        aux=55.0625;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[1].setPosition(415,123);
                    }
                    cAnimacion[i]=0;
                }
            }
            else if(ganarBonus==2){
                if(cAnimacion[i]==0){
                    if(i==0){
                    orientacionAncho=15;
        aux=56.73;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[0].setPosition(105,135);
                    }
                    else{
                    orientacionAncho=17;
        aux=53.52;
        orientacionAlto=21;
        aux2=3;
        aux3=18;
        aux4=21;
                    }
                    cAnimacion[i]++;
                }
                else{
		    if(i==0){
                orientacionAncho=16;
        aux=55.0625;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[0].setPosition(105,123);
                    }
                    else{
                    orientacionAncho=23;
        aux=40.73;
        orientacionAlto=25;
        aux2=2.44;
        aux3=24;
        aux4=25;
                    }
                    cAnimacion[i]=0;
                }
            }
            else{
                if(cAnimacion[i]==0){
                orientacionAncho=15;
        aux=56.73;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[0].setPosition(105,135);
        spriteAnimacion[1].setPosition(415,135);

                    cAnimacion[i]++;
                }
                else{
                orientacionAncho=16;
        aux=55.0625;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[0].setPosition(105,123);
        spriteAnimacion[1].setPosition(415,123);
                    cAnimacion[i]=0;
                }
            }


        }
        else if(jugador[i].getPersonaje()==5){

            if(ganarBonus==1){
                if(cAnimacion[i]==0){
                    if(i==0){
                    orientacionAncho=17;
        aux=46.23;
        orientacionAlto=21;
        aux2=3;
        aux3=18;
        aux4=21;
                    }
                    else{
                    orientacionAncho=15;
        aux=48.46;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[1].setPosition(415,135);
                    }
                    cAnimacion[i]++;
                }
                else{
                    if(i==0){
                    orientacionAncho=23;
        aux=35.34;
        orientacionAlto=25;
        aux2=2.44;
        aux3=24;
        aux4=25;
                    }
                    else{
                    orientacionAncho=16;
        aux=47.3125;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[1].setPosition(415,123);
                    }
                    cAnimacion[i]=0;
                }
            }
            else if(ganarBonus==2){
                if(cAnimacion[i]==0){
                    if(i==0){
                    orientacionAncho=15;
        aux=48.46;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[0].setPosition(105,135);
                    }
                    else{
                    orientacionAncho=17;
        aux=46.23;
        orientacionAlto=21;
        aux2=3;
        aux3=18;
        aux4=21;
                    }
                    cAnimacion[i]++;
                }
                else{
                    if(i==0){
                    orientacionAncho=16;
        aux=47.3125;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[0].setPosition(105,123);
                    }
                    else{
                    orientacionAncho=23;
        aux=35.34;
        orientacionAlto=25;
        aux2=2.44;
        aux3=24;
        aux4=25;
                    }
                    cAnimacion[i]=0;
                }
            }
            else{
                if(cAnimacion[i]==0){
                    orientacionAncho=15;
        aux=48.46;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[0].setPosition(105,135);
        spriteAnimacion[1].setPosition(415,135);
                    cAnimacion[i]++;
                }
                else{
                    orientacionAncho=16;
        aux=47.3125;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[0].setPosition(105,123);
        spriteAnimacion[1].setPosition(415,123);
                    cAnimacion[i]=0;
                }
            }

        }
        else if(jugador[i].getPersonaje()==6){

            if(ganarBonus==1){
                if(cAnimacion[i]==0){
                    if(i==0){
                    orientacionAncho=17;
        aux=28.58;
        orientacionAlto=21;
        aux2=3;
        aux3=18;
        aux4=21;
                    }
                    else{
                    orientacionAncho=15;
        aux=28.46;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[1].setPosition(415,135);
                    }
                    cAnimacion[i]++;
                }
                else{
		    if(i==0){
                    orientacionAncho=23;
        aux=22.30;
        orientacionAlto=25;
        aux2=2.44;
        aux3=24;
        aux4=25;
                    }
                    else{
                    orientacionAncho=16;
        aux=28.5625;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[1].setPosition(415,123);
                    }
                    cAnimacion[i]=0;
                }
            }
            else if(ganarBonus==2){
                if(cAnimacion[i]==0){
                    if(i==0){
                    orientacionAncho=15;
        aux=28.46;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[0].setPosition(105,135);
                    }
                    else{
                    orientacionAncho=17;
        aux=28.58;
        orientacionAlto=21;
        aux2=3;
        aux3=18;
        aux4=21;
                    }
                    cAnimacion[i]++;
                }
                else{
                    if(i==0){
                    orientacionAncho=16;
        aux=28.5625;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[0].setPosition(105,123);
                    }
                    else{
                    orientacionAncho=23;
        aux=22.30;
        orientacionAlto=25;
        aux2=2.44;
        aux3=24;
        aux4=25;
                    }
                    cAnimacion[i]=0;
                }
            }
            else{
                if(cAnimacion[i]==0){
                    orientacionAncho=15;
        aux=28.46;
        orientacionAlto=21;
        aux2=3;
        aux3=16;
        aux4=21;
        spriteAnimacion[0].setPosition(105,135);
        spriteAnimacion[1].setPosition(415,135);
                    cAnimacion[i]++;
                }
                else{
                    orientacionAncho=16;
        aux=28.5625;
        orientacionAlto=25;
        aux2=2.44;
        aux3=16;
        aux4=25;
        spriteAnimacion[0].setPosition(105,123);
        spriteAnimacion[1].setPosition(415,123);
                    cAnimacion[i]=0;
                }
            }
        }

    IntRect rect(orientacionAncho*aux,orientacionAlto*aux2,aux3,aux4);
    spriteAnimacion[i].setTextureRect(rect);
    }

    ventana1 -> draw(spriteAnimacion[0]);

    if(modo==2){
    ventana1 -> draw(spriteAnimacion[1]);
    }

}

#endif // CLSPUNTAJES_H_INCLUDED
