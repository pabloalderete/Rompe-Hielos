#ifndef CLSENEMIGOS_H_INCLUDED
#define CLSENEMIGOS_H_INCLUDED

///CLASE ENEMIGOS
class Enemigos {

  protected:
    Texture *textura;
    Sprite *sprite;
    Vector2f velocidad, posicion;
    bool golpeado, muerte, estado, caida, direccion, direcMuerte=false;
    int tipo, piso, plataforma;
    int orientacionAncho, orientacionAlto, aux, aux2, aux3, aux4;
    int c1,c2,c3;
    Clock relojOso;

  public:
    ///CONSTRUCTOR
    Enemigos();

    ///SETS
    void setEstado(bool e){estado=e;}
    void setPlataforma(int p){plataforma=p;}
    void setDireccion(bool d){direccion=d;}
    void setGolpeado(bool g){golpeado=g;}
    void setVelocidadX(int v){velocidad.x=v;}
    void setVelocidadY(int v){velocidad.y=v;}
    void setCaida(bool c){caida=c;}
    void setReloj(){relojOso.restart();}

    ///GETS
    Sprite getSprite(){return *sprite;}
    bool getDireccion(){return direccion;}
    bool getEstado(){return estado;}
    float getPosicion(){return posicion.y;}
    bool getGolpeado(){return golpeado;}
    Vector2f getVelocidad() {
        return velocidad;
    }
    Clock getReloj(){return relojOso;}
    bool getCaida(){return caida;}
    int getTipo(){return tipo;}
    bool getMurio(){return muerte;}


    ///METODOS
    void Movimiento(bool);
    void update(bool);
    void textpiso();
    void posicionarRebote();

    ///DESTRUCTOR
    ~Enemigos();

};

///CONSTRUCTOR
Enemigos::Enemigos() {
    textura= new Texture;
    textura->loadFromFile("Imagenes/Sprites.png");
    sprite = new Sprite;
    sprite->setTexture(*textura);
    estado=true;
    golpeado=false;
    muerte=false;
    c1=c2=c3=0;

}

///DESTRUCTOR
Enemigos::~Enemigos(){
    delete textura;
    delete sprite;
}

