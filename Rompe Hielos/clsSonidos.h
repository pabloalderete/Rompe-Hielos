#ifndef CLSSONIDOS_H_INCLUDED
#define CLSSONIDOS_H_INCLUDED

///CLASE DE EFECTOS DE SONIDO
class Sonidos{
private:
    SoundBuffer romperBloque, matarEnemigo, pausa, perderVida, salto, agarrarFruta, gameOver, rugidoAguilucho;
    Sound SromperBloque, SmatarEnemigo, Spausa, SperderVida, Ssalto, SagarrarFruta, SgameOver, SrugidoAguilucho;
    Music menuMusic, gameMusic, subeAguilucho, agarrarAguilucho, bonusMusic;
public:
    ///CONSTRUCTOR
    Sonidos();

    ///SETS

    ///GETS

    ///METODOS
    void seleccionarEfecto(int);
    void seleccionarMusica(int);
    void pausarMusica(int);
    void stopMusica(int);

    ///DESTRUCTOR
    ~Sonidos(){};
};

///CONSTRUCTOR
Sonidos::Sonidos(){
    if(!romperBloque.loadFromFile("Musica/Efectos/RomperBloque.wav")){
        cout << "Error";
    }

    if(!matarEnemigo.loadFromFile("Musica/Efectos/MatarEnemigo.wav")){
        cout << "Error";
    }

    if(!pausa.loadFromFile("Musica/Efectos/Pausa.wav")){
        cout << "Error";
    }

    if(!perderVida.loadFromFile("Musica/Efectos/PerderVida.wav")){
        cout << "Error";
    }

    if(!salto.loadFromFile("Musica/Efectos/Salto.wav")){
        cout << "Error";
    }

    if(!agarrarFruta.loadFromFile("Musica/Efectos/AgarrarFruta.wav")){
        cout << "Error";
    }

    if(!gameOver.loadFromFile("Musica/Efectos/GameOver.wav")){
        cout << "Error";
    }
    if(!rugidoAguilucho.loadFromFile("Musica/Efectos/RugidoAguilucho.wav")){
        cout << "Error";
    }
    if(!menuMusic.openFromFile("Musica/Musica/menuAndBonus.wav")){
        cout << "Error";
    }
    if(!gameMusic.openFromFile("Musica/Musica/gameMusic.wav")){
        cout << "Error";
    }
    if(!agarrarAguilucho.openFromFile("Musica/Musica/agarrarAguilucho.wav")){
        cout << "Error";
    }
    if(!subeAguilucho.openFromFile("Musica/Musica/subeAguilucho.wav")){
        cout << "Error";
    }
    if(!bonusMusic.openFromFile("Musica/Musica/menuAndBonus.wav")){
        cout << "Error";
    }

    SromperBloque.setBuffer(romperBloque);
    SmatarEnemigo.setBuffer(matarEnemigo);
    Spausa.setBuffer(pausa);
    SperderVida.setBuffer(perderVida);
    Ssalto.setBuffer(salto);
    SagarrarFruta.setBuffer(agarrarFruta);
    SgameOver.setBuffer(gameOver);
    SrugidoAguilucho.setBuffer(rugidoAguilucho);
}

///SELECCIONAR EFECTO DE SONIDO
void Sonidos::seleccionarEfecto(int efecto){
    switch (efecto){
    case 1:
        SromperBloque.play();
        SromperBloque.setVolume(40);
        break;
    case 2:
        SmatarEnemigo.play();
        SmatarEnemigo.setVolume(40);
        break;
    case 3:
        Spausa.play();
        break;
    case 4:
        SperderVida.play();
        SperderVida.setVolume(40);
        break;
    case 5:
        Ssalto.play();
        Ssalto.setVolume(40);
        break;
    case 6:
        SagarrarFruta.play();
        break;
    case 7:
        SgameOver.setVolume(80);
        SgameOver.play();
        break;
    case 8:
        SrugidoAguilucho.play();
        break;
    default:
        break;
    }
}

///SELECIONAR MUSICA
void Sonidos::seleccionarMusica(int musica){
    switch (musica){
    case 1:
        menuMusic.play();
        menuMusic.setLoop(true);
        break;
    case 2:
        gameMusic.play();
        gameMusic.setLoop(true);
        break;
    case 3:
        agarrarAguilucho.play();
        break;
    case 4:
        subeAguilucho.play();
        break;
    case 5:
        bonusMusic.play();
        break;
    default:
        break;
    }
}

///PAUSA MUSICA
void Sonidos::pausarMusica(int pausa){

    switch (pausa){
    case 1:
        menuMusic.pause();
        break;
    case 2:
        gameMusic.pause();
        break;
    case 3:
        agarrarAguilucho.pause();
        break;
    case 4:
        subeAguilucho.pause();
        break;
    case 5:
        bonusMusic.pause();
        break;
    default:
        break;
    }

}

///PARAR MUSICA
void Sonidos::stopMusica(int stop){
   switch (stop){
    case 1:
        menuMusic.stop();
        break;
    case 2:
        gameMusic.stop();
        break;
    case 3:
        agarrarAguilucho.stop();
        break;
    case 4:
        subeAguilucho.stop();
        break;
    case 5:
        bonusMusic.stop();
        break;
    default:
        break;
    }

}

#endif // CLSSONIDOS_H_INCLUDED
