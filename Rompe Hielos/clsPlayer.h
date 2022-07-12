#ifndef CLSPLAYER_H_INCLUDED
#define CLSPLAYER_H_INCLUDED

///CLASE JUGADOR 1 Y 2
class Player {

  private:
    Texture *textura1;
    Sprite *sprite1, *spriteVida;
    int pressL, pressR, cAnimacion, ground, vidas, ADSX, ADSY, pVidasY=10, tipo, personaje=0;
    Vector2f velocidad;
    bool isGrounded, direccion, hit, murio, renacio, dibujaPlayer, ADS, estadoVida[3], modo, posicionJugador=false;
    Plataforma *base;
    const int PISOS_JUGADOR[7]={515,385,240,80,-60,-190,-320};
    Clock reloj;
    bool rompio, dibujoVidas=false, estado=true, seguir[3]={false,false,false}, direcNube;
    Sonidos efectos;

  public:
    ///CONSTRUCTOR
    Player();

    ///GETS
    Sprite getSprite() {return *sprite1;}
    Sprite getSpriteVida(int x){return spriteVida[x];}
    bool getIsGrounded() {return isGrounded;}
    int getVelocidadY() {return velocidad.y;}
    int getGround() {return ground;}
    bool getHit(){return hit;}
    bool getDireccion(){return direccion;}
    bool getMurio(){return murio;}
    int getVidas(){return vidas;}
    bool getRenacio(){return renacio;}
    bool getDibujaPlayer(){return dibujaPlayer;}
    bool getEstadoVida(int x){return estadoVida[x];}
    int getPISOS_JUGADOR(int i){return PISOS_JUGADOR[i];}
    int getPVidasY(){return pVidasY;}
    bool getModo(){return modo;}
    bool getRompio(){return rompio;}
    bool getEstado(){return estado;}
    int getPersonaje(){return personaje;}

    ///SETS
    void setIsGrounded(bool ground) {isGrounded=ground;}
    void setVelocidad(int vx, int vy) {
        velocidad.x=vx;
        velocidad.y=vy;
    }
    void setPVidasY(int pVidas){pVidasY=pVidas;}
    void setRenacio(bool r){renacio=r;}
    void setVelocidadEntera(Vector2f v) {velocidad=v;}
    void setGround (int g) {ground=g;}
    void setMurio(bool m){murio=m;}
    void setVidas(int v){vidas=v;}
    void setDibujaPlayer(int d){dibujaPlayer=d;}
    void setEstadoVida(int x,bool ev){estadoVida[x]=ev;}
    void setRompio(bool r){rompio=r;}
    void setDibujoVidas(bool dv){dibujoVidas=dv;}
    void setEstado(bool e){estado=e;}
    void setSeguir(int i,bool s){seguir[i]=s;}
    void setDirecNube(bool d){direcNube=d;}
    void setPersonaje(int p){personaje=p;}

    ///METODOS
    void mover(int, bool);
    void update(int, bool);
    void morir();
    void posicionarVidas(int, int, int *);

    ///DESTRUCTOR
    ~Player();
};

///CONSTRUCTOR
Player::Player() {

    //JUGADOR
    base=new Plataforma;
    textura1=new Texture;
    murio=false;
    dibujaPlayer=true;
    vidas=3;
    isGrounded=true;
    cAnimacion=0;
    velocidad.x = 0;
    velocidad.y = 0;
    textura1->loadFromFile("Imagenes/Sprites.png");
    sprite1=new Sprite(*textura1);
    ground=515;
    sprite1->setScale(2.5,2.5);
    renacio=false;
    ADSY=515;
    ADS=false;
    rompio=false;
    spriteVida = new Sprite[3];

    //CONTADORES PARA ANIMACIONES
    pressL=0;
    pressR=0;

    //GOLPE
    hit=0;
}

///DESTRUCTOR
Player::~Player() {
    delete textura1;
    delete sprite1;
    delete spriteVida;
}

