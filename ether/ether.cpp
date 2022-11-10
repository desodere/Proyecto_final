#include "ether.h"
#include "ui_ether.h"
#include <QMouseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer();


    connect(timer, &QTimer::timeout, this, &MainWindow::detectar);

    timer_turno = new QTimer();


    connect(timer_turno, &QTimer::timeout, this, &MainWindow::iniciarReloj);
//    connect(timer, &QTimer::timeout, this, &MainWindow::posible_desplazamiento);
    x = 0;
    y = 0;

    //Configurando tamaño de la pantalla
   QRect Desktop = QApplication::desktop()->screenGeometry();
    x = Desktop.x();
    y = Desktop.y();
    ancho = Desktop.width()/1.92;
    alto = Desktop.height()/1.55;
//    ancho = Desktop.width()/2.92;
//    alto = Desktop.height()/1.55;
    scene = new QGraphicsScene(x, y, ancho, alto);

    //iniciando tablero
    int in1 = 0;
    int in2 = 0;
//    J1 = new Personaje(QPixmap(":/Imagenes/fantasma.png"));
    for (int i = 0; i < matriz.size(); i++)
    {
        for (int j = 0; j < matriz[i].size(); j++)
        {
           // qDebug()  << "i "<<i<< " j "<<j;
 //           J1->matriz[i][j]=matriz[i][j];
            casilla[i][j]= new Casilla(matriz[i][j],100,100,in2,in1,QPixmap(""));
            scene->addItem(casilla[i][j]);
            in1= in1 +100;
        }
        in1 = 0;
        in2 = in2 +100;
    }

//    //Creo las fichas
//    fantasma = new Ficha(QPixmap(":/fantasma.png"),1,150,250);
//    humano = new Ficha(QPixmap(":/humano.png"),2,150,350);
//    asura = new Ficha(QPixmap(":/asura.png"),3,150,450);



////    Ficha *fantasma22 = new Ficha(QPixmap(":/Imagenes/fantasma.png"),3);
//    //Agrego las fichas al jugador
//    fichasJ1.agregar(fantasma);
//    fichasJ1.agregar(humano);
//    fichasJ1.agregar(asura);


//    scene->addItem(fantasma);
//    scene->addItem(humano);
//    scene->addItem(asura);

 //   fantasma->setPos(150,250);
//    humano->setPos(150,350);
//    asura->setPos(150,450);
    //jugador 1
    fichasJ1.agregar(*casilla[1][2]);
    fichasJ1.agregar(*casilla[1][3]);
    fichasJ1.agregar(*casilla[1][4]);

    //jugador 2
    fichasJ2.agregar(*casilla[8][2]);
    fichasJ2.agregar(*casilla[8][3]);
    fichasJ2.agregar(*casilla[8][4]);




    ui->graphicsView->setScene(scene);
    ui->jugador1->setPixmap(QPixmap(":/jugador1.png"));
    ui->jugador2->setPixmap(QPixmap(":/jugador2.png"));

     derecha = false;
     izquierda = false;
     arriba = false;
     abajo = false ;
     desplazamiento = 0;
     fPasos = 0;
     fx = 0;
     fy = 0;
     fx2 = 0;
     fy2 = 0;
     contador_reloj = 0;
     numero_turnos = 0;
//     qDebug()  << "j1 "<<fichasJ1.bando<< " j2 "<<fichasJ2.bando;
//     fichasJ1.imprimir();
//     fichasJ2.imprimir();
     //conecto el boton
     inicio = false;
   //  ui->btn_inicio->setIcon(QIcon(QPixmap(":/boton.png")));
     connect(ui->btn_inicio, &QPushButton::released, this, &MainWindow::comenzar_partida);


     ///////////////  animacion de los cuerpos
     sceneJ1 = new QGraphicsScene(-90, -365, 180, 730);
     sceneJ2 = new QGraphicsScene(-90, -365, 180, 730);
     ui->graphicsView_J1->setScene(sceneJ1);
     ui->graphicsView_J2->setScene(sceneJ2);
     timer_cuerpo = new QTimer();
    limite_ancho = 4500;
    limite_alto = 10500;
   //  timer->start(1);


     connect(timer_cuerpo, &QTimer::timeout, this, &MainWindow::Actualizacion);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dibujar()
{
    scene->clear();
    //iniciando tablero
    int in1 = 0;
    int in2 = 0;
    for (int i = 0; i < matriz.size(); i++)
    {
        for (int j = 0; j < matriz[i].size(); j++)
        {
//            qDebug()  << "i "<<i<< " j "<<j;
 //           J1->matriz[i][j]=matriz[i][j];
            casilla[i][j]= new Casilla(matriz[i][j],100,100,in2,in1,QPixmap(""));
            casilla[i][j]->setSeleccionada(false);
            scene->addItem(casilla[i][j]);
            in1= in1 +100;
        }
        in1 = 0;
        in2 = in2 +100;
    }

     //ui->Reloj->setText(QString(contador_reloj));
}

