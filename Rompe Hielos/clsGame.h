#ifndef CLSGAME_H_INCLUDED
#define CLSGAME_H_INCLUDED

///CLASE GAME PRINCIPAL
class Game {
  private:
    int v=3, modo, guardarVidas[2]={3,3}, guardarPersonaje[2]={0,0};
    RenderWindow *ventana1;
    View cam;
    int fps, tipoCamara=0, ganarBonus=0, lastAlive;
    const float vCam=-30.0f;
    Texture *fondo;
    Sprite *sFondo;
    Player *jugador;
    Enemigos *enemigos;
    Plataforma *base;
    Bonus *bonus;
    Menu *menuPrincipal, *menuPausa, *menuSeleccion;
    Puntajes *puntaje;
    bool salir, bonusOn, salirPuntajes, pause, camaraPartida, cambiaDireccion=false, elegirDireccion, playMusic[5]={false,false,false,false,false}, animacionAguilucho=false, animacionGameOver=false;
    Clock relojRenacio[2], bonusTimer, relojAguilucho;
    Sonidos efectos, musica;

    bool stop[2]={false, false};

    Numeros *timer;
    int decena, unidad, contadorTimer=40;

  public:
    ///CONSTRUCTOR
    Game();

    ///METODOS
    void gameLoop();
    void controller();
    void checkCam(RenderWindow *ventana1, View &cam);
    void colision();
    void estados();
    void deleteStage();
    void createStage();
    void MenuPrincipal();
    void MenuPausa();
    void MenuPersonajes();
    void Partida(int);
    void Puntuacion();
    void maximoPuntaje();
    void bonusStage();
    void aguiluchoInicio();
    void gameOver(int);

    ///DESTRUCTOR
    ~Game();
};

///CONSTRUCTOR
Game::Game() {
    ventana1=new RenderWindow(VideoMode(770,600), "Rompe Hielos");
    jugador = new Player[2];
    cam = View(FloatRect(0,0,770,600));
    enemigos = new Enemigos[7];
    menuPrincipal = new Menu(1);
    menuPausa = new Menu(2);
    menuSeleccion = new Menu(3);
    puntaje = new Puntajes[2];

    ///SE DEFINE EL PISO EN EL QUE ESTA CADA ENEMIGO AL SER CREADO CADA OBJETO ENEMIGO
    for (int i=0;i<7;i++){
        enemigos[i].setPlataforma(i);
        enemigos[i].textpiso();
    }

    bonus = new Bonus;
    timer = new Numeros[6];
    base=new Plataforma;
    fondo = new Texture;
    fondo->loadFromFile("Imagenes/Mapa.png");
    sFondo = new Sprite(*fondo);
    sFondo->setPosition(0,-2000);
    sFondo->setScale(3,3);

    fps=30;
    ventana1 -> setFramerateLimit(fps);

    camaraPartida=false;
    bonusOn = false;
    pause=false;
    salir=false;
    salirPuntajes=false;
}

///DESTRUCTOR
Game::~Game() {
    delete jugador;
    delete base;
    delete fondo;
    delete sFondo;
    delete enemigos;
    delete menuPrincipal;
    delete menuPausa;
    delete menuSeleccion;
    delete bonus;
    delete timer;

}

///METODOS
///LOOP DEL JUEGO
void Game::gameLoop() {

    while (ventana1->isOpen()) {
        ventana1->clear();
        MenuPrincipal();

        switch (menuPrincipal->getOpciones()){
            puntaje[0].setDibujarPuntajeM(false);
            case 1:
                modo=1;
                if(puntaje[0].getPuntajeTotal()==0){
                MenuPersonajes();
                guardarPersonaje[0]=jugador[0].getPersonaje();
                }
                Partida(modo);
                break;
            case 2:
                modo=2;
                if(puntaje[0].getPuntajeTotal()==0){
                MenuPersonajes();
                guardarPersonaje[0]=jugador[0].getPersonaje();
                guardarPersonaje[1]=jugador[1].getPersonaje();
                }
                Partida(modo);
                break;
            case 3:
                controller();
            default:
                break;
        }

        if(salir==true){
            if(pause==false){
                puntaje[0].calcularPuntaje();
                if(modo==2){
                    puntaje[1].calcularPuntaje();
                }
                if(ganarBonus==1){
                    puntaje[0].setPuntajeTotal(puntaje[0].getPuntajeTotal()+2000);
                }
                else if(ganarBonus==2){
                    puntaje[1].setPuntajeTotal(puntaje[1].getPuntajeTotal()+2000);
                }

                if(modo==1){
                    if(jugador[0].getVidas()<0){
                        gameOver(1);
                    }
                }
                else{
                    if(jugador[1].getVidas()<0 && jugador[0].getVidas()<0){
                    gameOver(lastAlive);
                    }
                }

                while(salirPuntajes==false){
                    controller();
                    Puntuacion();
                    Sleep(16);
                }
            }
                deleteStage();
                createStage();
                salirPuntajes=false;
        }

        ventana1->display();
    }

}

