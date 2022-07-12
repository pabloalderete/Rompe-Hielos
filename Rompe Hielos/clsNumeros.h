#ifndef CLSNUMEROS_H_INCLUDED
#define CLSNUMEROS_H_INCLUDED

///CLASE DE SELECCION DE SPRITES DE NUMEROS
class Numeros{
private:
    Texture *textura;
    Sprite *sprite;
    int posicionx, posiciony;
    float orientacionAncho, orientacionAlto, aux, aux2, aux3, aux4, numero;
public:
    ///CONSTRUCTOR
    Numeros();

    ///SETS
    void setNumero(int n){numero=n;}

    ///GETS
    Sprite getSprite(){return *sprite;}
    float getNumero(){return numero;}

    ///METODOS
    void seleccionNumero(int, int, int);

    ///DESTRUCTOR
    ~Numeros();
};

///CONSTRUCTOR
Numeros::Numeros(){
textura = new Texture;
textura->loadFromFile("Imagenes/Mapa.png");
sprite = new Sprite(*textura);
posicionx=0;
posiciony=0;

sprite->setPosition(posicionx,posiciony);
sprite -> setScale(3,3);
IntRect rect(7*37.8, 7*1.2, 7, 7);
sprite->setTextureRect(rect);

}

///DESTRUCTOR
Numeros::~Numeros(){
    delete textura;
    delete sprite;

}

///ELIGE EL NUMERO QUE SE QUIERE UTILIZAR/DIBUJAR
void Numeros::seleccionNumero(int numero, int posicionx, int posiciony){

    switch (numero){
    case 0:
        orientacionAncho=7;
        aux=37.8;
        orientacionAlto=7;
        aux2=1.2;
        aux3=7;
        aux4=7;

        break;
    case 1:
        orientacionAncho=7;
        aux=38.9;
        orientacionAlto=7;
        aux2=1.2;
        aux3=7;
        aux4=7;

        break;
    case 2:
        orientacionAncho=7;
        aux=40;
        orientacionAlto=7;
        aux2=1.2;
        aux3=7;
        aux4=7;

        break;
    case 3:
        orientacionAncho=7;
        aux=41.2;
        orientacionAlto=7;
        aux2=1.2;
        aux3=7;
        aux4=7;

        break;
    case 4:
        orientacionAncho=7;
        aux=42.3;
        orientacionAlto=7;
        aux2=1.2;
        aux3=7;
        aux4=7;
        break;
    case 5:
        orientacionAncho=7;
        aux=43.5;
        orientacionAlto=7;
        aux2=1.2;
        aux3=7;
        aux4=7;

        break;
    case 6:
        orientacionAncho=7;
        aux=44.6;
        orientacionAlto=7;
        aux2=1.2;
        aux3=7;
        aux4=7;

        break;
    case 7:
        orientacionAncho=7;
        aux=45.8;
        orientacionAlto=7;
        aux2=1.2;
        aux3=7;
        aux4=7;

        break;
    case 8:
        orientacionAncho=7;
        aux=46.9;
        orientacionAlto=7;
        aux2=1.2;
        aux3=7;
        aux4=7;

        break;
    case 9:
        orientacionAncho=7;
        aux=48;
        orientacionAlto=7;
        aux2=1.2;
        aux3=7;
        aux4=7;

        break;

    default:
        break;
    }

    sprite->setPosition(posicionx,posiciony);
    IntRect rect(orientacionAncho*aux, orientacionAlto*aux2, aux3, aux4);
    sprite->setTextureRect(rect);

    }

#endif // CLSNUMEROS_H_INCLUDED