bool MainWindow::detectar()
{
    bool c = false ;
    if(inicio){

        //desplazamiento = 0 : busco casillas seleccionadas
        if(desplazamiento == 0){
            for (int i = 0; i < matriz.size(); i++)
            {
                for (int j = 0; j < matriz[i].size(); j++)
                {
                    //                if(desplazamiento == 1){
                    //                    casilla[i][j]->setSeleccionada(false);
                    //                }
                    if(casilla[i][j]->getSeleccionada() ){
                        if(casilla[i][j]->getEstado()<3){
                            casilla[i][j]->setSeleccionada(false);
                            fx = 0;
                            fy = 0;
                            fPasos = 0;
                            desplazamiento = 0;
                        }else{
                            fx = casilla[i][j]->getX();
                            fy = casilla[i][j]->getY();
                            if(fichasJ1.turno){
                                vector<Casilla>::iterator it;
                                for (it = fichasJ1.fichas.begin(); it != fichasJ1.fichas.end(); ++it){
                                    qDebug()  << "it->getX() "<<it->getX()<< " it->getY() "<<it->getY();
                                    if(casilla[i][j]->getX()==it->getX() and casilla[i][j]->getY()==it->getY()){
                                        //fichasJ1.fichas
                                        //casilla[i][j]->setSeleccionada(true);
                                        qDebug()  << "getSeleccionada j1";
//                                        fx = casilla[i][j]->getX();
//                                        fy = casilla[i][j]->getY();
                                        qDebug()  << "fx "<<fx<< " fy "<<fy;
                                        desplazamiento = 1 ;
                                        fPasos = casilla[i][j]->getCosto_paso();

                                        posible_desplazamiento(fPasos);
                                        break;
                                    }
                                }
                            }else{
                                vector<Casilla>::iterator it2;
                                for (it2 = fichasJ2.fichas.begin(); it2 != fichasJ2.fichas.end(); ++it2){
                                    qDebug()  << "it->getX() "<<it2->getX()<< " it->getY() "<<it2->getY();
                                    if(casilla[i][j]->getX()==it2->getX() and casilla[i][j]->getY()==it2->getY()){
                                        //fichasJ1.fichas
                                        casilla[i][j]->setSeleccionada(true);
                                        qDebug()  << "getSeleccionada j2";
//                                        fx = casilla[i][j]->getX();
//                                        fy = casilla[i][j]->getY();
                                        qDebug()  << "fx "<<fx<< " fy "<<fy;
                                        desplazamiento = 1 ;
                                        fPasos = casilla[i][j]->getCosto_paso();

                                        posible_desplazamiento(fPasos);
                                        break;
                                    }
                                }
                            }
                            break;

                        }
                    }


                }

            }
        }else if(desplazamiento==1){
            //        if(casilla[fx/100][fy/100]->getSeleccionada()!=true){
            //            qDebug()  << " n000000000o  getSeleccionada "<< casilla[fx/100][fy/100]->getSeleccionada();
            //            casilla[fx/100][fy/100]->setSeleccionada(true);
            //        }

            if(casilla[fx/100][fy/100]->getSeleccionada()!=false and casilla[fx/100][fy/100]->getEstado()!=1){
                qDebug()  << "fx "<<fx<< " fy "<<fy;
                qDebug()  << " no  getSeleccionada "<< casilla[fx/100][fy/100]->getSeleccionada();
                desplazamiento = 0 ;
                qDebug()  << " noooo   getSeleccionada ";
//                posible_desplazamiento(fPasos);
//                dibujar();
                limpiar_tablero();
            }else{
                qDebug()  << " sigo Seleccionada ";
                qDebug()  << "fx "<<fx<< " fy "<<fy;
                qDebug()  << " yo "<< casilla[fx/100][fy/100]->getSeleccionada();
                for (int i = 0; i < matriz.size(); i++)
                {
                    for (int j = 0; j < matriz[i].size(); j++)
                    {
                        //                if(desplazamiento == 1){
                        //                    casilla[i][j]->setSeleccionada(false);
                        //                }
                        if(casilla[i][j]->getSeleccionada()==true and (casilla[i][j]->getX()!=fx or casilla[i][j]->getY()!=fy) ){
                            qDebug()  << "  Seleccionada una diferente ";
                            qDebug()  << " nueva "<< casilla[i][j]->getX() <<"  x, y "<< casilla[i][j]->getX();
                            if(casilla[i][j]->getEstado()!=2){
                                qDebug()  << "  esta no se puede ";
                                casilla[i][j]->setSeleccionada(false);
                                fx2 = 0;
                                fy2 = 0;
                                fPasos = 0;
                                limpiar_tablero();
                               // desplazamiento = 0;
                            }else{
                                fx2 = casilla[i][j]->getX();
                                fy2 = casilla[i][j]->getY();
                                qDebug()  << " otra "<< casilla[fx2/100][fy2/100]->getSeleccionada();
                                bool agregar = true;
                                if(fichasJ1.turno){
                                    vector<Casilla>::iterator it;

                                    for (it = fichasJ1.fichas.begin(); it != fichasJ1.fichas.end(); ++it){
                                        qDebug()  << "it->getX() "<<it->getX()<< " it->getY() "<<it->getY();
                                        if(casilla[i][j]->getX()==it->getX() and casilla[i][j]->getY()==it->getY()){
//                                            //fichasJ1.fichas
//                                            //casilla[i][j]->setSeleccionada(true);
//                                            qDebug()  << "getSeleccionada ";
//                                            fx2 = casilla[i][j]->getX();
//                                            fy2 = casilla[i][j]->getY();
//                                            qDebug()  << "fx2 "<<fx2<< " fy2 "<<fy2;
                                            desplazamiento = 0 ;
                                            qDebug()  << "  ya esta agregada ";
                                            agregar = false;
                                            limpiar_tablero();
                                            break;

                                        }
//                                        else{
//                                            matriz[i][j] = casilla[fx/100][fy/100]->getEstado();
//                                            casilla[i][j]->setEstado( casilla[fx/100][fy/100]->getEstado());
//                                            fichasJ1.agregar(*casilla[i][j]);
//                                             qDebug()  << "gooooolll 1";
//                                             limpiar_tablero();
//                                        }
                                    }
                                    if(agregar){

                                        if(fichasJ1.agregar(*casilla[i][j])){
                                            matriz[i][j] = casilla[fx/100][fy/100]->getEstado();
                                            casilla[i][j]->setEstado( casilla[fx/100][fy/100]->getEstado());
                                            qDebug()  << "gooooolll 1";
                                            fichasJ1.pa = fichasJ1.pa - ((abs((fx-fx2) - (fy-fy2)) / 100) * casilla[fx/100][fy/100]->getCosto_paso());
                                        }

                                         limpiar_tablero();
                                    }
                                }else{
                                    vector<Casilla>::iterator it2;
                                    for (it2 = fichasJ2.fichas.begin(); it2 != fichasJ2.fichas.end(); ++it2){
                                        qDebug()  << "it->getX() "<<it2->getX()<< " it->getY() "<<it2->getY();
                                        if(casilla[i][j]->getX()==it2->getX() and casilla[i][j]->getY()==it2->getY()){
//                                            //fichasJ1.fichas
//                                            casilla[i][j]->setSeleccionada(true);
//                                            qDebug()  << "getSeleccionada ";
//                                            fx2 = casilla[i][j]->getX();
//                                            fy2 = casilla[i][j]->getY();
//                                            qDebug()  << "fx2 "<<fx2<< " fy2 "<<fy2;
                                            desplazamiento = 0 ;
                                            qDebug()  << "  ya esta agregada ";
                                            agregar = false;
                                            limpiar_tablero();
                                            break;
//                                            fPasos = casilla[i][j]->getCosto_paso();

//                                            posible_desplazamiento(fPasos);
//                                            break;
                                        }
//                                        else{
//                                            matriz[i][j] = casilla[fx/100][fy/100]->getEstado();
//                                        casilla[i][j]->setEstado( casilla[fx/100][fy/100]->getEstado());
//                                         qDebug()  << "gooooolll 2";
//                                         fichasJ2.agregar(*casilla[i][j]);
//                                         limpiar_tablero();
//                                    }

                                    }
                                    if(agregar){

                                     if(fichasJ2.agregar(*casilla[i][j])){
                                         matriz[i][j] = casilla[fx/100][fy/100]->getEstado();
                                     casilla[i][j]->setEstado( casilla[fx/100][fy/100]->getEstado());
                                      qDebug()  << "gooooolll 2";
                                      fichasJ2.pa = fichasJ2.pa - ((abs((fx-fx2) - (fy-fy2)) / 100) * casilla[fx/100][fy/100]->getCosto_paso());
                                     }
                                     limpiar_tablero();
                                    }
                                }
//                                break;


                            }
                            desplazamiento = 0;
                            break;
                        }


                    }

                }
            }
            //            qDebug() << " espero que la desseleccionen";
            //            if(numero_turnos % 2){
            //                vector<Casilla>::iterator it;
            //                for (it = fichasJ1.fichas.begin(); it != fichasJ1.fichas.end(); ++it){
            //                    qDebug()  << "it->getX() "<<it->getX()<< " it->getY() "<<it->getY();
            //                    if(casilla[fx/100][fy/100]->getX()==it->getX() and casilla[fx/100][fy/100]->getY()==it->getY()){
            //                        qDebug()  << "fx "<<fx<< " fy "<<fy;
            //                        qDebug()  << "  getSeleccionada "<< casilla[fx/100][fy/100]->getSeleccionada();
            //                        desplazamiento = 0 ;
            //                        qDebug()  << " noooo   getSeleccionada ";
            //                        posible_desplazamiento(fPasos);

            //                    }
            //                }
            //            }else{
            //                vector<Casilla>::iterator it2;
            //                for (it2 = fichasJ2.fichas.begin(); it2 != fichasJ2.fichas.end(); ++it2){
            //                    qDebug()  << "it->getX() "<<it2->getX()<< " it->getY() "<<it2->getY();
            //                    if(casilla[fx/100][fy/100]->getX()==it2->getX() and casilla[fx/100][fy/100]->getY()==it2->getY()){
            //                        qDebug()  << "fx "<<fx<< " fy "<<fy;
            //                        qDebug()  << "  getSeleccionada "<< casilla[fx/100][fy/100]->getSeleccionada();
            //                        desplazamiento = 0 ;
            //                        qDebug()  << " noooo   getSeleccionada ";
            //                        posible_desplazamiento(fPasos);
            //                    }
            //                }
            //            }
            //        }
        }else if(desplazamiento==2){

        }

    }
    return  c ;
}