///EVENTOS
void Game::controller() {
    Event *event;
    event=new Event;

    while (ventana1->pollEvent(*event)) {

        switch (event->type) {

        case sf::Event::KeyPressed:
            //Cierre del juego presionando la tecla ESCAPE
            if (Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                ventana1->close();
            }

            //Salir desde el menu principal
            if (menuPrincipal->getOpciones()==3){
                ventana1->close();
            }

            //EFECTOS DE SONIDO MENU SELECCION PERSONAJES
            if(modo==1){
                if((Keyboard::isKeyPressed(sf::Keyboard::Left) || Keyboard::isKeyPressed(sf::Keyboard::Right)) && jugador[0].getPersonaje()==0) {
                    efectos.seleccionarEfecto(1);
                }

                if(Keyboard::isKeyPressed(sf::Keyboard::RShift) && menuPrincipal->getOpciones()!=0 && jugador[0].getPersonaje()==0){
                    efectos.seleccionarEfecto(3);
                }
            }
            else{
                if((Keyboard::isKeyPressed(sf::Keyboard::Left) || Keyboard::isKeyPressed(sf::Keyboard::Right)) && (jugador[0].getPersonaje()==0 && jugador[1].getPersonaje()==0)) {
                    efectos.seleccionarEfecto(1);
                }

                if(Keyboard::isKeyPressed(sf::Keyboard::RShift) && menuPrincipal->getOpciones()!=0 && (jugador[0].getPersonaje()==0 && jugador[1].getPersonaje()==0)){
                    efectos.seleccionarEfecto(3);
                }
            }


            //Pausa
            if(modo==1){
                if((menuPrincipal->getOpciones()==1 || menuPrincipal->getOpciones()==2) && jugador[0].getPersonaje()!=0 && animacionAguilucho==true && animacionGameOver==false){
                    if (Keyboard::isKeyPressed(sf::Keyboard::P)) {
                        efectos.seleccionarEfecto(3);
                        if(pause == false){
                            pause=true;
                            if (bonusOn==false){
                            musica.pausarMusica(2);
                            }
                            else{
                            musica.pausarMusica(5);
                            }
                        }
                        else{
                            pause=false;
                            if (bonusOn==false){
                            musica.seleccionarMusica(2);
                            }
                            else{
                            musica.seleccionarMusica(5);
                            }

                        }
                    }
                }
            }
            else{
                if((menuPrincipal->getOpciones()==1 || menuPrincipal->getOpciones()==2) && (jugador[0].getPersonaje()!=0 && jugador[1].getPersonaje()!=0) && animacionAguilucho==true && animacionGameOver==false){
                if (Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    efectos.seleccionarEfecto(3);
                    if(pause == false){
                        pause=true;
                        if (bonusOn==false){
                        musica.pausarMusica(2);
                        }
                        else{
                        musica.pausarMusica(5);
                        }
                    }
                    else{
                        pause=false;
                        if (bonusOn==false){
                        musica.seleccionarMusica(2);
                        }
                        else{
                        musica.seleccionarMusica(5);
                        }

                    }
                }
            }
            }


            //Continuar al menu principal al estar en puntajes
            if(salir==true){
                if (Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    salirPuntajes=true;
                }
            }

        break;

        //Cierre del juego presionando la "X" de la ventana
        case Event::Closed:
            ventana1->close();
            exit(1);
        break;

        default:
            break;
        }


        //SE CHEQUEA LA CAMARA AL INICIAR LA PARTIDA
        if(modo==1){
            if(menuPrincipal->getOpciones()!=0 && jugador[0].getPersonaje()!=0 && animacionAguilucho==true && animacionGameOver==false){
                checkCam(ventana1,cam);
            }
        }
        else{
            if(menuPrincipal->getOpciones()!=0 && (jugador[0].getPersonaje()!=0 && jugador[1].getPersonaje()!=0) && animacionAguilucho==true && animacionGameOver==false){
                checkCam(ventana1,cam);
            }
        }
    }
    delete event;
}

///ANIMACION AGUILUCHO INICIO
void Game::aguiluchoInicio(){
    Texture *textura;
    Sprite *sprite;
    int c=0, tam;
    Clock *stopFly;
    Font *fuente;
    Text *texto;

    stopFly = new Clock;

    fuente = new Font;
    fuente -> loadFromFile("Fuentes Tipografia/arcade_ya/ARCADE_N.ttf");
    texto = new Text;
    texto -> setFont(*fuente);
    texto -> setScale(0.8,0.8);
    texto -> setColor(Color::Red);
    texto -> setString("CROOOOOAAAAAAR!!!");
    texto -> setPosition(200, -1940);

    textura = new Texture;
    textura -> loadFromFile("Imagenes/Sprites.png");
    sprite = new Sprite(*textura);
    sprite -> setScale(3,3);
    sprite -> setPosition(330, 500);

    musica.seleccionarMusica(4);

    while(animacionAguilucho==false){
        float aux=-1, aux2=0, aux3=0, aux4=0, orientacionAncho=0, orientacionAlto=0;
        float flySpeed=12.0f;
        controller();
        ventana1 -> clear();
        ventana1->draw(*sFondo);

         for (int i=0; i<7; i++) {
            if (i==0) {
                tam=22;
            }
            else if (i==1||i==2||i==3) {
                tam=20;
            }
            else if (i==4||i==5||i==6) {
               tam=20;
            }
            for (int j=0; j<tam; j++) {
            ventana1->draw(base->getSprite(i,j));
            }
         }

        for(int i=0;i<14;i++){
            ventana1->draw(base->getSpriteIrrompibles(i));
        }

         bonusStage();

         for(int i=0; i<7; i++){
         ventana1->draw(enemigos[i].getSprite());
         enemigos[i].update(jugador[0].getDireccion());
         }

        if (c==0 || c==1||c==2){
            orientacionAncho=34;
            aux=3.55;
            orientacionAlto=29;
            aux2=8.11;
            aux3=34;
            aux4=30;
            c++;
        }

        else if (c==3 || c==4 || c==5){
            orientacionAncho=33;
            aux=4.85;
            orientacionAlto=30;
            aux2=7.86;
            aux3=34;
            aux4=30;
            c++;
        }

        else if (c==6){
            orientacionAncho=34;
            aux=5.91;
            orientacionAlto=32;
            aux2=7.34;
            aux3=34;
            aux4=32;
            c=0;
        }


        if(sprite->getPosition().y!=-1900){
        sprite->move(0,-flySpeed);
        stopFly->restart();
        }
        else if(stopFly->getElapsedTime().asSeconds()<3){
            if(stopFly->getElapsedTime().asMilliseconds()<100){
                efectos.seleccionarEfecto(8);
            }
            else if(stopFly->getElapsedTime().asMilliseconds()>250){
                ventana1 -> draw(*texto);
            }
        }
        else{
            animacionAguilucho=true;
        }

        if(sprite->getPosition().y<310){
        this->cam.setCenter(385,sprite->getPosition().y);
        }
        ventana1->setView(cam);

        IntRect rect(orientacionAncho*aux, orientacionAlto*aux2, aux3, aux4);
        sprite->setTextureRect(rect);
        ventana1 -> draw(*sprite);

        ventana1 -> display();
    }
    delete textura;
    delete sprite;
    delete fuente;
    delete texto;
    delete stopFly;

    cam = View(FloatRect(0,0,770,600));
    ventana1->setView(cam);
}