///MOVIMIENTO DEL JUGADOR
void Player::mover(int jugador, bool modo) {
    float aux=-1, aux2=0,aux3=0,aux4=0;
    float orientacionAncho=0,orientacionAlto=0;
    const float Gravity=4;
    float moveSpeed=10.0f, jumpSpeed=40.0;

    ///MOVERSE CON LA NUBE
    for (int i=0;i<3;i++){
        if (seguir[i]==true){
            if (direcNube==true){
                sprite1->move(5,0);
            }
            else if (direcNube==false){
                sprite1->move(-5,0);
            }
        }
    }

    tipo=jugador;

    switch (tipo){

    ///JUGADOR 1///
    case 1:

    if(modo==false && posicionJugador==false){
        sprite1->setPosition(360,ground);
        posicionJugador=true;
    }
    else if(modo==true && posicionJugador==false){
        sprite1->setPosition(180,ground);
        posicionJugador=true;
    }

       ///SI MURIO CAE CON LA ANIMACION DE MUERTE
    if (murio==true){
        moveSpeed=0;
        jumpSpeed=10.0;
        velocidad.x=moveSpeed;
        velocidad.y=jumpSpeed;
        if (cAnimacion==0 || cAnimacion==1){
            orientacionAncho=18;
            aux=8.5;
            orientacionAlto=23;
            aux2=2.7;
            aux3=18;
            aux4=23;
            cAnimacion++;
        }

        else if (cAnimacion==1 || cAnimacion==2){
            orientacionAncho=18;
            aux=10.2;
            orientacionAlto=23;
            aux2=2.7;
            aux3=18;
            aux4=23;
            cAnimacion++;
        }

       else if (cAnimacion==3 || cAnimacion==4){
            orientacionAncho=18;
            aux=11.8;
            orientacionAlto=23;
            aux2=2.7;
            aux3=19;
            aux4=23;
            cAnimacion++;
        }

        else if (cAnimacion==5){
            orientacionAncho=18;
            aux=13.5;
            orientacionAlto=23;
            aux2=2.7;
            aux3=18;
            aux4=23;
            cAnimacion=0;
        }

    }
    else if (murio==false){

    ///SALTO
    if( Keyboard::isKeyPressed(sf::Keyboard::W) && isGrounded==true&&hit==false) {
        if(estado==true){
        efectos.seleccionarEfecto(5);
        }
        if (ADS==false){
            ADS=true;
            ADSX=sprite1->getPosition().x;
            ADSY=ground;

        }
        //SE FIJA HACIA QUE LADO MIRA CON "DIRECCION"
        if(direccion==false) {
            if(personaje==1){
                orientacionAncho=22;
                aux=2.8;
                orientacionAlto=23;
                aux2=0.1;
                aux3=22;
                aux4=23;
            }
            else if(personaje==2){
                orientacionAncho=22;
                aux=2.8;
                orientacionAlto=23;
                aux2=4;
                aux3=22;
                aux4=23;
            }
            else if(personaje==3){
                orientacionAncho=22;
                aux=41.3;
                orientacionAlto=23;
                aux2=0.1;
                aux3=22;
                aux4=23;
            }
            else if(personaje==4){
                orientacionAncho=22;
                aux=41.3;
                orientacionAlto=23;
                aux2=4;
                aux3=22;
                aux4=23;
            }
            else if(personaje==5){
                orientacionAncho=22;
                aux=22;
                orientacionAlto=23;
                aux2=0.1;
                aux3=22;
                aux4=23;
            }
            else if(personaje==6){
                orientacionAncho=22;
                aux=22;
                orientacionAlto=23;
                aux2=4;
                aux3=22;
                aux4=23;
            }


            velocidad.y=-jumpSpeed;
            sprite1->setPosition(sprite1->getPosition().x ,sprite1->getPosition().y-1);
            isGrounded=false;
        }
        else {
            if(personaje==1){
            orientacionAncho=22;
            aux=15;
            orientacionAlto=23;
            aux2=0.1;
            aux3=23;
            aux4=23;
            }
            else if(personaje==2){
                orientacionAncho=22;
                aux=15;
                orientacionAlto=23;
                aux2=4;
                aux3=23;
                aux4=23;
            }
            else if(personaje==3){
                orientacionAncho=22;
                aux=53.54;
                orientacionAlto=23;
                aux2=0.1;
                aux3=23;
                aux4=23;
            }
            else if(personaje==4){
                orientacionAncho=22;
                aux=53.54;
                orientacionAlto=23;
                aux2=4;
                aux3=23;
                aux4=23;
            }
            else if(personaje==5){
                orientacionAncho=22;
                aux=34.27;
                orientacionAlto=23;
                aux2=0.1;
                aux3=23;
                aux4=23;
            }
            else if(personaje==6){
                orientacionAncho=22;
                aux=34.27;
                orientacionAlto=23;
                aux2=4;
                aux3=23;
                aux4=23;
            }
            velocidad.y=-jumpSpeed;
            sprite1->setPosition(sprite1->getPosition().x ,sprite1->getPosition().y-1);
            isGrounded=false;
        }


    }

    ///CAMINAR HACIA IZQUIERDA
    if(Keyboard::isKeyPressed(sf::Keyboard::A)&&hit==false) {
        if(isGrounded==false) {
            moveSpeed=5.0f;
        } else {
            moveSpeed=10.0f;
        }
        direccion=false;
        velocidad.x=-moveSpeed;

        if(isGrounded==true) {
            if(pressL==0 || pressL==1) {
                if(personaje==1){
                orientacionAncho=15;
                aux=10.33;
                orientacionAlto=21;
                aux2=0.1;
                aux3=15;
                aux4=22;
                }
                else if(personaje==2){
                orientacionAncho=15;
                aux=10.33;
                orientacionAlto=21;
                aux2=4.4;
                aux3=15;
                aux4=22;
                }
                else if(personaje==3){
                orientacionAncho=15;
                aux=66.73;
                orientacionAlto=21;
                aux2=0.1;
                aux3=16;
                aux4=22;
                }
                else if(personaje==4){
                orientacionAncho=15;
                aux=66.73;
                orientacionAlto=21;
                aux2=4.4;
                aux3=16;
                aux4=22;
                }
                else if(personaje==5){
                orientacionAncho=15;
                aux=38.46;
                orientacionAlto=21;
                aux2=0.1;
                aux3=16;
                aux4=22;
                }
                else if(personaje==6){
                orientacionAncho=15;
                aux=38.46;
                orientacionAlto=21;
                aux2=4.4;
                aux3=15;
                aux4=22;
                }
                pressL++;
            }
            else if(pressL==2 || pressL==3) {
                if(personaje==1){
                orientacionAncho=14;
                aux=8.9;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==2){
                        orientacionAncho=14;
                aux=8.9;
                orientacionAlto=22;
                aux2=4.22;
                aux3=15;
                aux4=23;
                }
                else if(personaje==3){
                orientacionAncho=14;
                aux=69.42;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==4){
                orientacionAncho=14;
                aux=69.42;
                orientacionAlto=22;
                aux2=4.22;
                aux3=15;
                aux4=23;
                }
                else if(personaje==5){
                orientacionAncho=14;
                aux=39.14;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==6){
                orientacionAncho=14;
                aux=39.14;
                orientacionAlto=22;
                aux2=4.22;
                aux3=15;
                aux4=23;
                }
                pressL++;
            }
            else {
                if(personaje==1){
                orientacionAncho=16;
                aux=5.9;
                orientacionAlto=22;
                aux2=0.1;
                aux3=16;
                aux4=23;
                }
                else if(personaje==2){
                orientacionAncho=16;
                aux=5.9;
                orientacionAlto=22;
                aux2=4.22;
                aux3=16;
                aux4=23;
                }
                else if(personaje==3){
                orientacionAncho=16;
                aux=58.8125;
                orientacionAlto=22;
                aux2=0.1;
                aux3=16;
                aux4=23;
                }
                else if(personaje==4){
                orientacionAncho=16;
                aux=58.8125;
                orientacionAlto=22;
                aux2=4.22;
                aux3=16;
                aux4=23;
                }
                else if(personaje==5){
                orientacionAncho=16;
                aux=32.3125;
                orientacionAlto=22;
                aux2=0.1;
                aux3=16;
                aux4=23;
                }
                else if(personaje==6){
                orientacionAncho=16;
                aux=32.3125;
                orientacionAlto=22;
                aux2=4.22;
                aux3=16;
                aux4=23;
                }
                pressL=0;
            }
        }
        else {
            velocidad.x=-5;
        }
    }

    ///CAMINAR HACIA DERECHA
    else if(Keyboard::isKeyPressed(sf::Keyboard::D)&&hit==false) {
        if(isGrounded==false) {
            moveSpeed=5.0f;
        }
        else {
            moveSpeed=10.0f;
        }
        direccion=true;
        velocidad.x=moveSpeed;

        if(isGrounded==true) {
            if(pressR==0 || pressR==1) {
                if(personaje==1){
                orientacionAncho=15;
                aux=16.4;
                orientacionAlto=21;
                aux2=0.1;
                aux3=15;
                aux4=22;
                }
                else if(personaje==2){
                orientacionAncho=15;
                aux=16.4;
                orientacionAlto=21;
                aux2=4.4;
                aux3=15;
                aux4=22;
                }
                else if(personaje==3){
                orientacionAncho=15;
                aux=72.8;
                orientacionAlto=21;
                aux2=0.1;
                aux3=16;
                aux4=22;
                }
                else if(personaje==4){
                orientacionAncho=15;
                aux=72.8;
                orientacionAlto=21;
                aux2=4.4;
                aux3=16;
                aux4=22;
                }
                else if(personaje==5){
                orientacionAncho=15;
                aux=44.53;
                orientacionAlto=21;
                aux2=0.1;
                aux3=16;
                aux4=22;
                }
                else if(personaje==6){
                orientacionAncho=15;
                aux=44.53;
                orientacionAlto=21;
                aux2=4.4;
                aux3=15;
                aux4=22;
                }
                pressR++;
            }
            else if(pressR==2 || pressR==3) {
                if(personaje==1){
                orientacionAncho=14;
                aux=19.7;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==2){
                orientacionAncho=14;
                aux=19.7;
                orientacionAlto=22;
                aux2=4.22;
                aux3=15;
                aux4=23;
                }
                else if(personaje==3){
                orientacionAncho=14;
                aux=80.14;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==4){
                orientacionAncho=14;
                aux=80.14;
                orientacionAlto=22;
                aux2=4.22;
                aux3=15;
                aux4=23;
                }
                else if(personaje==5){
                orientacionAncho=14;
                aux=49.85;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==6){
                orientacionAncho=14;
                aux=49.85;
                orientacionAlto=22;
                aux2=4.22;
                aux3=15;
                aux4=23;
                }
                pressR++;
            }
            else {
                if(personaje==1){
                orientacionAncho=16;
                aux=19;
                orientacionAlto=22;
                aux2=0.1;
                aux3=16;
                aux4=23;
                }
                else if(personaje==2){
                orientacionAncho=16;
                aux=19;
                orientacionAlto=22;
                aux2=4.22;
                aux3=16;
                aux4=23;
                }
                else if(personaje==3){
                orientacionAncho=16;
                aux=71.9375;
                orientacionAlto=22;
                aux2=0.1;
                aux3=16;
                aux4=23;
                }
                else if(personaje==4){
                orientacionAncho=16;
                aux=71.9375;
                orientacionAlto=22;
                aux2=4.22;
                aux3=16;
                aux4=23;
                }
                else if(personaje==5){
                orientacionAncho=14;
                aux=49.85;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==6){
                orientacionAncho=16;
                aux=45.4375;
                orientacionAlto=22;
                aux2=4.22;
                aux3=16;
                aux4=23;
                }
                pressR=0;
            }
        }
        else {
            velocidad.x=5;
        }
    }

    else {

        velocidad.x=0;
    }


    ///GOLPEAR
    if(Keyboard::isKeyPressed(sf::Keyboard::Space)&&hit==false&&isGrounded==true) {
        if(isGrounded==true) {
            if(direccion==false) {
                reloj.restart();

                if(personaje==1){
                orientacionAncho=23;
                aux=0;
                orientacionAlto=26;
                aux2=0;
                aux3=23;
                aux4=27;
                }
                else if(personaje==2){
                orientacionAncho=23;
                aux=0;
                orientacionAlto=26;
                aux2=3.5;
                aux3=23;
                aux4=27;

                }
                else if(personaje==3){
                orientacionAncho=23;
                aux=36.82;
                orientacionAlto=26;
                aux2=0;
                aux3=24;
                aux4=27;
                }
                else if(personaje==4){
                orientacionAncho=23;
                aux=36.82;
                orientacionAlto=26;
                aux2=3.5;
                aux3=24;
                aux4=27;
                }
                else if(personaje==5){
                orientacionAncho=23;
                aux=18.39;
                orientacionAlto=26;
                aux2=0;
                aux3=23;
                aux4=27;
                }
                else if(personaje==6){
                orientacionAncho=23;
                aux=18.39;
                orientacionAlto=26;
                aux2=3.5;
                aux3=24;
                aux4=27;
                }

            }
            else {
                reloj.restart();

                velocidad.y+=Gravity;
                if(personaje==1){
                orientacionAncho=23;
                aux=17;
                orientacionAlto=26;
                aux2=0;
                aux3=23;
                aux4=27;
                }
                else if(personaje==2){
                orientacionAncho=23;
                aux=17;
                orientacionAlto=26;
                aux2=3.5;
                aux3=23;
                aux4=27;

                }
                else if(personaje==3){
                orientacionAncho=23;
                aux=53.82;
                orientacionAlto=26;
                aux2=0;
                aux3=24;
                aux4=27;
                }
                else if(personaje==4){
                orientacionAncho=23;
                aux=53.82;
                orientacionAlto=26;
                aux2=3.5;
                aux3=24;
                aux4=27;
                }
                else if(personaje==5){
                orientacionAncho=23;
                aux=35.39;
                orientacionAlto=26;
                aux2=0;
                aux3=23;
                aux4=27;
                }
                else if(personaje==6){
                orientacionAncho=23;
                aux=35.39;
                orientacionAlto=26;
                aux2=3.5;
                aux3=24;
                aux4=27;
                }
            }
        }
        hit=true;
    }


    ///PASAJE DEL BORDE DE LA PANTALLA HACIA EL OTRO EXTREMO
    if(sprite1->getPosition().x   > 750)
        sprite1->setPosition(1,sprite1 -> getPosition().y);
    if(sprite1->getPosition().x  < 1)
        sprite1->setPosition(750,sprite1 -> getPosition().y);

//    if(sprite1->getPosition().y+velocidad.y<ground-100&&isGrounded==false&&(sprite1->getPosition().x + velocidad.x+30>-10&&sprite1->getPosition().x+velocidad.x+29<100))velocidad.y=0;
//
//    if(sprite1->getPosition().y+velocidad.y<ground-100&&isGrounded==false&&(sprite1->getPosition().x + velocidad.x+30<810&&sprite1->getPosition().x+velocidad.x+29>710))velocidad.y=0;

    if( sprite1->getPosition().y + velocidad.y  > ground)
        velocidad.y=0;

    ///CAIDA AL SALTAR
    if (sprite1->getPosition().y < ground) {
        isGrounded=false;
        if(direccion==false) {
            velocidad.y+=Gravity;
            if(personaje==1){
            orientacionAncho=17;
            aux=1.9;
            orientacionAlto=27;
            aux2=0;
            aux3=18;
            aux4=27;
            }
            else if(personaje==2){
            orientacionAncho=17;
            aux=1.9;
            orientacionAlto=27;
            aux2=3.35;
            aux3=18;
            aux4=27;
            }
            else if(personaje==3){
            orientacionAncho=17;
            aux=51.76;
            orientacionAlto=27;
            aux2=0;
            aux3=18;
            aux4=27;
            }
            else if(personaje==4){
            orientacionAncho=17;
            aux=51.76;
            orientacionAlto=27;
            aux2=3.35;
            aux3=18;
            aux4=27;
            }
            else if(personaje==5){
            orientacionAncho=17;
            aux=26.82;
            orientacionAlto=27;
            aux2=0;
            aux3=18;
            aux4=27;
            }
            else if(personaje==6){
            orientacionAncho=17;
            aux=26.82;
            orientacionAlto=27;
            aux2=3.35;
            aux3=18;
            aux4=27;
            }
        }
        else {
            velocidad.y+=Gravity;
            if(personaje==1){
            orientacionAncho=17;
            aux=21.4;
            orientacionAlto=27;
            aux2=0;
            aux3=18;
            aux4=27;
            }
            else if(personaje==2){
            orientacionAncho=17;
            aux=21.4;
            orientacionAlto=27;
            aux2=3.35;
            aux3=18;
            aux4=27;
            }
            else if(personaje==3){
            orientacionAncho=17;
            aux=71.23;
            orientacionAlto=27;
            aux2=0;
            aux3=18;
            aux4=27;
            }
            else if(personaje==4){
            orientacionAncho=17;
            aux=71.23;
            orientacionAlto=27;
            aux2=3.35;
            aux3=18;
            aux4=27;
            }
            else if(personaje==5){
            orientacionAncho=17;
            aux=46.294;
            orientacionAlto=27;
            aux2=0;
            aux3=18;
            aux4=27;
            }
            else if(personaje==6){
            orientacionAncho=17;
            aux=46.294;
            orientacionAlto=27;
            aux2=3.35;
            aux3=18;
            aux4=27;
            }
        }
    }
    else {

        //AL CAER SOBRE UNA PLATAFORMA, SETEA EL NUEVO PISO
        sprite1->setPosition(sprite1 ->getPosition().x, ground);
        isGrounded=true;
        ADS=false;



    }
}

    //MUEVE CON SUS RESPECTIVAS VELOCIDADES
   // irrompibles();
    sprite1->move(velocidad.x,velocidad.y);


    ///ANIMACIONES AL ESTAR QUIETO
    if(aux==-1 && direccion==true) {
        if(personaje==1){
        orientacionAncho=14;
        aux=15.4;
        orientacionAlto=22;
        aux2=0.1;
        aux3=15;
        aux4=23;
        }
        else if(personaje==2){
        orientacionAncho=14;
        aux=15.4;
        orientacionAlto=22;
        aux2=4.22;
        aux3=15;
        aux4=23;
        }
        else if(personaje==3){
        orientacionAncho=14;
        aux=75.85;
        orientacionAlto=22;
        aux2=0.1;
        aux3=15;
        aux4=23;
        }
        else if(personaje==4){
        orientacionAncho=14;
        aux=75.85;
        orientacionAlto=22;
        aux2=4.22;
        aux3=15;
        aux4=23;
        }
        else if(personaje==5){
        orientacionAncho=14;
        aux=45.57;
        orientacionAlto=22;
        aux2=0.1;
        aux3=15;
        aux4=23;
        }
        else if(personaje==6){
        orientacionAncho=14;
        aux=45.57;
        orientacionAlto=22;
        aux2=4.22;
        aux3=15;
        aux4=23;

        }
    }
    if(aux==-1 && direccion==false) {
        if(personaje==1){
            orientacionAncho=14;
            aux=13.2;
            orientacionAlto=22;
            aux2=0.1;
            aux3=15;
            aux4=23;
        }
        else if(personaje==2){
            orientacionAncho=14;
        aux=13.2;
        orientacionAlto=22;
        aux2=4.22;
        aux3=15;
        aux4=23;
        }
        else if(personaje==3){
            orientacionAncho=14;
        aux=73.71;
        orientacionAlto=22;
        aux2=0.1;
        aux3=15;
        aux4=23;
        }
        else if(personaje==4){
            orientacionAncho=14;
        aux=73.71;
        orientacionAlto=22;
        aux2=4.22;
        aux3=15;
        aux4=23;
        }
        else if(personaje==5){
            orientacionAncho=14;
        aux=43.42;
        orientacionAlto=22;
        aux2=0.1;
        aux3=15;
        aux4=23;
        }
        else if(personaje==6){
            orientacionAncho=14;
        aux=43.42;
        orientacionAlto=22;
        aux2=4.22;
        aux3=15;
        aux4=23;
        }
    }

    ///ANIMACIONES GOLPE
    if(hit==true) {
        if(reloj.getElapsedTime().asMilliseconds()>20 && reloj.getElapsedTime().asMilliseconds()<200) {
            if(direccion==false) {
                if(personaje==1){
                orientacionAncho=23;
                aux=0;
                orientacionAlto=27;
                aux2=1.1;
                aux3=23;
                aux4=28;
                }
                else if(personaje==2){
                orientacionAncho=23;
                aux=0;
                orientacionAlto=27;
                aux2=4.44;
                aux3=23;
                aux4=28;
                }
                else if(personaje==3){
                orientacionAncho=23;
                aux=36.82;
                orientacionAlto=27;
                aux2=1.1;
                aux3=24;
                aux4=28;
                }
                else if(personaje==4){
                orientacionAncho=23;
                aux=36.82;
                orientacionAlto=27;
                aux2=4.44;
                aux3=24;
                aux4=28;
                }
                else if(personaje==5){
                orientacionAncho=23;
                aux=18.39;
                orientacionAlto=27;
                aux2=1.1;
                aux3=23;
                aux4=28;
                }
                else if(personaje==6){
                orientacionAncho=23;
                aux=18.39;
                orientacionAlto=27;
                aux2=4.44;
                aux3=24;
                aux4=28;
                }
            }
            else {
                if(personaje==1){
                orientacionAncho=23;
                aux=17;
                orientacionAlto=27;
                aux2=1.1;
                aux3=23;
                aux4=28;
                }
                else if(personaje==2){
                orientacionAncho=23;
                aux=17;
                orientacionAlto=27;
                aux2=4.44;
                aux3=23;
                aux4=28;
                }
                else if(personaje==3){
                orientacionAncho=23;
                aux=53.82;
                orientacionAlto=27;
                aux2=1.1;
                aux3=24;
                aux4=28;
                }
                else if(personaje==4){
                orientacionAncho=23;
                aux=53.82;
                orientacionAlto=27;
                aux2=4.44;
                aux3=24;
                aux4=28;
                }
                else if(personaje==5){
                orientacionAncho=23;
                aux=35.39;
                orientacionAlto=27;
                aux2=1.1;
                aux3=23;
                aux4=28;
                }
                else if(personaje==6){
                orientacionAncho=23;
                aux=35.39;
                orientacionAlto=27;
                aux2=4.44;
                aux3=24;
                aux4=28;
                }
            }
        }
        if(reloj.getElapsedTime().asMilliseconds()>200) {
                hit=false;
        }

    }


        break;

    ///JUGADOR 2///
    case 2:

        if(modo==false && posicionJugador==false){
            sprite1->setPosition(360,ground);
            posicionJugador=true;
        }
        else if(modo==true && posicionJugador==false){
            sprite1->setPosition(540,ground);
            posicionJugador=true;
        }

        ///SI MURIO CAE CON LA ANIMACION DE MUERTE
    if (murio==true){
        moveSpeed=0;
        jumpSpeed=10.0;
        velocidad.x=moveSpeed;
        velocidad.y=jumpSpeed;
        if (cAnimacion==0){
            orientacionAncho=18;
            aux=8.5;
            orientacionAlto=23;
            aux2=2.7;
            aux3=18;
            aux4=23;
            cAnimacion++;
        }

        else if (cAnimacion==1){
            orientacionAncho=18;
            aux=10.2;
            orientacionAlto=23;
            aux2=2.7;
            aux3=18;
            aux4=23;
            cAnimacion++;
        }

       else if (cAnimacion==2){
            orientacionAncho=18;
            aux=11.8;
            orientacionAlto=23;
            aux2=2.7;
            aux3=19;
            aux4=23;
            cAnimacion++;
        }

        else if (cAnimacion==3){
            orientacionAncho=18;
            aux=13.5;
            orientacionAlto=23;
            aux2=2.7;
            aux3=18;
            aux4=23;
            cAnimacion=0;
        }

    }
    else if (murio==false){

    ///SALTO
    if( Keyboard::isKeyPressed(sf::Keyboard::Up) && isGrounded==true&&hit==false) {
        if(estado==true){
        efectos.seleccionarEfecto(5);
        }
        if (ADS==false){
            ADS=true;
            ADSX=sprite1->getPosition().x;
            ADSY=ground;

        }
        //SE FIJA HACIA QUE LADO MIRA CON "DIRECCION"
        if(direccion==false) {
            if(personaje==1){
                orientacionAncho=22;
                aux=2.8;
                orientacionAlto=23;
                aux2=0.1;
                aux3=22;
                aux4=23;
            }
            else if(personaje==2){
                orientacionAncho=22;
                aux=2.8;
                orientacionAlto=23;
                aux2=4;
                aux3=22;
                aux4=23;
            }
            else if(personaje==3){
                orientacionAncho=22;
                aux=41.3;
                orientacionAlto=23;
                aux2=0.1;
                aux3=22;
                aux4=23;
            }
            else if(personaje==4){
                orientacionAncho=22;
                aux=41.3;
                orientacionAlto=23;
                aux2=4;
                aux3=22;
                aux4=23;
            }
            else if(personaje==5){
                orientacionAncho=22;
                aux=22;
                orientacionAlto=23;
                aux2=0.1;
                aux3=22;
                aux4=23;
            }
            else if(personaje==6){
                orientacionAncho=22;
                aux=22;
                orientacionAlto=23;
                aux2=4;
                aux3=22;
                aux4=23;
            }


            velocidad.y=-jumpSpeed;
            sprite1->setPosition(sprite1->getPosition().x ,sprite1->getPosition().y-1);
            isGrounded=false;
        }
        else {
            if(personaje==1){
            orientacionAncho=22;
            aux=15;
            orientacionAlto=23;
            aux2=0.1;
            aux3=23;
            aux4=23;
            }
            else if(personaje==2){
                orientacionAncho=22;
                aux=15;
                orientacionAlto=23;
                aux2=4;
                aux3=23;
                aux4=23;
            }
            else if(personaje==3){
                orientacionAncho=22;
                aux=53.54;
                orientacionAlto=23;
                aux2=0.1;
                aux3=23;
                aux4=23;
            }
            else if(personaje==4){
                orientacionAncho=22;
                aux=53.54;
                orientacionAlto=23;
                aux2=4;
                aux3=23;
                aux4=23;
            }
            else if(personaje==5){
                orientacionAncho=22;
                aux=34.27;
                orientacionAlto=23;
                aux2=0.1;
                aux3=23;
                aux4=23;
            }
            else if(personaje==6){
                orientacionAncho=22;
                aux=34.27;
                orientacionAlto=23;
                aux2=4;
                aux3=23;
                aux4=23;
            }
            velocidad.y=-jumpSpeed;
            sprite1->setPosition(sprite1->getPosition().x ,sprite1->getPosition().y-1);
            isGrounded=false;
        }

    }

    ///CAMINAR HACIA IZQUIERDA
    if(Keyboard::isKeyPressed(sf::Keyboard::Left)&&hit==false) {
        if(isGrounded==false) {
            moveSpeed=5.0f;
        } else {
            moveSpeed=10.0f;
        }
        direccion=false;
        velocidad.x=-moveSpeed;

        if(isGrounded==true) {
           if(pressL==0 || pressL==1) {
                if(personaje==1){
                orientacionAncho=15;
                aux=10.33;
                orientacionAlto=21;
                aux2=0.1;
                aux3=15;
                aux4=22;
                }
                else if(personaje==2){
                orientacionAncho=15;
                aux=10.33;
                orientacionAlto=21;
                aux2=4.4;
                aux3=15;
                aux4=22;
                }
                else if(personaje==3){
                orientacionAncho=15;
                aux=66.73;
                orientacionAlto=21;
                aux2=0.1;
                aux3=16;
                aux4=22;
                }
                else if(personaje==4){
                orientacionAncho=15;
                aux=66.73;
                orientacionAlto=21;
                aux2=4.4;
                aux3=16;
                aux4=22;
                }
                else if(personaje==5){
                orientacionAncho=15;
                aux=38.46;
                orientacionAlto=21;
                aux2=0.1;
                aux3=16;
                aux4=22;
                }
                else if(personaje==6){
                orientacionAncho=15;
                aux=38.46;
                orientacionAlto=21;
                aux2=4.4;
                aux3=15;
                aux4=22;
                }
                pressL++;
            }
            else if(pressL==2 || pressL==3) {
                if(personaje==1){
                orientacionAncho=14;
                aux=8.9;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==2){
                        orientacionAncho=14;
                aux=8.9;
                orientacionAlto=22;
                aux2=4.22;
                aux3=15;
                aux4=23;
                }
                else if(personaje==3){
                orientacionAncho=14;
                aux=69.42;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==4){
                orientacionAncho=14;
                aux=69.42;
                orientacionAlto=22;
                aux2=4.22;
                aux3=15;
                aux4=23;
                }
                else if(personaje==5){
                orientacionAncho=14;
                aux=39.14;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==6){
                orientacionAncho=14;
                aux=39.14;
                orientacionAlto=22;
                aux2=4.22;
                aux3=15;
                aux4=23;
                }
                pressL++;
            }
            else {
                if(personaje==1){
                orientacionAncho=16;
                aux=5.9;
                orientacionAlto=22;
                aux2=0.1;
                aux3=16;
                aux4=23;
                }
                else if(personaje==2){
                orientacionAncho=16;
                aux=5.9;
                orientacionAlto=22;
                aux2=4.22;
                aux3=16;
                aux4=23;
                }
                else if(personaje==3){
                orientacionAncho=16;
                aux=58.8125;
                orientacionAlto=22;
                aux2=0.1;
                aux3=16;
                aux4=23;
                }
                else if(personaje==4){
                orientacionAncho=16;
                aux=58.8125;
                orientacionAlto=22;
                aux2=4.22;
                aux3=16;
                aux4=23;
                }
                else if(personaje==5){
                orientacionAncho=16;
                aux=32.3125;
                orientacionAlto=22;
                aux2=0.1;
                aux3=16;
                aux4=23;
                }
                else if(personaje==6){
                orientacionAncho=16;
                aux=32.3125;
                orientacionAlto=22;
                aux2=4.22;
                aux3=16;
                aux4=23;
                }
                pressL=0;
            }
        }
        else {
            velocidad.x=-5;
        }
    }

    ///CAMINAR HACIA DERECHA
    else if(Keyboard::isKeyPressed(sf::Keyboard::Right)&&hit==false) {
        if(isGrounded==false) {
            moveSpeed=5.0f;
        }
        else {
            moveSpeed=10.0f;
        }
        direccion=true;
        velocidad.x=moveSpeed;

        if(isGrounded==true) {
           if(pressR==0 || pressR==1) {
                if(personaje==1){
                orientacionAncho=15;
                aux=16.4;
                orientacionAlto=21;
                aux2=0.1;
                aux3=15;
                aux4=22;
                }
                else if(personaje==2){
                orientacionAncho=15;
                aux=16.4;
                orientacionAlto=21;
                aux2=4.4;
                aux3=15;
                aux4=22;
                }
                else if(personaje==3){
                orientacionAncho=15;
                aux=72.8;
                orientacionAlto=21;
                aux2=0.1;
                aux3=16;
                aux4=22;
                }
                else if(personaje==4){
                orientacionAncho=15;
                aux=72.8;
                orientacionAlto=21;
                aux2=4.4;
                aux3=16;
                aux4=22;
                }
                else if(personaje==5){
                orientacionAncho=15;
                aux=44.53;
                orientacionAlto=21;
                aux2=0.1;
                aux3=16;
                aux4=22;
                }
                else if(personaje==6){
                orientacionAncho=15;
                aux=44.53;
                orientacionAlto=21;
                aux2=4.4;
                aux3=15;
                aux4=22;
                }
                pressR++;
            }
            else if(pressR==2 || pressR==3) {
                if(personaje==1){
                orientacionAncho=14;
                aux=19.7;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==2){
                orientacionAncho=14;
                aux=19.7;
                orientacionAlto=22;
                aux2=4.22;
                aux3=15;
                aux4=23;
                }
                else if(personaje==3){
                orientacionAncho=14;
                aux=80.14;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==4){
                orientacionAncho=14;
                aux=80.14;
                orientacionAlto=22;
                aux2=4.22;
                aux3=15;
                aux4=23;
                }
                else if(personaje==5){
                orientacionAncho=14;
                aux=49.85;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==6){
                orientacionAncho=14;
                aux=49.85;
                orientacionAlto=22;
                aux2=4.22;
                aux3=15;
                aux4=23;
                }
                pressR++;
            }
            else {
                if(personaje==1){
                orientacionAncho=16;
                aux=19;
                orientacionAlto=22;
                aux2=0.1;
                aux3=16;
                aux4=23;
                }
                else if(personaje==2){
                orientacionAncho=16;
                aux=19;
                orientacionAlto=22;
                aux2=4.22;
                aux3=16;
                aux4=23;
                }
                else if(personaje==3){
                orientacionAncho=16;
                aux=71.9375;
                orientacionAlto=22;
                aux2=0.1;
                aux3=16;
                aux4=23;
                }
                else if(personaje==4){
                orientacionAncho=16;
                aux=71.9375;
                orientacionAlto=22;
                aux2=4.22;
                aux3=16;
                aux4=23;
                }
                else if(personaje==5){
                orientacionAncho=14;
                aux=49.85;
                orientacionAlto=22;
                aux2=0.1;
                aux3=15;
                aux4=23;
                }
                else if(personaje==6){
                orientacionAncho=16;
                aux=45.4375;
                orientacionAlto=22;
                aux2=4.22;
                aux3=16;
                aux4=23;
                }
                pressR=0;
            }
        }
        else {
            velocidad.x=5;
        }
    }

    else {

        velocidad.x=0;
    }


    ///GOLPEAR
    if(Keyboard::isKeyPressed(sf::Keyboard::RShift)&&hit==false&&isGrounded==true) {
        if(isGrounded==true) {
            if(direccion==false) {
                reloj.restart();
                if(personaje==1){
                orientacionAncho=23;
                aux=0;
                orientacionAlto=26;
                aux2=0;
                aux3=23;
                aux4=27;
                }
                else if(personaje==2){
                orientacionAncho=23;
                aux=0;
                orientacionAlto=26;
                aux2=3.5;
                aux3=23;
                aux4=27;

                }
                else if(personaje==3){
                orientacionAncho=23;
                aux=36.82;
                orientacionAlto=26;
                aux2=0;
                aux3=24;
                aux4=27;
                }
                else if(personaje==4){
                orientacionAncho=23;
                aux=36.82;
                orientacionAlto=26;
                aux2=3.5;
                aux3=24;
                aux4=27;
                }
                else if(personaje==5){
                orientacionAncho=23;
                aux=18.39;
                orientacionAlto=26;
                aux2=0;
                aux3=23;
                aux4=27;
                }
                else if(personaje==6){
                orientacionAncho=23;
                aux=18.39;
                orientacionAlto=26;
                aux2=3.5;
                aux3=24;
                aux4=27;
                }
            }
            else {
                reloj.restart();
                velocidad.y+=Gravity;
                if(personaje==1){
                orientacionAncho=23;
                aux=17;
                orientacionAlto=26;
                aux2=0;
                aux3=23;
                aux4=27;
                }
                else if(personaje==2){
                orientacionAncho=23;
                aux=17;
                orientacionAlto=26;
                aux2=3.5;
                aux3=23;
                aux4=27;

                }
                else if(personaje==3){
                orientacionAncho=23;
                aux=53.82;
                orientacionAlto=26;
                aux2=0;
                aux3=24;
                aux4=27;
                }
                else if(personaje==4){
                orientacionAncho=23;
                aux=53.82;
                orientacionAlto=26;
                aux2=3.5;
                aux3=24;
                aux4=27;
                }
                else if(personaje==5){
                orientacionAncho=23;
                aux=35.39;
                orientacionAlto=26;
                aux2=0;
                aux3=23;
                aux4=27;
                }
                else if(personaje==6){
                orientacionAncho=23;
                aux=35.39;
                orientacionAlto=26;
                aux2=3.5;
                aux3=24;
                aux4=27;
                }
            }
        }
        hit=true;
    }


    ///PASAJE DEL BORDE DE LA PANTALLA HACIA EL OTRO EXTREMO
    if(sprite1->getPosition().x + velocidad.x+30  > 800)
        sprite1->setPosition(0,ground);
    if(sprite1->getPosition().x + velocidad.x+29  < 0)
        sprite1->setPosition(800,ground);

//    if(sprite1->getPosition().y+velocidad.y<ground-100&&isGrounded==false&&(sprite1->getPosition().x + velocidad.x+30>-10&&sprite1->getPosition().x+velocidad.x+29<100))velocidad.y=0;
//
//    if(sprite1->getPosition().y+velocidad.y<ground-100&&isGrounded==false&&(sprite1->getPosition().x + velocidad.x+30<810&&sprite1->getPosition().x+velocidad.x+29>710))velocidad.y=0;

    if( sprite1->getPosition().y + velocidad.y  > ground)
        velocidad.y=0;

    ///CAIDA AL SALTAR
    if (sprite1->getPosition().y < ground) {
        isGrounded=false;
       if(direccion==false) {
            velocidad.y+=Gravity;
            if(personaje==1){
            orientacionAncho=17;
            aux=1.9;
            orientacionAlto=27;
            aux2=0;
            aux3=18;
            aux4=27;
            }
            else if(personaje==2){
            orientacionAncho=17;
            aux=1.9;
            orientacionAlto=27;
            aux2=3.35;
            aux3=18;
            aux4=27;
            }
            else if(personaje==3){
            orientacionAncho=17;
            aux=51.76;
            orientacionAlto=27;
            aux2=0;
            aux3=18;
            aux4=27;
            }
            else if(personaje==4){
            orientacionAncho=17;
            aux=51.76;
            orientacionAlto=27;
            aux2=3.35;
            aux3=18;
            aux4=27;
            }
            else if(personaje==5){
            orientacionAncho=17;
            aux=26.82;
            orientacionAlto=27;
            aux2=0;
            aux3=18;
            aux4=27;
            }
            else if(personaje==6){
            orientacionAncho=17;
            aux=26.82;
            orientacionAlto=27;
            aux2=3.35;
            aux3=18;
            aux4=27;
            }
        }
        else {
            velocidad.y+=Gravity;
            if(personaje==1){
            orientacionAncho=17;
            aux=21.4;
            orientacionAlto=27;
            aux2=0;
            aux3=18;
            aux4=27;
            }
            else if(personaje==2){
            orientacionAncho=17;
            aux=21.4;
            orientacionAlto=27;
            aux2=3.35;
            aux3=18;
            aux4=27;
            }
            else if(personaje==3){
            orientacionAncho=17;
            aux=71.23;
            orientacionAlto=27;
            aux2=0;
            aux3=18;
            aux4=27;
            }
            else if(personaje==4){
            orientacionAncho=17;
            aux=71.23;
            orientacionAlto=27;
            aux2=3.35;
            aux3=18;
            aux4=27;
            }
            else if(personaje==5){
            orientacionAncho=17;
            aux=46.294;
            orientacionAlto=27;
            aux2=0;
            aux3=18;
            aux4=27;
            }
            else if(personaje==6){
            orientacionAncho=17;
            aux=46.294;
            orientacionAlto=27;
            aux2=3.35;
            aux3=18;
            aux4=27;
            }
        }
    }
    else {

        //AL CAER SOBRE UNA PLATAFORMA, SETEA EL NUEVO PISO
        sprite1->setPosition(sprite1 ->getPosition().x, ground);
        moveSpeed=6.0f;
        isGrounded=true;
        ADS=false;



    }
}

    //MUEVE CON SUS RESPECTIVAS VELOCIDADES

    sprite1->move(velocidad.x,velocidad.y);


    ///ANIMACIONES AL ESTAR QUIETO
   if(aux==-1 && direccion==true) {
        if(personaje==1){
        orientacionAncho=14;
        aux=15.4;
        orientacionAlto=22;
        aux2=0.1;
        aux3=15;
        aux4=23;
        }
        else if(personaje==2){
        orientacionAncho=14;
        aux=15.4;
        orientacionAlto=22;
        aux2=4.22;
        aux3=15;
        aux4=23;
        }
        else if(personaje==3){
        orientacionAncho=14;
        aux=75.85;
        orientacionAlto=22;
        aux2=0.1;
        aux3=15;
        aux4=23;
        }
        else if(personaje==4){
        orientacionAncho=14;
        aux=75.85;
        orientacionAlto=22;
        aux2=4.22;
        aux3=15;
        aux4=23;
        }
        else if(personaje==5){
        orientacionAncho=14;
        aux=45.57;
        orientacionAlto=22;
        aux2=0.1;
        aux3=15;
        aux4=23;
        }
        else if(personaje==6){
        orientacionAncho=14;
        aux=45.57;
        orientacionAlto=22;
        aux2=4.22;
        aux3=15;
        aux4=23;

        }
    }
    if(aux==-1 && direccion==false) {
        if(personaje==1){
            orientacionAncho=14;
            aux=13.2;
            orientacionAlto=22;
            aux2=0.1;
            aux3=15;
            aux4=23;
        }
        else if(personaje==2){
            orientacionAncho=14;
        aux=13.2;
        orientacionAlto=22;
        aux2=4.22;
        aux3=15;
        aux4=23;
        }
        else if(personaje==3){
            orientacionAncho=14;
        aux=73.71;
        orientacionAlto=22;
        aux2=0.1;
        aux3=15;
        aux4=23;
        }
        else if(personaje==4){
            orientacionAncho=14;
        aux=73.71;
        orientacionAlto=22;
        aux2=4.22;
        aux3=15;
        aux4=23;
        }
        else if(personaje==5){
            orientacionAncho=14;
        aux=43.42;
        orientacionAlto=22;
        aux2=0.1;
        aux3=15;
        aux4=23;
        }
        else if(personaje==6){
            orientacionAncho=14;
        aux=43.42;
        orientacionAlto=22;
        aux2=4.22;
        aux3=15;
        aux4=23;
        }
    }

    ///ANIMACIONES GOLPE
    if(hit==true) {
        if(reloj.getElapsedTime().asMilliseconds()>20 && reloj.getElapsedTime().asMilliseconds()<200) {
             if(direccion==false) {
                if(personaje==1){
                orientacionAncho=23;
                aux=0;
                orientacionAlto=27;
                aux2=1.1;
                aux3=23;
                aux4=28;
                }
                else if(personaje==2){
                orientacionAncho=23;
                aux=0;
                orientacionAlto=27;
                aux2=4.44;
                aux3=23;
                aux4=28;
                }
                else if(personaje==3){
                orientacionAncho=23;
                aux=36.82;
                orientacionAlto=27;
                aux2=1.1;
                aux3=24;
                aux4=28;
                }
                else if(personaje==4){
                orientacionAncho=23;
                aux=36.82;
                orientacionAlto=27;
                aux2=4.44;
                aux3=24;
                aux4=28;
                }
                else if(personaje==5){
                orientacionAncho=23;
                aux=18.39;
                orientacionAlto=27;
                aux2=1.1;
                aux3=23;
                aux4=28;
                }
                else if(personaje==6){
                orientacionAncho=23;
                aux=18.39;
                orientacionAlto=27;
                aux2=4.44;
                aux3=24;
                aux4=28;
                }
            }
            else {
                if(personaje==1){
                orientacionAncho=23;
                aux=17;
                orientacionAlto=27;
                aux2=1.1;
                aux3=23;
                aux4=28;
                }
                else if(personaje==2){
                orientacionAncho=23;
                aux=17;
                orientacionAlto=27;
                aux2=4.44;
                aux3=23;
                aux4=28;
                }
                else if(personaje==3){
                orientacionAncho=23;
                aux=53.82;
                orientacionAlto=27;
                aux2=1.1;
                aux3=24;
                aux4=28;
                }
                else if(personaje==4){
                orientacionAncho=23;
                aux=53.82;
                orientacionAlto=27;
                aux2=4.44;
                aux3=24;
                aux4=28;
                }
                else if(personaje==5){
                orientacionAncho=23;
                aux=35.39;
                orientacionAlto=27;
                aux2=1.1;
                aux3=23;
                aux4=28;
                }
                else if(personaje==6){
                orientacionAncho=23;
                aux=35.39;
                orientacionAlto=27;
                aux2=4.44;
                aux3=24;
                aux4=28;
                }
            }
        }
        if(reloj.getElapsedTime().asMilliseconds()>200) {
                hit=false;
        }

    }

        break;
    default:
        break;
    }

    //RECORTA EL SPRITE
    IntRect rect(orientacionAncho*aux,orientacionAlto*aux2,aux3,aux4);
    sprite1->setTextureRect(rect);

}