void MainWindow::posible_desplazamiento(int fPasos){//Valido caminos
    int se_puede_mover = 0 ;
    int jugada ;
    int pa = 0 ;
    qDebug()  << "fichasJ1.pa "<<fichasJ1.pa ;
    qDebug()  << "fPasos "<<fPasos ;


    if(fichasJ1.turno){
        jugada=1;
        pa = fichasJ1.pa;
        qDebug()  << "posible fichasJ1.pa "<<fichasJ1.pa ;
    }else
    if(fichasJ2.turno){
        jugada=2;
        pa = fichasJ2.pa;
        qDebug()  << " poesible fichasJ2.pa "<<fichasJ2.pa ;
    }


    if(desplazamiento==1){
        for(int i = 1; i<=pa/fPasos ; i++){
            qDebug()  << " i  "<< i  ;
            // para la derecha
            if(fx<800 and fx>=100){
                if((fx+(i*100))<=800 ){
                    derecha = true;
                }else{
                    derecha = false;
                }
                if (derecha){
                    //casilla[fx/100][fy/100]->setEstado(2);
                    if( casilla[(fx/100)+i][(fy/100)]->getEstado()-(3*jugada) >=0 and
                          casilla[(fx/100)+i][(fy/100)]->getEstado()-(3*jugada) >=0 )
                    {

                    }else{
                    casilla[(fx/100)+i][fy/100]->setEstado(2);
                    qDebug()  << "matriz[(fx/100)+1][fy/100]1 "<<matriz[(fx/100)+i][fy/100] ;
                    matriz[(fx/100)+i][fy/100] = 2;
                    qDebug()  << "matriz[(fx/100)+1][fy/100]d "<<matriz[(fx/100)+i][fy/100] ;
                    dibujar();
                    //                    casilla[fx+2][fy]->setEstado(4);
                    //                    casilla[fx+3][fy]->setEstado(4);
                    derecha = false;
                    se_puede_mover++;
                    }
                }
            }
            // para la izquierda
            if(fx<=800 and fx>100){
                qDebug()  << " ((fx-(i*100))>=100) "<<(fx-(i*100)) ;
                if((fx-(i*100))>=100){
                izquierda = true;
                }else{
                    izquierda = false;
                }
                if (izquierda){
                    //casilla[fx/100][fy/100]->setEstado(2);
                    if( casilla[(fx/100)-i][(fy/100)]->getEstado()-(3*jugada) >=0 and
                          casilla[(fx/100)-i][(fy/100)]->getEstado()-(3*jugada) >=0 )
                    {

                    }else{
                    casilla[(fx/100)-i][fy/100]->setEstado(2);
                    qDebug()  << "matriz[(fx/100)+1][fy/100]1 "<<matriz[(fx/100)-i][fy/100] ;
                    matriz[(fx/100)-i][fy/100] = 2;
                    qDebug()  << "matriz[(fx/100)+1][fy/100]d "<<matriz[(fx/100)-i][fy/100] ;
                    dibujar();
                    //                    casilla[fx+2][fy]->setEstado(4);
                    //                    casilla[fx+3][fy]->setEstado(4);
                    izquierda = false;
                    se_puede_mover++;
                    }
                }
            }
            // para la arriba
            if(fy<=500 and fy>100){
                if((fy-(i*100))>=100){
                arriba = true;
                }else{
                    arriba = false;
                }
                if (arriba){
                    //casilla[fx/100][fy/100]->setEstado(2);
                    if( casilla[(fx/100)][(fy/100)-i]->getEstado()-(3*jugada) >=0 and
                          casilla[(fx/100)][(fy/100)-i]->getEstado()-(3*jugada) >=0 )
                    {

                    }else{
                    casilla[(fx/100)][(fy/100)-i]->setEstado(2);
                    qDebug()  << "matriz[(fx/100)+1][fy/100]1 "<<matriz[(fx/100)][(fy/100)-i] ;
                    matriz[(fx/100)][(fy/100)-i] = 2;
                    qDebug()  << "matriz[(fx/100)+1][fy/100]d "<<matriz[(fx/100)][(fy/100)-i] ;
                    dibujar();
                    //                    casilla[fx+2][fy]->setEstado(4);
                    //                    casilla[fx+3][fy]->setEstado(4);
                    arriba = false;
                    se_puede_mover++;
                    }
                }
            }
            // para la abajo
            if(fy<500 and fy>=100){
                if((fy+(i*100))<=500){
                abajo = true;
                }else{
                    abajo = false;
                }
                if (abajo){
                    //casilla[fx/100][fy/100]->setEstado(2);
                    if( casilla[(fx/100)][(fy/100)+i]->getEstado()-(3*jugada) >=0 and
                          casilla[(fx/100)][(fy/100)+i]->getEstado()-(3*jugada) >=0 )
                    {

                    }else{
                    casilla[(fx/100)][(fy/100)+i]->setEstado(2);
                    qDebug()  << "matriz[(fx/100)+1][fy/100]1 "<<matriz[(fx/100)][(fy/100)+i] ;
                    matriz[(fx/100)][(fy/100)+i] = 2;
                    qDebug()  << "matriz[(fx/100)+1][fy/100]d "<<matriz[(fx/100)][(fy/100)+i] ;
                    dibujar();
                    //                    casilla[fx+2][fy]->setEstado(4);
                    //                    casilla[fx+3][fy]->setEstado(4);
                    abajo = false;
                    se_puede_mover++;
                    }
                }
            }
        }

    }/*else if(desplazamiento==0){
//        if(numero_turnos % 2 and fichasJ1.turno==false){
//            jugada=2;
//            pa = fichasJ1.pa;
//        }else{
//            jugada=1;
//            pa = fichasJ2.pa;
//        }
//        //BORAR POSIBLE CAMINOS

//            for(int i = 1; i<=pa/fPasos ; i++){
//                qDebug()  << " i  "<< i  ;
//                // para la derecha
//                if(fx<800 and fx>=100){
//                    if((fx+(i*100))<=800 and  (fx+(i*100))>=100){
//                        derecha = true;
//                    }
//                    if (derecha){
//                        if( casilla[(fx/100)+i][(fy/100)]->getEstado()-(3*jugada) >=0 and
//                              casilla[(fx/100)+i][(fy/100)]->getEstado()-(3*jugada) >=0 )
//                        {

//                        }else{

//                        casilla[(fx/100)+i][fy/100]->setEstado(0);
//                        qDebug()  << "matriz[(fx/100)+1][fy/100]1 "<<matriz[(fx/100)+i][fy/100] ;
//                        matriz[(fx/100)+i][fy/100] = 0;
//                        qDebug()  << "matriz[(fx/100)+1][fy/100]d "<<matriz[(fx/100)+i][fy/100] ;

//                        dibujar();
//                        derecha = false;
//                        }
//                    }
//                }
//                // para la izquierda
//                if(fx<=800 and fx>100){
//                    if((fx-(i*100))<=800 and  (fx-(i*100))>=100){
//                    izquierda = true;
//                    }
//                    if (izquierda){
//                        if( casilla[(fx/100)-i][(fy/100)]->getEstado()-(3*jugada) >=0 and
//                              casilla[(fx/100)-i][(fy/100)]->getEstado()-(3*jugada) >=0 )
//                        {

//                        }else{
//                        casilla[(fx/100)-i][fy/100]->setEstado(0);
//                        qDebug()  << "matriz[(fx/100)+1][fy/100]1 "<<matriz[(fx/100)-i][fy/100] ;
//                        matriz[(fx/100)-i][fy/100] = 0;
//                        qDebug()  << "matriz[(fx/100)+1][fy/100]d "<<matriz[(fx/100)-i][fy/100] ;

//                        dibujar();
//                        derecha = false;
//                        }
//                    }
//                }
//                // para la arriba
//                if(fy<=500 and fy>100){
//                    if((fy-(i*100))<=500 and  (fy-(i*100))>=100){
//                    arriba = true;
//                    }
//                    if (arriba){
//                        if( casilla[(fx/100)][(fy/100)-i]->getEstado()-(3*jugada) >=0 and
//                              casilla[(fx/100)][(fy/100)-i]->getEstado()-(3*jugada) >=0 )
//                        {

//                        }else{
//                        //casilla[fx/100][fy/100]->setEstado(2);
//                        casilla[(fx/100)][(fy/100)-i]->setEstado(0);
//                        qDebug()  << "matriz[(fx/100)+1][fy/100]1 "<<matriz[(fx/100)][(fy/100)-i] ;
//                        matriz[(fx/100)][(fy/100)-i] = 0;
//                        qDebug()  << "matriz[(fx/100)+1][fy/100]d "<<matriz[(fx/100)][(fy/100)-i] ;

//                        dibujar();
//                        arriba = false;
//                        }
//                    }
//                }
//                // para la abajo
//                if(fy<500 and fy>=100){
//                    if((fy+(i*100))<=500 and  (fy+(i*100))>=100){
//                    abajo = true;
//                    }
//                    if (abajo){
//                        if( casilla[(fx/100)][(fy/100)+i]->getEstado()-(3*jugada) >=0 and
//                              casilla[(fx/100)][(fy/100)+i]->getEstado()-(3*jugada) >=0 )
//                        {

//                        }else{
//                        //casilla[fx/100][fy/100]->setEstado(2);
//                        casilla[(fx/100)][(fy/100)+i]->setEstado(0);
//                        qDebug()  << "matriz[(fx/100)+1][fy/100]1 "<<matriz[(fx/100)][(fy/100)+i] ;
//                        matriz[(fx/100)][(fy/100)+i] = 0;
//                        qDebug()  << "matriz[(fx/100)+1][fy/100]d "<<matriz[(fx/100)][(fy/100)+i] ;
//                        dibujar();
//                        //                    casilla[fx+2][fy]->setEstado(4);
//                        //                    casilla[fx+3][fy]->setEstado(4);
//                        abajo = false;
//                        }
//                    }
//                }
//            }

        //iniciando tablero
        int in1 = 0;
        int in2 = 0;
    //    J1 = new Personaje(QPixmap(":/Imagenes/fantasma.png"));
        for (int i = 0; i < matriz.size(); i++)
        {
            for (int j = 0; j < matriz[i].size(); j++)
            {

     //           J1->matriz[i][j]=matriz[i][j];
                if( casilla[i][j]->getEstado()==2){
                    matriz[i][j] = 0;
                    casilla[i][j]->setEstado(0);

                    //qDebug()  << "i "<<i<< " j "<<j;
                }
                casilla[i][j]->setSeleccionada(false);
//                casilla[i][j]= new Casilla(matriz[i][j],100,100,in2,in1,QPixmap(""));
//                scene->addItem(casilla[i][j]);
                in1= in1 +100;
            }
            in1 = 0;
            in2 = in2 +100;
        }
    }

    */
    if(se_puede_mover<=0){
        desplazamiento = 0;
    }
}