///ANIMACION GAME OVER
void Game::gameOver(int lastAlive){
    Texture *textura;
    Sprite *sprite;
    Clock *stopGame;

    stopGame = new Clock;
    textura = new Texture;
    textura -> loadFromFile("Imagenes/GameOver.png");
    sprite = new Sprite(*textura);
    sprite -> setScale(0.3,0.3);

    if(lastAlive==1){
        sprite -> setPosition(215, jugador[0].getSprite().getPosition().y+170);
    }
    else{
        sprite -> setPosition(215, jugador[1].getSprite().getPosition().y+170);
    }

    while(animacionGameOver==false){
        float flySpeed=5.0f;
        int tam;
        controller();
        ventana1 -> clear();

        ventana1->draw(*sFondo);

         for (int i=0; i<7; i++) {
            if (i==0) {
                tam=22;
            }
            else if (i==1||i==2||i==3) {
                tam=20;
            }
            else if (i==4||i==5||i==6) {
               tam=20;
            }
            for (int j=0; j<tam; j++) {
                if(base->getEstado(i,j)==true){
                    ventana1->draw(base->getSprite(i,j));
                }
            }
         }

        for(int i=0;i<14;i++){
            ventana1->draw(base->getSpriteIrrompibles(i));
        }

         bonusStage();

         for(int i=0; i<7; i++){
            if(enemigos[i].getEstado()==true){
                ventana1->draw(enemigos[i].getSprite());
                enemigos[i].update(jugador[0].getDireccion());
            }
         }


        if(sprite->getPosition().y > cam.getCenter().y-100){
        sprite -> move(0, -flySpeed);
        stopGame->restart();
        }
        else if(stopGame->getElapsedTime().asSeconds() < 5){
            if(stopGame->getElapsedTime().asMilliseconds() < 50){
                efectos.seleccionarEfecto(7);
            }
        }
        else{
            animacionGameOver=true;
        }

        ventana1->setView(cam);

        ventana1 -> draw(*sprite);

        ventana1 -> display();
    }
    delete textura;
    delete sprite;
    delete stopGame;

    cam = View(FloatRect(0,0,770,600));
    ventana1->setView(cam);

    animacionGameOver=false;
}

///PARTIDA (MODO UN JUGADOR / MODO DOS JUGADORES)
void Game::Partida(int modo){
    musica.stopMusica(1);

    if(animacionAguilucho==false){
        aguiluchoInicio();
    }
    animacionAguilucho=true;
    musica.stopMusica(4);
    musica.seleccionarMusica(2);
    //MODO UN JUGADOR
    if(modo==1){
        while(salir==false){
            ventana1->clear();
            controller();
            ventana1->setView(cam);
            if(!pause){
                ventana1->draw(*sFondo);

                if(ganarBonus==0){
                jugador[0].update(1,false);
                relojAguilucho.restart();
                }
                else{
                    if(relojAguilucho.getElapsedTime().asSeconds()>5 && relojAguilucho.getElapsedTime().asSeconds()>2){
                    salir=true;
                    musica.stopMusica(3);

                    }
                }

                estados();
                colision();
                bonusStage();

            }
            if(pause==true){
                MenuPausa();
            }
            ventana1->display();
        }


    }
    //MODO DOS JUGADORES
    else{
        while(salir==false){
            if (playMusic[1]==false){
                    musica.seleccionarMusica(2);
                    playMusic[1]=true;
                }
            controller();
            ventana1->setView(cam);
            ventana1->clear();

            if(!pause){
                ventana1->draw(*sFondo);
                for(int i=0;i<2;i++){
                    if(ganarBonus==0){
                        jugador[i].update(i+1,true);
                        relojAguilucho.restart();
                    }
                    else{
                        if(relojAguilucho.getElapsedTime().asSeconds()>5 && relojAguilucho.getElapsedTime().asSeconds()>2){
                            musica.stopMusica(3);
                            salir=true;
                        }
                    }
                }

                estados();
                colision();
                bonusStage();
            }
            if(pause==true){
                MenuPausa();
            }
            ventana1->display();
        }

    }
}

///AL FINALIZAR UNA PARTIDA, BORRA TODO PARA EMPEZAR UNA NUEVA
void Game::deleteStage(){

    if(salir==true){
        if(pause==false){
            if(modo==1){
                guardarVidas[0]=jugador[0].getVidas();
            }
            else{
                for(int i=0;i<2;i++){
                    guardarVidas[i]=jugador[i].getVidas();
                }
            }
        }
        else{
            for(int i=0;i<2;i++){
                    guardarVidas[i]=3;
            }
        }
    }


    delete base;
    delete jugador;
    delete enemigos;
    delete bonus;
    delete timer;
    delete menuPrincipal;
    delete menuSeleccion;

//    Al salir del menu de puntajes y eliminar todo, setea todo en 0 para la proxima partida, y guarda en disco el puntaje del jugador anterior
    if(salir==true && pause==false){
        if(modo==1){
                puntaje[0].setAcumularPuntaje(false);
                puntaje[0].leerPuntaje();
                puntaje[0].grabarPuntaje();
                puntaje[0].setDibujarPuntaje(false);
                if(jugador[0].getVidas()<0){
                    puntaje[0].setPuntajeTotal(0);
                }

        }
        else{
            for(int i=0;i<2;i++){
                puntaje[i].setAcumularPuntaje(false);
                puntaje[i].leerPuntaje();
                puntaje[i].grabarPuntaje();
                puntaje[i].setDibujarPuntaje(false);


            }
                if(jugador[0].getVidas()<0 && jugador[1].getVidas()<0){
                    for(int i=0;i<2;i++){
                        puntaje[i].setPuntajeTotal(0);
                    }
                }
        }
    }
    else if(pause == true && salir == true){
        delete puntaje;
    }

}

