#ifndef CLSFRUTAS_H_INCLUDED
#define CLSFRUTAS_H_INCLUDED

///CLASE OBJETOS FRUTA
class Frutas {
  private:
    Texture *textura;
    Sprite *sprite;
    int tipo;
    float orientacionAncho, orientacionAlto, aux, aux2, aux3, aux4;
    bool estado;

  public:
    ///CONSTRUCTOR
    Frutas();

    ///SETS
    void setEstado(int e){estado=e;}
    ///GETS
    Sprite getSprite(){return *sprite;}
    bool getEstado(){return estado;}

    ///METODOS
    void Random(int, bool);

    ///DESTRUCTOR
    ~Frutas();

};

///CONSTRUCTOR
Frutas::Frutas(){
    textura = new Texture;
    textura -> loadFromFile("Imagenes/Sprites.png");
    sprite = new Sprite(*textura);
    sprite -> setScale(3,3);
    estado = true;

}

///DETRUCTOR
Frutas::~Frutas(){
    delete textura;
    delete sprite;

}

///DIBUJA UNA FRUTA RANDOM
void Frutas::Random(int c, bool mapa){

    tipo = rand()%(4-1+1)+1;

    switch (tipo){
    //BERENJENA
    case 1:
        orientacionAncho=14;
        aux=0.4;
        orientacionAlto=18;
        aux2=8.6;
        aux3=14;
        aux4=19;
        break;
    //CEBOLLA
    case 2:
        orientacionAncho=12;
        aux=13;
        orientacionAlto=18;
        aux2=8.6;
        aux3=12;
        aux4=19;
        break;
    //PEPINO
    case 3:
        orientacionAncho=12;
        aux=8;
        orientacionAlto=18;
        aux2=8.6;
        aux3=12;
        aux4=19;
        break;
    //ZANAHORIA
    case 4:
        orientacionAncho=17;
        aux=1.9;
        orientacionAlto=18;
        aux2=8.6;
        aux3=18;
        aux4=20;
        break;
    default:
        break;
    }

    ///DEPENDIENDO QUE MAPA SEA (1 O 2) ACOMODA LA FRUTA EN SU DETERMINADA PLATAFORMA
    if(mapa==false){
        ///LAS UBICACIONES DE LAS PLATAFORMAS SE RELACIONAN POR MEDIO DE UN CONTADOR QUE SE PASA POR PARAMETRO EN LA FUNCION
        switch (c){
        case 0:
            sprite->setPosition(367,-740);

            break;
        case 1:
            sprite->setPosition(250,-980);

            break;
        case 2:
            sprite->setPosition(473,-980);

            break;
        case 3:
            sprite->setPosition(367,-1120);

            break;
        case 4:
            sprite->setPosition(170,-1388);

            break;
        case 5:
            if(tipo==4){
            sprite->setPosition(544,-1388);
            }
            else{
            sprite->setPosition(558,-1388);
            }
            break;
        case 6:
            sprite->setPosition(367,-1490);

            break;
        case 7:
            sprite->setPosition(247,-1590);

            break;
        case 8:
            sprite->setPosition(487,-1590);

            break;
        case 9:
            sprite->setPosition(180,-1255);

            break;
        case 10:
            sprite->setPosition(620,-855);

            break;
        default:
            break;
        }
    }
    else{
        switch (c){
        case 0:
            sprite->setPosition(367,-740);

            break;
        case 1:
            sprite->setPosition(150,-810);

            break;
        case 2:
            sprite->setPosition(585,-810);

            break;
        case 3:
            sprite->setPosition(367,-933);

            break;
        case 4:
            sprite->setPosition(130,-977);

            break;
        case 5:
            if(tipo==4){
            sprite->setPosition(590,-977);
            }
            else{
            sprite->setPosition(600,-977);
            }
            break;
        case 6:
            sprite->setPosition(367,-1207);

            break;
        case 7:
            sprite->setPosition(170,-1315);

            break;
        case 8:
            if(tipo==4){
            sprite->setPosition(545,-1315);
            }
            else{
            sprite->setPosition(555,-1315);
            }
            break;
        case 9:
            sprite->setPosition(270,-1507);

            break;
        case 10:
            sprite->setPosition(460,-1507);

            break;
        default:
            break;
        }
    }

    if(c==11){
        c=0;
    }

    //RECORTA Y SETEA EL SPRITE CORRESPONDIENDE
    IntRect rect(orientacionAncho*aux, orientacionAlto*aux2, aux3, aux4);
    sprite->setTextureRect(rect);
}

#endif // CLSFRUTAS_H_INCLUDED
