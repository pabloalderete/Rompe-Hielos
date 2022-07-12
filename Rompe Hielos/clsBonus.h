#ifndef CLSBONUS_H_INCLUDED
#define CLSBONUS_H_INCLUDED

///CLASE DEL BONUS STAGE
class Bonus{
private:
    Texture *texturaPlataforma, *texturaNube, *texturaAguilucho;
    Sprite *spritePlataforma, *spriteNube, *spriteAguilucho;
    bool *direccionNubes, mapa,direccionAguilucho;
    float orientacionAncho, orientacionAlto, aux, aux2, aux3, aux4;
    int mapaBonus, c=0,c2=0,c3=0;
    Clock relojAguilucho;
    Frutas *frutas;

public:
    ///CONSTRUCTOR
    Bonus();

    ///GETS
    Sprite getSpritePlataforma(int i){return spritePlataforma[i];}
    Sprite getSpriteNube(int i){return spriteNube[i];}
    Sprite getSpriteFruta(int i){return frutas[i].getSprite();}
    Sprite getSpriteAguilucho(){return *spriteAguilucho;}
    int getMapaBonus(){return mapaBonus;}
    bool getEstadoFruta(int i){return frutas[i].getEstado();}
    Clock getRelojAguilucho(){return relojAguilucho;}
    bool getDireccionNubes(int i){return direccionNubes[i];}

    ///SETS
    void setEstadoFruta(int i, bool e){frutas[i].setEstado(e);}
    void setRelojAguilucho(){relojAguilucho.restart();}

    ///METODOS
    void MovimientoNube();
    void MovimientoAguilucho();

    ///DESTRUCTOR
    ~Bonus();
};

///CONSTRUCTOR
Bonus::Bonus(){
    texturaPlataforma=new Texture;
    texturaPlataforma->loadFromFile("Imagenes/Mapa.png");
    IntRect rect(48*4.35,8*77,48,8);

    texturaNube = new Texture;
    texturaAguilucho=new Texture;
    texturaNube -> loadFromFile("Imagenes/Sprites.png");
    texturaAguilucho->loadFromFile("Imagenes/Sprites.png");
    IntRect rectNube(45*6.75,10*15.9,46,11);
    IntRect rectAguilucho(34*5.88,18*11.7,35,19);
    spriteAguilucho = new Sprite(*texturaAguilucho,rectAguilucho);
    spriteAguilucho -> setPosition(0,-1900);
    spriteAguilucho -> setScale(3,3);
    direccionAguilucho=true;


    //Dependiendo el numero random que salga, se genera un mapa diferente
    mapaBonus=rand()%(2-1+1)+1;


    if(mapaBonus==1){
       mapa=false;
    }
    else{
        mapa=true;
    }

    frutas = new Frutas[11];
    for(int i=0;i<11;i++){
        frutas[i].Random(c, mapa);
        c++;
    }
    switch (mapaBonus){
    case 1:
    spritePlataforma=new Sprite[15];
    spriteNube = new Sprite[2];
    direccionNubes = new bool[2];

    direccionNubes[0]=true;
    direccionNubes[1]=false;

    for(int i=0;i<15;i++){
    spritePlataforma[i].setTexture(*texturaPlataforma);
    spritePlataforma[i].setTextureRect(rect);
    spritePlataforma[i].setScale(3,3);
    }

    for(int i=0;i<2;i++){
    spriteNube[i].setTexture(*texturaNube);
    spriteNube[i].setTextureRect(rectNube);
    spriteNube[i].setScale(3,3);
    }

    spriteNube[0].setPosition(0,-1200);
    spriteNube[1].setPosition(620,-800);

    spritePlataforma[0].setPosition(0,-585);
    spritePlataforma[1].setPosition(205,-585);
    spritePlataforma[2].setPosition(418,-585);
    spritePlataforma[3].setPosition(626,-585);
    spritePlataforma[4].setPosition(312,-680);
    spritePlataforma[5].setPosition(200,-920);
    spritePlataforma[6].setPosition(420,-920);
    spritePlataforma[7].setPosition(312,-1060);
    spritePlataforma[8].setPosition(168,-1330);
    spritePlataforma[9].setPosition(457,-1330);
    spritePlataforma[10].setPosition(312,-1430);
    spritePlataforma[11].setPosition(192,-1530);
    spritePlataforma[12].setPosition(432,-1530);
    spritePlataforma[13].setPosition(143,-1665);
    spritePlataforma[14].setPosition(480,-1665);

        break;
    case 2:
    spritePlataforma=new Sprite[17];
    spriteNube = new Sprite[3];
    direccionNubes = new bool[3];

    direccionNubes[0]=false;
    direccionNubes[1]=true;
    direccionNubes[2]=false;


    for(int i=0;i<17;i++){
    spritePlataforma[i].setTexture(*texturaPlataforma);
    spritePlataforma[i].setTextureRect(rect);
    spritePlataforma[i].setScale(3,3);
    }

    for(int i=0;i<3;i++){
    spriteNube[i].setTexture(*texturaNube);
    spriteNube[i].setTextureRect(rectNube);
    spriteNube[i].setScale(3,3);
    }

    spriteNube[0].setPosition(620,-1040);
    spriteNube[1].setPosition(0,-1350);
    spriteNube[2].setPosition(620,-1560);


    spritePlataforma[0].setPosition(0,-585);
    spritePlataforma[1].setPosition(205,-585);
    spritePlataforma[2].setPosition(418,-585);
    spritePlataforma[3].setPosition(626,-585);
    spritePlataforma[4].setPosition(312,-680);
    spritePlataforma[5].setPosition(95,-752);
    spritePlataforma[6].setPosition(530,-752);
    spritePlataforma[7].setPosition(312,-875);
    spritePlataforma[8].setPosition(70,-920);
    spritePlataforma[9].setPosition(555,-920);
    spritePlataforma[10].setPosition(312,-1150);
    spritePlataforma[11].setPosition(160,-1257);
    spritePlataforma[12].setPosition(460,-1257);
    spritePlataforma[13].setPosition(160,-1448);
    spritePlataforma[14].setPosition(460,-1448);
    spritePlataforma[15].setPosition(143,-1665);
    spritePlataforma[16].setPosition(480,-1665);

        break;
    default:
        break;
    }

}

