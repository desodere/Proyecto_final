#ifndef JUGADOR_H
#define JUGADOR_H

#include "casilla.h"
#include "cuerpo.h"

class Jugador
{


public:
    Jugador(int _bando);
//    ~Jugador();
    int bando;
    int pa;
    bool turno;
    bool agregar(Casilla ficha);
    bool remover(Casilla ficha);
    vector<Casilla> fichas;

    void imprimir();

//    // temporizador para el pulso
//    QTimer *timer_cuerpo;

    Cuerpo *c1;
    //lista de objetos
    QList <Cuerpo*> sistema;


private:
    int puntos_conquista;
};

#endif // JUGADOR_H