void MainWindow::iniciarReloj()
{
if(inicio){
    contador_reloj++;


    if(contador_reloj>=5){



        if(numero_turnos % 2 == 0){
            ui->jugador1->show();
            ui->jugador2->hide();
            fichasJ1.turno = true;
            fichasJ2.turno = false;
            qDebug()  << "fichasJ1.turno " << fichasJ1.turno;
            animacionJ1();

        }else{
            ui->jugador1->hide();
            ui->jugador2->show();
            fichasJ1.turno = false;
            fichasJ2.turno = true;
            qDebug()  << "fichasJ2.turno " << fichasJ2.turno;
            limpiar();
        }

        if(fichasJ1.turno){
            fichasJ1.pa = fichasJ1.pa + 3;
//            fichasJ1.pa =  3;
            qDebug()  << "fichasJ1.pa " << fichasJ1.pa;
        }else
        if(fichasJ2.turno){
            fichasJ2.pa = fichasJ2.pa + 3;
//            fichasJ2.pa =  3;
            qDebug()  << "fichasJ2.pa " << fichasJ2.pa;
        }




        numero_turnos++;
        contador_reloj = 0;
        desplazamiento = 0;
        limpiar_tablero();
        //posible_desplazamiento(1);
    }




    ui->Reloj->setNum(contador_reloj);

    ui->btn_inicio->setText(QString(contador_reloj+48));

    ui->pa_jugador1->setNum(fichasJ1.pa);
    ui->pa_jugador2->setNum(fichasJ2.pa);

   // ui->btn_inicio->hide();
//    ui->btn_inicio->setIcon(QIcon(QString(contador_reloj+49)));
    //     qDebug()  << contador_reloj;

    // dibujar();
}
}