///MOVIMIENTO ENEMIGOS
void Enemigos::Movimiento(bool direcPlayer) {
    float moveSpeed=3.0f,fallSpeed=0.0f;
    float aux=0, aux2=0,aux3=0,aux4=0;
    float orientacionAncho=0,orientacionAlto=0;


    switch (tipo){

    ///MOVIMIENTO FOCA
    case 1:{
        if (golpeado==false) {
        if (direccion==true) {

           moveSpeed=3.0f;

            if (c1==0 || c1==1 ){
            orientacionAncho=18;
            aux=6.8;
            orientacionAlto=15;
            aux2=22.2;
            aux3=19;
            aux4=18;
            c1++;
            }
            else if (c1==2 || c1==3 ){
            orientacionAncho=17;
            aux=9;
            orientacionAlto=16;
            aux2=21;
            aux3=18;
            aux4=16;
            c1++;
            }
            else if (c1==4){
            orientacionAncho=15;
            aux=12.2;
            orientacionAlto=17;
            aux2=19.7;
            aux3=18;
            aux4=18;
            c1=0;
            }

        }

        else {

            moveSpeed=-3.0f;

            if (c2==0 || c2==1 ){
            orientacionAncho=18;
            aux=5.2;
            orientacionAlto=15;
            aux2=22.2;
            aux3=19;
            aux4=18;
            c2++;
            }
            else if (c2==2 || c2==3 ){
            orientacionAncho=17;
            aux=3.7;
            orientacionAlto=16;
            aux2=21;
            aux3=18;
            aux4=16;
            c2++;
            }
            else if (c2==4){
            orientacionAncho=15;
            aux=2.26;
            orientacionAlto=17;
            aux2=19.7;
            aux3=18;
            aux4=18;
            c2=0;
            }

        }

    }
    else if(golpeado==true &&caida==false){


        if(muerte==false){
            if(direcPlayer==true){
                direcMuerte=true;
            }
            else{
                direcMuerte=false;
            }
        }

        muerte=true;

        if(c3==0){
        orientacionAncho=16;
            aux=0.2;
            orientacionAlto=17;
            aux2=19.7;
            aux3=17;
            aux4=18;
        c3++;
        }
        else{
        orientacionAncho=16;
            aux=13.375;
            orientacionAlto=17;
            aux2=19.7;
            aux3=17;
            aux4=18;
        c3=0;
        }
    }
    else if (caida==true && golpeado == true){
        muerte=true;
        fallSpeed=20.0f;
        moveSpeed=0.0f;
         if(c3==0){
        orientacionAncho=16;
            aux=0.2;
            orientacionAlto=17;
            aux2=19.7;
            aux3=17;
            aux4=18;
        c3++;
        }
        else{
        orientacionAncho=16;
            aux=13.375;
            orientacionAlto=17;
            aux2=19.7;
            aux3=17;
            aux4=18;
            c3=0;

        }

    }

        if(direcMuerte==true && muerte==true && caida==false){
            moveSpeed=10.0f;
        }
        else if(direcMuerte==false && muerte==true && caida==false){
            moveSpeed=-10.0f;
        }

        velocidad.x=moveSpeed;
        velocidad.y=fallSpeed;

        sprite->move (velocidad.x,velocidad.y);

        if (sprite->getPosition().x >= 780 &&muerte==true){
            estado=false;
        }

        if (sprite->getPosition().x < -10&&muerte==true){
            estado=false;
        }

        if (sprite->getPosition().x >= 780){
            sprite->setPosition(-10,piso);

        }
        else if (sprite->getPosition().x < -10 ){
            sprite->setPosition(770, piso);
        }

        if (sprite->getPosition().y==830&&muerte==true){
            estado=false;

        }

        IntRect rect(orientacionAncho*aux, orientacionAlto*aux2, aux3, aux4);
        sprite->setTextureRect(rect);
    }
        break;

    ///MOVIMIENTO JETI
    case 2:{
    if (golpeado==false) {
        if (direccion==true) {

           moveSpeed=3.0f;

            if (c1==0 || c1==1){
            orientacionAncho=17;
            aux=7.2;
            orientacionAlto=18;
            aux2=15.3;
            aux3=18;
            aux4=18;
            c1++;
            }
            else if (c1==2 || c1==3){
            orientacionAncho=17;
            aux=9;
            orientacionAlto=18;
            aux2=15.3;
            aux3=17;
            aux4=18;
            c1++;
            }
            else if (c1==4){
            orientacionAncho=18;
            aux=10.2;
            orientacionAlto=17;
            aux2=16.2;
            aux3=18;
            aux4=17;
            c1=0;
            }

        }

        else {

            moveSpeed=-3.0f;

            if (c2==0 || c2==1){
            orientacionAncho=17;
            aux=5.5;
            orientacionAlto=18;
            aux2=15.3;
            aux3=17;
            aux4=18;
            c2++;
            }
            else if (c2==2 || c2==3){
            orientacionAncho=17;
            aux=3.7;
            orientacionAlto=18;
            aux2=15.3;
            aux3=18;
            aux4=18;
            c2++;
            }
            else if (c2==4){
            orientacionAncho=18;
            aux=1.87;
            orientacionAlto=17;
            aux2=16.2;
            aux3=18;
            aux4=17;
            c2=0;
            }

        }

    }
    else if (golpeado==true && caida==false){

        if(muerte==false){
            if(direcPlayer==true){
                direcMuerte=true;
            }
            else{
                direcMuerte=false;
            }
        }

        muerte=true;

        if(c3==0){
        orientacionAncho=17;
        aux=0.2;
        orientacionAlto=18;
        aux2=15.3;
        aux3=17;
        aux4=18;
        c3++;
        }
        else{
        orientacionAncho=17;
        aux=12.55;
        orientacionAlto=18;
        aux2=15.3;
        aux3=17;
        aux4=18;
        c3=0;
        }
    }
    else if (caida==true && golpeado == true){
        muerte=true;
        fallSpeed=20.0f;
        moveSpeed=0.0f;
        if(c3==0){
        orientacionAncho=17;
        aux=0.2;
        orientacionAlto=18;
        aux2=15.3;
        aux3=17;
        aux4=18;
        c3++;
        }
        else{
        orientacionAncho=17;
        aux=12.55;
        orientacionAlto=18;
        aux2=15.3;
        aux3=17;
        aux4=18;
        c3=0;
        }
    }

        if(direcMuerte==true && muerte==true && caida==false){
            moveSpeed=10.0f;
        }
        else if(direcMuerte==false && muerte==true && caida==false){
            moveSpeed=-10.0f;
        }

        velocidad.x=moveSpeed;
        velocidad.y=fallSpeed;

        sprite->move (velocidad.x,velocidad.y);

        if (sprite->getPosition().x ==820){
            sprite->setPosition(-20,piso);

        }
        else if (sprite->getPosition().x == -20 ){
            sprite->setPosition(820, piso);
        }

        if (sprite->getPosition().x==770&&muerte==true){
            estado=false;
        }

        if (sprite->getPosition().x==0&&muerte==true){
            estado=false;
        }


        if (sprite->getPosition().y==830&&muerte==true){
            estado=false;
        }

        IntRect rect(orientacionAncho*aux, orientacionAlto*aux2, aux3, aux4);
        sprite->setTextureRect(rect);

    }
        break;

    ///MOVIMIENTO OSO
    case 3:{
    if (golpeado==false) {
        if (direccion==true) {

           moveSpeed=3.0f;

            if (c1==0 || c1==1){
            orientacionAncho=15;
            aux=8.3;
            orientacionAlto=33;
            aux2=9;
            aux3=15;
            aux4=33;
            c1++;
            }
            else if (c1==2 || c1==3){
            orientacionAncho=17;
            aux=9;
            orientacionAlto=32;
            aux2=9.3;
            aux3=17;
            aux4=33;
            c1++;
            }
            else if (c1==4){
            orientacionAncho=17;
            aux=10.8;
            orientacionAlto=32;
            aux2=9.3;
            aux3=17;
            aux4=33;
            c1=0;
            }

        }

        else {

            moveSpeed=-3.0f;

            if (c2==0 || c2==1){
            orientacionAncho=15;
            aux=6.33;
            orientacionAlto=33;
            aux2=9;
            aux3=15;
            aux4=33;
            c2++;
            }
            else if (c2==2 || c2==3){
            orientacionAncho=17;
            aux=3.7;
            orientacionAlto=32;
            aux2=9.3;
            aux3=18;
            aux4=33;
            c2++;
            }
            else if (c2==4){
            orientacionAncho=17;
            aux=1.9;
            orientacionAlto=32;
            aux2=9.3;
            aux3=18;
            aux4=33;
            c2=0;
            }

        }


    }
    else if (golpeado==true && caida==false){

        moveSpeed=0.0f;
        orientacionAncho=18;
        aux=11.83;
        orientacionAlto=31;
        aux2=9.6;
        aux3=19;
        aux4=32;
        if (relojOso.getElapsedTime().asMilliseconds()>2000){
        golpeado=false;
        }
        if(relojOso.getElapsedTime().asMilliseconds()>=0&&relojOso.getElapsedTime().asMilliseconds()<250){
        orientacionAncho=18;
        aux=0.1;
        orientacionAlto=31;
        aux2=9.6;
        aux3=20;
        aux4=31;
        }
        if(relojOso.getElapsedTime().asMilliseconds()>250&&relojOso.getElapsedTime().asMilliseconds()<500){
            orientacionAncho=18;
        aux=11.83;
        orientacionAlto=31;
        aux2=9.6;
        aux3=19;
        aux4=32;
        }
        if(relojOso.getElapsedTime().asMilliseconds()>500&&relojOso.getElapsedTime().asMilliseconds()<750){
            orientacionAncho=18;
        aux=0.1;
        orientacionAlto=31;
        aux2=9.6;
        aux3=20;
        aux4=31;
        }
        if(relojOso.getElapsedTime().asMilliseconds()>750&&relojOso.getElapsedTime().asMilliseconds()<1000){
        orientacionAncho=18;
        aux=11.83;
        orientacionAlto=31;
        aux2=9.6;
        aux3=19;
        aux4=32;
        }
        if(relojOso.getElapsedTime().asMilliseconds()>1000&&relojOso.getElapsedTime().asMilliseconds()<1250){
        orientacionAncho=18;
        aux=0.1;
        orientacionAlto=31;
        aux2=9.6;
        aux3=20;
        aux4=31;
        }
        if(relojOso.getElapsedTime().asMilliseconds()>1250&&relojOso.getElapsedTime().asMilliseconds()<1500){
        orientacionAncho=18;
        aux=11.83;
        orientacionAlto=31;
        aux2=9.6;
        aux3=19;
        aux4=32;
        }
        if(relojOso.getElapsedTime().asMilliseconds()>1500&&relojOso.getElapsedTime().asMilliseconds()<1750){
        orientacionAncho=18;
        aux=0.1;
        orientacionAlto=31;
        aux2=9.6;
        aux3=20;
        aux4=31;
        }
        if(relojOso.getElapsedTime().asMilliseconds()>1750&&relojOso.getElapsedTime().asMilliseconds()<2000){
        orientacionAncho=18;
        aux=11.83;
        orientacionAlto=31;
        aux2=9.6;
        aux3=19;
        aux4=32;
        }
    }
    else if (golpeado== true && caida == true){
        muerte=true;

        fallSpeed=20.0f;
        moveSpeed=0.0f;
        orientacionAncho=18;
        aux=0.1;
        orientacionAlto=31;
        aux2=9.6;
        aux3=20;
        aux4=31;



    }
        if(sprite->getPosition().x==370){
            direccion=false;
            moveSpeed=-10.0f;
        }

        if(sprite->getPosition().x==375){
            direccion=true;
            moveSpeed=10.0f;
        }

        velocidad.y=fallSpeed;
        velocidad.x=moveSpeed;


        sprite->move (velocidad.x,velocidad.y);


        if (sprite->getPosition().x==800){
            sprite->setPosition(-10,piso);
        }
        else if (sprite->getPosition().x==-10){
             sprite->setPosition(800,piso);
        }

        if (sprite->getPosition().y==830&&muerte==true){
            estado=false;
        }

        IntRect rect(orientacionAncho*aux,orientacionAlto*aux2,aux3,aux4);
        sprite->setTextureRect(rect);

    }
        break;

    ///MOVIMIENTO PAJARO
    case 4:{
    if (golpeado==false) {
        if (direccion==true) {

           moveSpeed=5.0f;

            if (c1==0 || c1==1){
            orientacionAncho=18;
            aux=5.2;
            orientacionAlto=14;
            aux2=13.4;
            aux3=18;
            aux4=14;
            c1++;
            }
            else if (c1==2 || c1==3 ){
            orientacionAncho=18;
            aux=6.85;
            orientacionAlto=18;
            aux2=10.3;
            aux3=18;
            aux4=18;
            c1++;
            }
            else if (c1==4){
            orientacionAncho=18;
            aux=6.85;
            orientacionAlto=18;
            aux2=10.3;
            aux3=18;
            aux4=18;
                c1=0;
            }

        }

        else {

            moveSpeed=-5.0f;

            if (c2==0 || c2==1){
            orientacionAncho=18;
            aux=3.5;
            orientacionAlto=14;
            aux2=13.4;
            aux3=18;
            aux4=14;
            c2++;
            }
            else if (c2==2 || c2==3){
            orientacionAncho=18;
            aux=1.85;
            orientacionAlto=18;
            aux2=10.3;
            aux3=18;
            aux4=18;
            c2++;
            }
            else if (c2==4){
                 orientacionAncho=18;
            aux=1.85;
            orientacionAlto=18;
            aux2=10.3;
            aux3=18;
            aux4=18;
                c2=0;
            }


        }


    }
    else{
        muerte=true;

        fallSpeed=20.0f;
        moveSpeed=0;

        orientacionAncho=16;
        aux=9.63;
        orientacionAlto=17;
        aux2=10.9;
        aux3=16;
        aux4=17;


    }

        velocidad.x=moveSpeed;
        velocidad.y=fallSpeed;

        sprite->move (velocidad.x,velocidad.y);

        if (sprite->getPosition().y==830&&muerte==true){
            estado=false;
        }

        if (sprite->getPosition().x==960){
            sprite->setPosition(0,piso);
        }


        IntRect rect(orientacionAncho*aux,orientacionAlto*aux2,aux3,aux4);
        sprite->setTextureRect(rect);

    }
        break;
    default:
        break;
    }
}