///AL EMPEZAR OTRA PARTIDA, RECREA LO ELIMINADO
void Game::createStage(){
    ventana1->setFramerateLimit(30);
    menuPrincipal = new Menu(1);
    menuSeleccion = new Menu(3);
    base = new Plataforma;
    jugador = new Player[2];
    if(pause==false && salir==true){
        if(modo==1){
            if(guardarVidas[0]<0){
                guardarVidas[0]=3;
                guardarPersonaje[0]=0;
                puntaje = new Puntajes[2];
                animacionAguilucho=false;
            }
            else{
                jugador[0].setPersonaje(guardarPersonaje[0]);
                menuPrincipal->setOpciones(1);
            }

            jugador[0].setVidas(guardarVidas[0]);
        }
        else{
            if(guardarVidas[0]<0 && guardarVidas[1]<0){
                for(int i=0;i<2;i++){
                    guardarVidas[i]=3;
                    guardarPersonaje[0]=0;
                }
                puntaje = new Puntajes[2];
                animacionAguilucho=false;
            }

            else{
                for(int i=0;i<2;i++){
                jugador[i].setPersonaje(guardarPersonaje[i]);
                }
                menuPrincipal->setOpciones(2);
            }

            for(int i=0;i<2;i++){
                jugador[i].setVidas(guardarVidas[i]);
            }
        }
    }
    else if(pause==true && salir==true){
        puntaje = new Puntajes[2];
        animacionAguilucho=false;
    }

    enemigos = new Enemigos[7];
    for (int i=0;i<7;i++){
        enemigos[i].setPlataforma(i);
        enemigos[i].textpiso();
    }
    bonus = new Bonus;
    timer = new Numeros[6];
    contadorTimer=40;
    salir=false;
    bonusOn=false;
    camaraPartida=false;
    tipoCamara=0;
    ganarBonus=0;
    pause=false;

    delete menuPausa;
    menuPausa = new Menu(2);

    for (int i=0;i<5;i++){
        playMusic[i]=false;
    }

}

///MENU PRINCIPAL
void Game::MenuPrincipal(){

    if (playMusic[0]==false){
    musica.seleccionarMusica(1);
    playMusic[0]=true;
    }
    controller();

    ventana1->draw(menuPrincipal->getSprite());
    ventana1->draw(menuPrincipal->getHammer());

    puntaje[0].maximoPuntaje(ventana1);

    menuPrincipal->hammerMove(1);


}

///MENU PAUSA
void Game::MenuPausa(){
    ventana1->clear();
    controller();
    cam = View(FloatRect(0,0,770,600));
    ventana1->setView(cam);
    ventana1->draw(menuPausa->getSprite());
    ventana1->draw(menuPausa->getHammer());
    menuPausa->hammerMove(2);

    if(menuPausa->getOpciones()==1){
        efectos.seleccionarEfecto(3);
        if (bonusOn==false){
            musica.seleccionarMusica(2);
        }
        else{
            musica.seleccionarMusica(5);
        }
        pause=false;
        checkCam(ventana1, cam);
        menuPausa->setOpciones(0);
    }
    else if(menuPausa->getOpciones()==2){
        salir=true;
    }
}

///MENU SELECCIONA DE PERSONAJES
void Game::MenuPersonajes(){
    musica.stopMusica(1);
    if(modo==1){
        while(jugador[0].getPersonaje()==0){
            cam = View(FloatRect(0,0,770,600));
            ventana1->setView(cam);
            ventana1->clear();
            controller();
            ventana1->draw(menuSeleccion->getSprite());
            menuSeleccion->seleccionarPersonaje(jugador, modo, ventana1);
            ventana1->display();
        }
    }
    else{
        for(int i=0;i<2;i++){
            while(jugador[i].getPersonaje()==0){
                cam = View(FloatRect(0,0,770,600));
                ventana1->setView(cam);
                ventana1->clear();
                controller();
                ventana1->draw(menuSeleccion->getSprite());
                menuSeleccion->seleccionarPersonaje(jugador, modo, ventana1);
                ventana1->display();
            }
        }
    }

}

///MENU PUNTAJES
void Game::Puntuacion(){

    cam = View(FloatRect(0,0,770,600));
    ventana1->setView(cam);
    ventana1->clear();

    puntaje[0].seleccionarMenuPuntajes(ventana1, modo, jugador, ganarBonus);

        if(modo==1){
        puntaje[0].dibujarPuntaje(ventana1, 100);
        }
        else{
        puntaje[0].dibujarPuntaje(ventana1, 100);
        puntaje[1].dibujarPuntaje(ventana1, 415);
        }

    puntaje[0].animacionPuntajes(ventana1, modo, jugador, ganarBonus);

    ventana1->display();

}