void MainWindow::limpiar_tablero()
{

    //limpio estados de las fichas de los jugadores

    scene->clear();
    //iniciando tablero
    int in1 = 0;
    int in2 = 0;
    for (int i = 0; i < matriz.size(); i++)
    {
        for (int j = 0; j < matriz[i].size(); j++)
        {
            if( matriz[i][j]==2){
                matriz[i][j] = 0;
            }
            casilla[i][j]= new Casilla(matriz[i][j],100,100,in2,in1,QPixmap(""));
            casilla[i][j]->setSeleccionada(false);
            scene->addItem(casilla[i][j]);
            in1= in1 +100;
        }
        in1 = 0;
        in2 = in2 +100;
    }

    //1
    vector<Casilla>::iterator it;
    for (it = fichasJ1.fichas.begin(); it != fichasJ1.fichas.end(); ++it){
        it->setSeleccionada(false);
        qDebug()  <<  " ddd1 " <<   it->getSeleccionada();
    }
    //2
    vector<Casilla>::iterator it2;
    for (it2 = fichasJ2.fichas.begin(); it2 != fichasJ2.fichas.end(); ++it2){
        it2->setSeleccionada(false);
        qDebug()  <<  " ddd2 " <<   it2->getSeleccionada();
    }
    //dibujar();
}