///SETEA EL PISO DE CADA ENEMIGO DEPENDIENDO SU TIPO
void Enemigos::textpiso(){
    int acum=0;

    tipo = rand()%(4-1+1)+1;

    if (tipo==1) acum= 530;
    else if (tipo==2) acum= 530;
    else if (tipo==3) acum= 495;
    else acum=515;

    switch (plataforma){
        case 0:
            acum-=145;
            break;
        case 1:
            acum-=290;
            break;
        case 2:
            acum-=435;
            break;
        case 3:
            acum-=580;
            break;
        case 4:
            acum-=725;
            break;
        case 5:
            acum-=870;
            break;
        case 6:
            acum-=1015;
            break;
    }

        piso=acum;
        switch (tipo){
        case 1:{

            direccion=true;
            IntRect rect(18*6.8, 15*22.2, 19, 18);
            sprite->setTextureRect(rect);
            sprite->setPosition(0,piso);
            sprite->setScale(2.5, 2.5);

        }
            break;
        case 2:{
            direccion=false;
            IntRect rect(17*5.5, 18*15.3, 17, 18);
            sprite->setTextureRect(rect);
            sprite->setPosition(700,piso);
            sprite->setScale(2.5, 2.5);
        }
            break;
        case 3:{
            direccion=true;
            IntRect rect(15*8.3, 33*9, 15, 33);
            sprite->setTextureRect(rect);
            sprite->setPosition(380,piso);
            sprite->setScale(2.5, 2.5);
        }
            break;
        case 4:{
            direccion=true;
            IntRect rect(18*5.2, 14*13.4, 18, 14);
            sprite->setTextureRect(rect);
            sprite->setPosition(0,piso);
            sprite->setScale(2, 2);
        }
            break;
        default:
            break;
        }

    caida=false;


}

///ACTUALIZA LOS MOVIMIENTOS DE LOS ENEMIGOS
void Enemigos::update(bool direcPlayer){
Movimiento(direcPlayer);
}

///POSICIONA AL ENEMIGO AL CHOCAR CONTRA UNA PLATAFORMA VACIA
void Enemigos::posicionarRebote(){

    if(direccion==true){
        direccion=false;
        sprite->setPosition(sprite->getPosition().x-15, sprite->getPosition().y);
    }
    else{
        direccion=true;
        sprite->setPosition(sprite->getPosition().x+15, sprite->getPosition().y);
    }

}

#endif // CLSENEMIGOS_H_INCLUDED