///ESTADOS DEL JUGADOR (VIVO, MUERTO, DIBUJAR / RESTAR VIDAS) Y DIBUJO DE LOS ENEMIGOS / JUGADOR
void Game::estados(){
    if(modo==1){

            jugador[1].setEstado(false);

            if (jugador[0].getDibujaPlayer()==true && jugador[0].getEstado()==true){
            ventana1->draw(jugador[0].getSprite());
            }


            if(jugador[0].getSprite().getPosition().y>cam.getCenter().y+300){
                //ESTANDO FUERA DEL BONUS
                if(bonusOn==false){
                    if (jugador[0].getMurio()==false){
                        jugador[0].setMurio(true);
                        relojRenacio[0].restart();
                    }
                        jugador[0].morir();
                }

                //ESTANDO DENTRO DEL BONUS
                else{
                    salir=true;
                    musica.stopMusica(5);

                }
            }
            else if(bonusOn==true && contadorTimer==0 ){
                salir=true;
                musica.stopMusica(5);

            }


            for(int i=0;i<14;i++){
                ventana1->draw(base->getSpriteIrrompibles(i));
            }


            for (int x=0;x<3;x++){
                if (jugador[0].getEstadoVida(x)==true&&bonusOn==false){
                    ventana1->draw(jugador[0].getSpriteVida(x));
                }
            }

            if (jugador[0].getVidas()<0){
                salir=true;
                musica.stopMusica(2);

                jugador[0].setEstado(false);
            }


            for(int i=0; i<7;i++){
                if(enemigos[i].getEstado()==true){
                ventana1->draw(enemigos[i].getSprite());
                enemigos[i].update(jugador[0].getDireccion());
                }

            }

            if(jugador[0].getSprite().getPosition().y<-650 && cam.getCenter().y-200 < -650 && jugador[0].getIsGrounded()==true){
                    bonusOn=true;
                    if (playMusic[4]==false){
                        musica.stopMusica(2);
                        musica.seleccionarMusica(5);
                        playMusic[4]=true;
                    }
            }


    }
    else{
        for(int i=0;i<14;i++){
                ventana1->draw(base->getSpriteIrrompibles(i));
            }

        for(int i=0;i<2;i++){
            if (jugador[i].getDibujaPlayer()==true && jugador[i].getEstado()==true){
            ventana1->draw(jugador[i].getSprite());
            }

            //ESTANDO DENTRO DEL BONUS
            if(bonusOn==true){
                if(jugador[i].getSprite().getPosition().y>cam.getCenter().y+300){
                    jugador[i].setEstado(false);
                }
            }
            //ESTANDO FUERA DEL BONUS
            else{
               if(jugador[i].getSprite().getPosition().y>cam.getCenter().y+300){
                    if (jugador[i].getMurio()==false){
                        jugador[i].setMurio(true);
                        relojRenacio[i].restart();
                    }
                    jugador[i].morir();
               }
            }

            for (int x=0;x<3;x++){
                if (jugador[i].getEstadoVida(x)==true&&bonusOn==false){
                ventana1->draw(jugador[i].getSpriteVida(x));
                }
            }

            if(jugador[i].getVidas()<0){
                jugador[i].setEstado(false);
            }

        }

            ///SETEA EL BONUS EN TRUE AL PISAR EL SEGUNDO PISO DEL BONUS
            if(jugador[0].getVidas()>0 && jugador[1].getVidas()>0){
                if((jugador[0].getSprite().getPosition().y<-650 && jugador[1].getSprite().getPosition().y<-650) && cam.getCenter().y-200 < -650 && (jugador[0].getIsGrounded()==true && jugador[1].getIsGrounded()==true)){
                    bonusOn=true;
                    if (playMusic[4]==false){
                        musica.stopMusica(2);
                        musica.seleccionarMusica(5);
                        playMusic[4]=true;
                    }
                }
            }
            else if(jugador[0].getVidas()>=0 && jugador[1].getVidas()<0){
                if(jugador[0].getSprite().getPosition().y<-650 && cam.getCenter().y-200 < -650 && jugador[0].getIsGrounded()==true){
                    bonusOn=true;
                    if (playMusic[4]==false){
                        musica.stopMusica(2);
                        musica.seleccionarMusica(5);
                        playMusic[4]=true;
                    }
                }
            }
            else if(jugador[1].getVidas()>=0 && jugador[0].getVidas()<0){
                if(jugador[1].getSprite().getPosition().y<-650 && cam.getCenter().y-200 < -650 && jugador[1].getIsGrounded()==true){
                    bonusOn=true;
                    if (playMusic[4]==false){
                        musica.stopMusica(2);
                        musica.seleccionarMusica(5);
                        playMusic[4]=true;
                    }
                }
            }


            if(jugador[0].getVidas()<0 && jugador[1].getVidas()>-1){
                lastAlive=2;
            }
            if(jugador[1].getVidas()<0 && jugador[0].getVidas()>-1){
                lastAlive=1;
            }


            ///SI SE MUEREN LOS DOS, SALE
            if (jugador[0].getVidas()<0 && jugador[1].getVidas()<0){
                salir=true;
                musica.stopMusica(2);

            }

            ///SI LOS DOS CAEN DENTRO DEL BONUS, SALE
            if(bonusOn==true){
                if((jugador[0].getSprite().getPosition().y>cam.getCenter().y+300 && jugador[1].getSprite().getPosition().y>cam.getCenter().y+300) || contadorTimer==0){
                    salir=true;
                    musica.stopMusica(5);

                }
            }

            for(int i=0; i<7;i++){
                if(enemigos[i].getEstado()==true){
                ventana1->draw(enemigos[i].getSprite());
                enemigos[i].update(jugador[elegirDireccion].getDireccion());
                }
            }

    }

}