void MainWindow::comenzar_partida()
{
    if(inicio==false){
    // change the text
   // ui->btn_inicio->setText("Example");
    // resize button
    ui->btn_inicio->resize(100,100);
    ui->btn_inicio->setIcon(QIcon(QPixmap("")));
    ui->btn_inicio->setFont(QFont("Arial", 20));
    qDebug()  <<  " ddd ";
    inicio = true ;
    limpiar_tablero();
//    fichasJ1.pa = 3 ;
//    fichasJ1.turno = true;
    contador_reloj = 5;
    timer_turno->start(1000);

    timer->start(300);

    }
}


void MainWindow::Actualizacion()
{
    if (secuencia){
    cont++;


    double axt=0, ayt=0;
    if(cont<1000000){


       // qDebug()<< cont;
        for (int i=0 ; i < fichasJ1.sistema.length() ; i++){

        //    qDebug() << i << "------  "<< sistema[i]->x<< " " << sistema[i]->y;
            for (int j=0 ; j < fichasJ1.sistema.length() ; j++){
                if(i!=j){

                    fichasJ1.sistema[i]->aceleracion(fichasJ1.sistema[j]);
                    axt = axt + fichasJ1.sistema[i]->ax;
                    ayt = ayt + fichasJ1.sistema[i]->ay;

                }

            }





            fichasJ1.sistema[i]->aceleracion(axt, ayt);
            fichasJ1.sistema[i]->velocidades();
            fichasJ1.sistema[i]->posiciones();
            if(fichasJ1.sistema[i]->x<=-limite_ancho or fichasJ1.sistema[i]->x>=limite_ancho ){

                fichasJ1.sistema[i]->vx = fichasJ1.sistema[i]->vx * (-1) ;
                 fichasJ1.sistema[i]->vx = fichasJ1.sistema[i]->vx - (fichasJ1.sistema[i]->vx*0.2) ;

            }
            if(fichasJ1.sistema[i]->y<=-limite_alto or fichasJ1.sistema[i]->y>=limite_alto ){

                fichasJ1.sistema[i]->vy = fichasJ1.sistema[i]->vy * (-1) ; //cambio el sentido de la direccion
                fichasJ1.sistema[i]->vy = fichasJ1.sistema[i]->vy  - (fichasJ1.sistema[i]->vy*0.2) ; //disminuyo la velocidad para que no aumente infinitamente

            }
            if(fichasJ1.sistema[i]->x<=-limite_ancho  ){
                fichasJ1.sistema[i]->x += 20; //no permito que se quede al borde
            }
            if( fichasJ1.sistema[i]->x>=limite_ancho ){
                fichasJ1.sistema[i]->x -= 20;
            }

            if(fichasJ1.sistema[i]->y<=-limite_alto  ){
                fichasJ1.sistema[i]->y += 20;
            }
            if(fichasJ1.sistema[i]->y>=limite_alto ){
                fichasJ1.sistema[i]->y -= 20 ;
            }
            axt = 0;
            ayt = 0;
        }


    }else if(cont==1000000){
       // qDebug()<< cont;
        secuencia = false;

    }else{

    }
    }
}