///DESTRUCTOR
Bonus::~Bonus(){
    delete texturaPlataforma;
    delete spritePlataforma;
    delete texturaNube;
    delete spriteNube;
    delete spriteAguilucho;
    delete direccionNubes;

    for(int i=0;i<11;i++){
        frutas[i].~Frutas();
    }
}

///MOVIMIENTO DE LA PLATAFORMA NUBE
void Bonus::MovimientoNube(){
 float moveSpeed=5.0f;
 int cantNubes;

 if(mapaBonus==1){
    cantNubes=2;
 }
 else{
    cantNubes=3;
 }

for(int i=0;i<cantNubes;i++){
    if(direccionNubes[i]==true){
    spriteNube[i].move(moveSpeed, 0);
    }
    if(direccionNubes[i]==false){
    spriteNube[i].move(-moveSpeed, 0);
    }


    if(spriteNube[i].getPosition().x==620){
    direccionNubes[i]=false;
    }

    if(spriteNube[i].getPosition().x==20){
    direccionNubes[i]=true;
    }

}

}

///MOVIMIENTO DEL AGUILUCHO
void Bonus::MovimientoAguilucho(){
    float moveSpeed=10.0f;


    if(direccionAguilucho==true){
        if (c2==0 || c2==1||c2==2){
            orientacionAncho=34;
            aux=5.88;
            orientacionAlto=18;
            aux2=11.7;
            aux3=35;
            aux4=19;
            c2++;

        }

        else if (c2==3 || c2==4 || c2==5){
            orientacionAncho=34;
            aux=4.70;
            orientacionAlto=16;
            aux2=13.25;
            aux3=35;
            aux4=16;
            c2++;
        }



        else if (c2==6){
            orientacionAncho=34;
            aux=3.52;
            orientacionAlto=16;
            aux2=13.25;
            aux3=35;
            aux4=16;
            c2=0;

        }


        moveSpeed=10.0f;
    }


    if(direccionAguilucho==false){
         if (c2==0 || c2==1||c2==2 ){
            orientacionAncho=34;
            aux=0;
            orientacionAlto=18;
            aux2=11.7;
            aux3=34;
            aux4=19;
            c2++;

        }
        else if (c2==3 || c2==4 || c2==5){
            orientacionAncho=34;
            aux=1.17;
            orientacionAlto=16;
            aux2=13.25;
            aux3=35;
            aux4=16;
            c2++;
        }
        else if (c2==6){
           orientacionAncho=34;
            aux=2.35;
            orientacionAlto=16;
            aux2=13.25;
            aux3=35;
            aux4=16;
            relojAguilucho.restart();
            c2=0;
        }

        moveSpeed=-10.0f;

    }

    spriteAguilucho->move(moveSpeed,0);

    if(spriteAguilucho->getPosition().x==620){
    direccionAguilucho=false;
    }


    if(spriteAguilucho->getPosition().x==20){
    direccionAguilucho=true;
    }


    IntRect rectAguilucho(orientacionAncho*aux, orientacionAlto*aux2, aux3, aux4);
    spriteAguilucho->setTextureRect(rectAguilucho);

}

#endif // CLSBONUS_H_INCLUDED
