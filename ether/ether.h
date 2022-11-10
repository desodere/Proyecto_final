#ifndef ETHER_H
#define ETHER_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <vector>
#include "qgraphicsscene.h"
#include <QTimer>
#include <QDebug>
//#include "casilla.h"
#include "jugador.h"


using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    float x, y, ancho, alto;
    QTimer *timer;
    QTimer *timer_turno;

  //***************
    // temporizador para la animacion de los cuerpos
    QGraphicsScene *sceneJ1;
    QGraphicsScene *sceneJ2;
    QTimer *timer_cuerpo;

    Cuerpo *c1;
    int valor1 ;
    int valor2 ;
    int num = 4000;
    int limite_ancho, limite_alto;
    int cont ;

    //booleano para controlar la simulación
    bool secuencia;
    void limpiar();
    void Actualizacion();
 //***************
    void animacionJ1();
    void animacionJ2();
     //***************
    vector<vector<int>> matriz
    {
        {1,1,1,1,1,1,1},
        {1,0,3,4,5,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,8,7,6,0,1},
        {1,1,1,1,1,1,1},
    };
    void dibujar();


    bool detectar();
    void posible_desplazamiento(int fPasos);
    void iniciarReloj();
    int contador_reloj;
    int numero_turnos;
    bool inicio;
    void limpiar_tablero();

public slots:
    void comenzar_partida();



private slots:
//    void on_lanzamiento1_btn_clicked();

    void on_lanzamiento2_btn_clicked();

    void on_finalizar_btn_clicked();

//    void on_pushButton_btn_clicked();
    ///
    ///
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Casilla *casilla[12][7];


    Jugador fichasJ1 = (1);
    Jugador fichasJ2 = (2);

    int desplazamiento;
    int fx, fy, fx2, fy2;
    bool derecha, izquierda, arriba, abajo;
    int fPasos;
};
#endif // ETHER_H