void MainWindow::animacionJ1()
{
    limpiar();
    if (!secuencia)
    {

        //sistema 2 de 5 cuerpos
            c1 = new Cuerpo(0,0,25000,200,0,0);
            fichasJ1.sistema.append(c1);
//            sceneJ1->addItem(fichasJ1.sistema.last());
  //          scene->addItem(c1);

            c1 = new Cuerpo(-4000,0,70,200,0,-2);
            fichasJ1.sistema.append(c1);
            sceneJ1->addItem(fichasJ1.sistema.last());
            sceneJ1->addItem(c1);

            c1 = new Cuerpo(4000,0,70,200,0,2);
            fichasJ1.sistema.append(c1);
            sceneJ1->addItem(fichasJ1.sistema.last());
            sceneJ1->addItem(c1);

            c1 = new Cuerpo(0,-4000,70,200,2,0);
            fichasJ1.sistema.append(c1);
            sceneJ1->addItem(fichasJ1.sistema.last());
            sceneJ1->addItem(c1);

            c1 = new Cuerpo(0,4000,70,200,-2,0);
            fichasJ1.sistema.append(c1);
//            sceneJ1->addItem(fichasJ1.sistema.last());
//            sceneJ1->addItem(c1);

        secuencia = true;
    }
     timer_cuerpo->start(1);
}