///SEGUIMIENTO Y MOVIMIENTO DE CAMARA
void Game::checkCam(RenderWindow *ventana1, View &cam){

    if(modo==1){
        tipoCamara=1;
    }
    else{
        if((jugador[0].getVidas()<0 && jugador[1].getVidas()>=0) || (jugador[0].getEstado()==false && jugador[1].getEstado()==true)){
            tipoCamara=2;
        }
        else if((jugador[1].getVidas()<0 && jugador[0].getVidas()>=0) || (jugador[1].getEstado()==false && jugador[0].getEstado()==true) ){
            tipoCamara=1;
        }
        else{
            tipoCamara=3;
        }
    }

    switch (tipoCamara){
    case 1:
        if(ventana1->hasFocus()){
            if(jugador[0].getSprite().getPosition().y<200){
                if(jugador[0].getMurio()==false&&jugador[0].getIsGrounded()==true&&jugador[0].getEstado()==true){
                    if(this->cam.getCenter().y>jugador[0].getSprite().getPosition().y+87){
                        if(bonusOn==false){
                        if(camaraPartida==false){
                                cam = View(FloatRect(0,0,770,600));
                                camaraPartida=true;
                            }
                            else{
                                this->cam.setCenter(385,jugador[0].getSprite().getPosition().y+87);
                            }
                        }
                        else{
                            this->cam.setCenter(385,jugador[0].getSprite().getPosition().y-200);
                        }

                        jugador[0].posicionarVidas(cam.getCenter().y-290, 1, guardarVidas);
                    }
                }
            }
            else{
               jugador[0].posicionarVidas(cam.getCenter().y-290, 1, guardarVidas);
            }
        }
        break;
    case 2:
        if(ventana1->hasFocus()){
            if(jugador[1].getSprite().getPosition().y<200){
                if(jugador[1].getMurio()==false&&jugador[1].getIsGrounded()==true){
                    if(this->cam.getCenter().y>jugador[1].getSprite().getPosition().y+87){
                        if(bonusOn==false){
                        if(camaraPartida==false){
                                cam = View(FloatRect(0,0,770,600));
                                camaraPartida=true;
                            }
                            else{
                                this->cam.setCenter(385,jugador[1].getSprite().getPosition().y+87);
                            }
                        }
                        else{
                            this->cam.setCenter(385,jugador[1].getSprite().getPosition().y-200);
                        }

                        jugador[1].posicionarVidas(cam.getCenter().y-290, 2, guardarVidas);
                    }
                }
            }
            else{
               jugador[1].posicionarVidas(cam.getCenter().y-290, 2, guardarVidas);
            }
        }
        break;
    case 3:
         if(ventana1->hasFocus()){
            if(jugador[0].getSprite().getPosition().y<200 && jugador[1].getSprite().getPosition().y<200 ){
                if((jugador[0].getMurio()==false&&jugador[0].getIsGrounded()==true) && (jugador[1].getMurio()==false&&jugador[1].getIsGrounded()==true)){
                    if(this->cam.getCenter().y>jugador[0].getSprite().getPosition().y+87 && this->cam.getCenter().y>jugador[1].getSprite().getPosition().y+87){
                        if(bonusOn==false){
                            if(camaraPartida==false){
                                cam = View(FloatRect(0,0,770,600));
                                camaraPartida=true;
                            }
                            else{
                                this->cam.setCenter(385,jugador[0].getSprite().getPosition().y+87);
                            }
                        }
                        else{
                            this->cam.setCenter(385,jugador[0].getSprite().getPosition().y-200);
                        }

                        for(int i=0;i<2;i++){
                            jugador[i].posicionarVidas(cam.getCenter().y-290, i+1, guardarVidas);
                        }
                    }
                }
            }
            else{
                for(int i=0;i<2;i++){
                    jugador[i].posicionarVidas(cam.getCenter().y-290, i+1, guardarVidas);
                }
            }
        }
        break;
    default:
        break;
    }

}

///DIBUJA EL BONUS STAGE
void Game::bonusStage(){
int cantPlat, cantNubes;

        if(bonus->getMapaBonus()==1){
            cantPlat=15;
            cantNubes=2;
        }
        else{
            cantPlat=17;
            cantNubes=3;
        }
            for(int i=0;i<cantPlat;i++){
                ventana1->draw(bonus->getSpritePlataforma(i));
            }
            for(int i=0;i<cantNubes;i++){
                ventana1->draw(bonus->getSpriteNube(i));
            }
            for(int i=0;i<11;i++){
                if (bonus->getEstadoFruta(i)==true){
                ventana1->draw(bonus->getSpriteFruta(i));
                }
            }

            if(animacionAguilucho==true){
            ventana1->draw(bonus->getSpriteAguilucho());
            }

            if(ganarBonus==0){
            bonus->MovimientoAguilucho();
            }


            if(bonusOn==true){
                unidad=contadorTimer%10;
                decena=contadorTimer/10;

                //TIMER 1
                timer[0].seleccionNumero(decena,100,-1130);
                ventana1->draw(timer[0].getSprite());

                timer[1].seleccionNumero(unidad,125,-1130);
                ventana1->draw(timer[1].getSprite());

                //TIMER 2
                timer[2].seleccionNumero(decena,45,-760);
                ventana1->draw(timer[2].getSprite());

                timer[3].seleccionNumero(unidad,70,-760);
                ventana1->draw(timer[3].getSprite());

                //TIMER 3
                timer[4].seleccionNumero(decena,95,-1770);
                ventana1->draw(timer[4].getSprite());

                timer[5].seleccionNumero(unidad,120,-1770);
                ventana1->draw(timer[5].getSprite());

                if(bonusTimer.getElapsedTime().asMilliseconds()>1000){
                    if(ganarBonus==0){
                    contadorTimer--;
                    bonusTimer.restart();
                    }
                }
            }

            if(ganarBonus==0){
            bonus->MovimientoNube();
            }
}