///ACTUALIZACION DE MOVIMIENTOS
void Player::update(int jugador, bool modo) {
    mover(jugador, modo);
}

///FUNCION DE MUERTE -> RESTA VIDAS / SETEA EL GROUND ANTERIOR AL RESPAWNEAR
void Player::morir(){

    if (vidas<=3 && vidas>=-1){
        murio=false;
        sprite1->setPosition(ADSX,ADSY);
        estadoVida[vidas-1]=false;
        vidas--;
        renacio=true;

    }

}

///POSICIONA LAS VIDAS CUANDO SE MUEVE LA CAMARA
void Player::posicionarVidas(int y, int jugador, int *guardarVidas){
    float aux, aux2, aux3, aux4, orientacionAncho, orientacionAlto;

    if(jugador==1){
        if(personaje==1){
        orientacionAncho=10;
        aux=12.7;
        orientacionAlto=10;
        aux2=6.9;
        aux3=11;
        aux4=10;
        }
        else if(personaje==2){
        orientacionAncho=10;
        aux=27.7;
        orientacionAlto=10;
        aux2=6.9;
        aux3=11;
        aux4=10;
        }
        else if(personaje==3){
        orientacionAncho=10;
        aux=97.4;
        orientacionAlto=10;
        aux2=6.9;
        aux3=11;
        aux4=10;
        }
        else if(personaje==4){
        orientacionAncho=10;
        aux=112.4;
        orientacionAlto=10;
        aux2=6.9;
        aux3=11;
        aux4=10;
        }
        else if(personaje==5){
        orientacionAncho=10;
        aux=55;
        orientacionAlto=10;
        aux2=6.9;
        aux3=11;
        aux4=10;
        }
        else if(personaje==6){
        orientacionAncho=10;
        aux=70;
        orientacionAlto=10;
        aux2=6.9;
        aux3=11;
        aux4=10;
        }

        int acum=10;
        for(int i=0;i<3;i++){
            spriteVida[i].setTexture(*textura1);
            spriteVida[i].setScale(2.5,2.5);
            if(dibujoVidas==false){
                if(i<guardarVidas[0]){
                    estadoVida[i]=true;
                }
                else{
                    estadoVida[i]=false;
                }
            }
            spriteVida[i].setPosition(acum,y);
            acum+=40;
        }
        dibujoVidas=true;

    }
    else{
       if(personaje==1){
        orientacionAncho=10;
        aux=12.7;
        orientacionAlto=10;
        aux2=6.9;
        aux3=11;
        aux4=10;
        }
        else if(personaje==2){
        orientacionAncho=10;
        aux=27.7;
        orientacionAlto=10;
        aux2=6.9;
        aux3=11;
        aux4=10;
        }
        else if(personaje==3){
        orientacionAncho=10;
        aux=97.4;
        orientacionAlto=10;
        aux2=6.9;
        aux3=11;
        aux4=10;
        }
        else if(personaje==4){
        orientacionAncho=10;
        aux=112.4;
        orientacionAlto=10;
        aux2=6.9;
        aux3=11;
        aux4=10;
        }
        else if(personaje==5){
        orientacionAncho=10;
        aux=55;
        orientacionAlto=10;
        aux2=6.9;
        aux3=11;
        aux4=10;
        }
        else if(personaje==6){
        orientacionAncho=10;
        aux=70;
        orientacionAlto=10;
        aux2=6.9;
        aux3=11;
        aux4=10;
        }
        int acum=650;
        for(int i=0;i<3;i++){
            spriteVida[i].setTexture(*textura1);
            spriteVida[i].setScale(2.5,2.5);
            if(dibujoVidas==false){
                for(int j=0;j<2;j++){
                    if(i<guardarVidas[j]){
                        estadoVida[i]=true;
                    }
                    else{
                        estadoVida[i]=false;
                    }
                }
            }
            spriteVida[i].setPosition(acum,y);
            acum+=40;
        }
        dibujoVidas=true;
    }


    IntRect rectVida(orientacionAncho*aux, orientacionAlto*aux2, aux3, aux4);
    for(int i=0;i<3;i++){
        spriteVida[i].setTextureRect(rectVida);
    }
}


#endif // CLSPLAYER_H_INCLUDED