void MainWindow::animacionJ2()
{

}

void MainWindow::limpiar()
{
    int i=0;
    cont = 0;

    timer_cuerpo->stop();

    for (i=0 ; i <fichasJ1. sistema.length() ; i++)
        sceneJ1->removeItem(fichasJ1.sistema[i]);

    fichasJ1.sistema.clear();

    secuencia = false;
}


void MainWindow::on_lanzamiento2_btn_clicked()
//Lanza el cuerpo 2 en mvto parabolico
{

    limpiar();
    if (!secuencia)
    {

        //sistema 2 de 5 cuerpos
            c1 = new Cuerpo(0,0,25000,200,0,0);
            fichasJ1.sistema.append(c1);
//            sceneJ1->addItem(fichasJ1.sistema.last());
  //          scene->addItem(c1);

            c1 = new Cuerpo(-4000,0,70,200,0,-2);
            fichasJ1.sistema.append(c1);
            sceneJ1->addItem(fichasJ1.sistema.last());
            sceneJ1->addItem(c1);

            c1 = new Cuerpo(4000,0,70,200,0,2);
            fichasJ1.sistema.append(c1);
            sceneJ1->addItem(fichasJ1.sistema.last());
            sceneJ1->addItem(c1);

            c1 = new Cuerpo(0,-4000,70,200,2,0);
            fichasJ1.sistema.append(c1);
            sceneJ1->addItem(fichasJ1.sistema.last());
            sceneJ1->addItem(c1);

            c1 = new Cuerpo(0,4000,70,200,-2,0);
            fichasJ1.sistema.append(c1);
//            sceneJ1->addItem(fichasJ1.sistema.last());
//            sceneJ1->addItem(c1);

        secuencia = true;
    }
     timer_cuerpo->start(1);
}


void MainWindow::on_finalizar_btn_clicked()
//para finalizar la simulacion
{

    valor1= rand()%(num+(num-1))-num;
    valor2= rand()%(num+(num-1))-num;
    qDebug()<<"valor1 "<< valor1;
    qDebug()<<"valor2 "<< valor2;

    timer_cuerpo->stop();


    c1 = new Cuerpo(valor1,valor2,70,200,-2,0);
    fichasJ1.sistema.append(c1);
    sceneJ1->addItem(fichasJ1.sistema.last());
    sceneJ1->addItem(c1);

    c1 = new Cuerpo(-valor1,-valor2,70,200,2,0);
    fichasJ1.sistema.append(c1);
//    sceneJ1->addItem(fichasJ1.sistema.last());
//    sceneJ1->addItem(c1);;

//    c1 = new cuerpo(valor1,0,70,70,-2,0);
//    sistema.append(c1);
////    scene->addItem(sistema.last());
////    scene->addItem(c1);

//    c1 = new cuerpo(-valor1,0,70,70,2,0);
//    sistema.append(c1);
////    scene->addItem(sistema.last());
////    scene->addItem(c1);

    timer_cuerpo->start(1);
}