///FUNCION COLISIONES
void Game::colision() {
    bool piso[2]={false,false};
    int tam;

    for(int n=0;n<2;n++){

    if(jugador[n].getEstado()==true){

        ///RESPAWN CON TIEMPO DE INMUNIDAD
        if (jugador[n].getRenacio()==true){
            if (relojRenacio[n].getElapsedTime().asMilliseconds()>5000){
                jugador[n].setRenacio(false);
            }
            else{
                int acum=0,acum2=250;
                for (int i=0;i<10;i++){
                    if (relojRenacio[n].getElapsedTime().asMilliseconds()>acum&&relojRenacio[n].getElapsedTime().asMilliseconds()<acum2){
                        jugador[n].setDibujaPlayer(false);
                    }
                    acum+=250;
                    acum2+=250;
                    if (relojRenacio[n].getElapsedTime().asMilliseconds()>acum&&relojRenacio[n].getElapsedTime().asMilliseconds()<acum2){
                        jugador[n].setDibujaPlayer(true);
                    }
                    acum+=250;
                    acum2+=250;
                }
            }
        }


        ///COLISIONES BONUS STAGE
        int tipoMapa=bonus->getMapaBonus(), cantPlat, cantNubes;
        switch (tipoMapa){
        case 1:
            cantPlat=15;
            cantNubes=2;

            for (int i=0;i<cantPlat;i++){
                if (jugador[n].getSprite().getGlobalBounds().intersects(bonus->getSpritePlataforma(i).getGlobalBounds())) {
                    if(jugador[n].getSprite().getPosition().y<bonus->getSpritePlataforma(i).getPosition().y){
                        jugador[n].setGround(bonus->getSpritePlataforma(i).getPosition().y-54);
                    }
                    else{
                        jugador[n].setVelocidad(10,0);
                    }
                }
                else{
                    if(bonusOn==true){
                        if(jugador[n].getSprite().getPosition().y < -600 && i==4){
                            jugador[n].setGround(bonus->getSpritePlataforma(3).getPosition().y);
                        }
                    }
                    else{
                        if(i==0){
                           if(jugador[n].getSprite().getPosition().y < bonus->getSpritePlataforma(0).getPosition().y-50){
                                   jugador[n].setGround(-320);
                           }
                        }
                    }

                }

            }


            for (int i=0;i<cantNubes;i++){
                if (jugador[n].getSprite().getGlobalBounds().intersects(bonus->getSpriteNube(i).getGlobalBounds())) {
                    if(jugador[n].getSprite().getPosition().y<bonus->getSpriteNube(i).getPosition().y){
                        jugador[n].setGround(bonus->getSpriteNube(i).getPosition().y-54);
                        jugador[n].setDirecNube(bonus->getDireccionNubes(i));
                        jugador[n].setSeguir(i, true);
                    }
                    else{
                        jugador[n].setVelocidad(10,0);
                    }
                }
                else{
                jugador[n].setSeguir(i,false);
                }
            }


            break;

        case 2:
            cantPlat=17;
            cantNubes=3;

             for (int i=0;i<cantPlat;i++){
                if (jugador[n].getSprite().getGlobalBounds().intersects(bonus->getSpritePlataforma(i).getGlobalBounds())) {
                    if(jugador[n].getSprite().getPosition().y<bonus->getSpritePlataforma(i).getPosition().y){
                         jugador[n].setGround(bonus->getSpritePlataforma(i).getPosition().y-54);
                    }
                    else{
                        jugador[n].setVelocidad(10,0);
                    }
                }
                else{
                    if(bonusOn==true){
                        if(jugador[n].getSprite().getPosition().y < -600 && i==4){
                            jugador[n].setGround(bonus->getSpritePlataforma(3).getPosition().y);
                        }
                    }
                    else{
                        if(i==0){
                           if(jugador[n].getSprite().getPosition().y < bonus->getSpritePlataforma(0).getPosition().y-50){
                                   jugador[n].setGround(-320);
                           }
                        }
                    }

                }

            }

            for (int i=0;i<cantNubes;i++){
                if (jugador[n].getSprite().getGlobalBounds().intersects(bonus->getSpriteNube(i).getGlobalBounds())) {
                    if(jugador[n].getSprite().getPosition().y<bonus->getSpriteNube(i).getPosition().y){
                        jugador[n].setGround(bonus->getSpriteNube(i).getPosition().y-54);
                        jugador[n].setDirecNube(bonus->getDireccionNubes(i));
                        jugador[n].setSeguir(i, true);
                    }
                    else{
                        jugador[n].setVelocidad(10,0);
                    }
                }
                else{
                jugador[n].setSeguir(i,false);
                }
            }

            break;

        default:
            break;

        }

        ///AGARRAR FRUTAS
        for(int i=0;i<11;i++){
            if (jugador[n].getSprite().getGlobalBounds().intersects(bonus->getSpriteFruta(i).getGlobalBounds())&&bonus->getEstadoFruta(i)==true){
                if(bonus->getEstadoFruta(i)==true){
                    efectos.seleccionarEfecto(6);
                }
                bonus->setEstadoFruta(i,false);
                ///SUMAR ACUMULADOR DE PUNTOS
                puntaje[n].setCantFrutas(puntaje[n].getCantFrutas()+1);

            }
        }

        ///GANAR BONUS AL CHOCAR CONTRA AGUILUCHO
        if (jugador[n].getSprite().getGlobalBounds().intersects(bonus->getSpriteAguilucho().getGlobalBounds())){
            ganarBonus=n+1;
            if (playMusic[3]==false){
            musica.stopMusica(5);
            musica.seleccionarMusica(3);
            playMusic[3]=true;
            }
        }

    }

            for (int i=0; i<7; i++) {

                ///DEPENDIENDO EL PISO, SE REGULA LA CANTIDAD DE BLOQUES DE LA PLATAFORMA
                if (i==0) {
                    tam=22;
                } else if (i==1||i==2||i==3) {

                    tam=20;

                } else if (i==4||i==5||i==6) {
                   tam=20;
                }

                for (int j=0; j<tam; j++) {
                        Vector2f v;
                        v.x=10;
                        v.y=0;



                if(jugador[n].getEstado()==true){

                    ///ROMPER BLOQUES AL SALTAR
                    if (jugador[n].getSprite().getGlobalBounds().intersects(base->getSprite(i,j).getGlobalBounds())) {
                        if(jugador[n].getIsGrounded()==false &&jugador[n].getSprite().getPosition().y>base->getSprite(i,j).getPosition().y) {
                            if(jugador[n].getRompio()==false) {
                                if (base->getEstado(i,j)==true){
                                    base->setEstado(false,i,j);
                                    jugador[n].setRompio(true);
                                    puntaje[n].setCantBloques(puntaje[n].getCantBloques()+1);
                                    jugador[n].setVelocidad(10,0);
                                    efectos.seleccionarEfecto(1);

                                    ///SI EL JUGADOR ROMPE UN BLOQUE Y HAY UN ENEMIGO, ESTE SE CAE Y ES ELIMINADO
                                    if (base->getSprite(i,j).getGlobalBounds().intersects(enemigos[i].getSprite().getGlobalBounds())){
                                        puntaje[n].setCantEnemigos(puntaje[n].getCantEnemigos()+1);
                                        enemigos[i].setCaida(true);
                                        enemigos[i].setGolpeado(true);
                                        efectos.seleccionarEfecto(2);
                                    }
                                }
                            }
                        }
                    }


                    ///CAER AL HABER UNA PLATAFORMA ROTA
                    if (jugador[n].getSprite().getGlobalBounds().intersects(base->getSprite(i,j).getGlobalBounds())) {
                        if(jugador[n].getSprite().getPosition().y<base->getSprite(i,j).getPosition().y){
                            if(base->getEstado(i,j)==true||piso[n]==true){
                                piso[n]=true;
                                jugador[n].setGround(base->getSprite(i,j).getPosition().y-45);
                                jugador[n].setRompio(true);
                            }
                            else{
                                jugador[n].setRompio(true);
                                if(jugador[n].getSprite().getPosition().y>300&&jugador[n].getSprite().getPosition().y<400){
                                jugador[n].setGround(515);
                                }

                                if(jugador[n].getSprite().getPosition().y>200&&jugador[n].getSprite().getPosition().y<300){
                                jugador[n].setGround(385);
                                }

                                if(jugador[n].getSprite().getPosition().y>50&&jugador[n].getSprite().getPosition().y<150){
                                jugador[n].setGround(240);
                                }

                                if(jugador[n].getSprite().getPosition().y>-100&&jugador[n].getSprite().getPosition().y<0){
                                jugador[n].setGround(80);
                                }

                                if(jugador[n].getSprite().getPosition().y>-300&&jugador[n].getSprite().getPosition().y<-80){
                                jugador[n].setGround(-60);
                                }

                                if(jugador[n].getSprite().getPosition().y>-400&&jugador[n].getSprite().getPosition().y<-300){
                                jugador[n].setGround(-190);
                                }

                                if(jugador[n].getSprite().getPosition().y>-500&&jugador[n].getSprite().getPosition().y<-400){
                                jugador[n].setGround(-320);
                                }


                            }
                        }
                    }

                    ///COLISION ENEMIGOS AL GOLPEAR
                    if(jugador[n].getHit()==true){
                        if(jugador[n].getSprite().getGlobalBounds().intersects(enemigos[i].getSprite().getGlobalBounds())){
                            efectos.seleccionarEfecto(2);
                            enemigos[i].setGolpeado(true);
                            elegirDireccion=n;

                            if(enemigos[i].getTipo()!=3 && stop[n]==false && enemigos[i].getMurio()==false){
                            puntaje[n].setCantEnemigos(puntaje[n].getCantEnemigos()+1);
                            stop[n]=true;
                            }

                            if(enemigos[i].getTipo()==3){
                                enemigos[i].setReloj();
                            }
                        }
                    }

                    else if (jugador[n].getHit()==false&&jugador[n].getSprite().getGlobalBounds().intersects(enemigos[i].getSprite().getGlobalBounds())&&enemigos[i].getGolpeado()==false&&jugador[n].getRenacio()==false){
                        if(jugador[n].getMurio()==false){
                            efectos.seleccionarEfecto(4);
                        }
                        jugador[n].setMurio(true);
                        relojRenacio[n].restart();



                    }
                    else if(jugador[n].getHit()==false){
                        stop[n]=false;
                    }
                }

                ///DIBUJA LAS PLATAFORMAS
                if(base->getEstado(i,j)==true) {
                   ventana1->draw(base->getSprite(i,j));
                }


                ///SI FUE GOLPEADO Y AL SALIR DISPARADO CHOCA CON UN PISO VACIO, CAE
                if(base->getEstado(i,j)==false&& base->getSprite(i,j).getGlobalBounds().intersects(enemigos[i].getSprite().getGlobalBounds())&&enemigos[i].getMurio()==true){
                    enemigos[i].setCaida(true);
                }

                ///SI HAY UN BLOQUE ROTO EN LA PLATAFORMA, EL ENEMIGO CAMBIA DE DIRECCION
                if(n==0){
                    if(enemigos[i].getSprite().getGlobalBounds().intersects(base->getSprite(i,j).getGlobalBounds())){
                        if(base->getEstado(i,j)==false){
                            if(enemigos[i].getDireccion()==false && cambiaDireccion==false){
                            enemigos[i].posicionarRebote();
                            cambiaDireccion=true;
                            }
                            else if (enemigos[i].getDireccion()==true && cambiaDireccion==false){
                            enemigos[i].posicionarRebote();
                            cambiaDireccion=true;
                            }
                        }
                        else{
                            cambiaDireccion=false;
                        }

                    }
                }


            }
            ///TERMINA EL FOR POR BLOQUE


        }
        ///TERMINA EL FOR POR PLATAFORMA

        ///LIMITES DE LOS BORDES DE LAS PLATAFORMAS PRINCIPALES
        for(int i=0;i<14;i++){
            if(jugador[n].getSprite().getGlobalBounds().intersects(base->getSpriteIrrompibles(i).getGlobalBounds())){
                if(jugador[n].getSprite().getPosition().y<base->getSpriteIrrompibles(i).getPosition().y){
                    jugador[n].setGround(base->getSpriteIrrompibles(i).getPosition().y-55);
                }
                else{
                    jugador[n].setVelocidad(10,0);
                }
            }
        }

        ///RECIEN CUANDO VUELVE A TOCAR EL PISO PUEDE VOLVER A ROMPER BLOQUES
        if(jugador[n].getIsGrounded()==true){
            jugador[n].setRompio(false);
        }

    }
    ///TERMINA EL FOR DE JUGADORES


}


#endif // CLSGAME_H_INCLUDED
