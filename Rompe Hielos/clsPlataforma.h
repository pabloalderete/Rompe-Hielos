#ifndef CLSPLATAFORMA_H_INCLUDED
#define CLSPLATAFORMA_H_INCLUDED

///CLASE DE LAS PLATAFORMAS / PISOS
class Plataforma{
private:
    Texture *textura, *texturaIrrompibles;
    Sprite **sprite, *spriteIrrompibles;
    Vector2f posicion, velocidad;
    bool estado[7][22];

public:
    ///CONSTRUCTOR
    Plataforma();

    ///GETS
    Sprite getSprite(int x,int y){return sprite[x][y];}
    Sprite getSpriteAll(){return **sprite;}
    Sprite getSpriteIrrompibles(int i){return spriteIrrompibles[i];}
    bool getEstado(int x, int y){return estado[x][y];}

    ///SETS
    void setEstado(bool e, int x, int y){estado[x][y]=e;}

    ///METODOS

    ///DESTRUCTOR
    ~Plataforma();
};

///CONSTRUCTOR
Plataforma::Plataforma(){
    textura=new Texture;
    textura->loadFromFile("Imagenes/Sprites.png");
    sprite=new Sprite*[7];
    for(int i=0; i<7; i++){
        sprite[i]=new Sprite[22];
    }

    IntRect rect(10*39.7, 10*19, 10, 10);
    posicion.x=108;
    posicion.y=418;
    int acumy=0;
    for (int i=0;i<7;i++){
        int acumx=0;
        int color1,color2,color3;
        if (i==0){
            color1= 200;
            color2= 255;
            color3= 0;
        }
        else if (i==1||i==2||i==3){
            if (i==2 || i==3){
                acumy+=1;
            }

            posicion.x=134;
            color1= 240;
            color2= 80;
            color3= 0;


        }
        else if (i==4||i==5||i==6){
            color1= 255;
            color2= 255;
            color3= 255;
        }

        for(int j=0;j<22;j++){
            Color color (color1,color2,color3);
            sprite[i][j].setTexture(*textura);
            sprite[i][j].setTextureRect(rect);
            sprite[i][j].setRotation(45.f);
            sprite[i][j].setScale(3,3);
            sprite[i][j].setColor(color);
            sprite[i][j].setPosition(posicion.x+acumx , posicion.y-acumy);
            acumx+=26;
            estado[i][j]=true;

        }
        acumy+=144;
    }

    texturaIrrompibles = new Texture;
    texturaIrrompibles -> loadFromFile("Imagenes/Mapa.png");
    spriteIrrompibles = new Sprite[14];
    IntRect rectIrrompibles(48*4.35,8*77,48,8);

    int acumxIrrom=0, acumyIrrom=0;

    for(int i=0; i<14; i++){
        int color1,color2,color3;
        if(i<2){
            if(i==0){
                acumxIrrom=-48;
            }
            else{
                acumxIrrom=670;
            }

            acumyIrrom=424;

            color1= 200;
            color2= 255;
            color3= 0;
        }
        else if(i<8){
            if(i%2==0){
                acumxIrrom=-24;
            }
            else{
                acumxIrrom=646;
            }

            if(i==2 || i==3){
                acumyIrrom=280;
            }
            else if(i==4 || i==5){
                acumyIrrom=136;
            }
            else{
                acumyIrrom=-8;
            }


            color1= 240;
            color2= 80;
            color3= 0;
        }
        else{
            if(i%2==0){
                acumxIrrom=0;
            }
            else{
                acumxIrrom=622;
            }

            if(i==8 || i==9){
                acumyIrrom=-152;
            }
            else if(i==10 || i==11){
                acumyIrrom=-296;
            }
            else{
                acumyIrrom=-440;
            }


            color1= 255;
            color2= 255;
            color3= 255;
        }

        Color color (color1, color2, color3);

        spriteIrrompibles[i].setTexture(*texturaIrrompibles);
        spriteIrrompibles[i].setTextureRect(rectIrrompibles);
        spriteIrrompibles[i].setScale(3,3);
        spriteIrrompibles[i].setColor(color);
        spriteIrrompibles[i].setPosition(acumxIrrom, acumyIrrom);

    }
}

///DESTRUCTOR
Plataforma::~Plataforma(){
    delete textura;
    delete sprite;
}

#endif // CLSPLATAFORMA_H_INCLUDED
