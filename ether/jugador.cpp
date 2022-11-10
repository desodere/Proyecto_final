#include "jugador.h"



Jugador::Jugador(int _bando)
{
    pa = 0;
    bando = _bando;
    turno = false;
    puntos_conquista = 0;
}

bool Jugador::agregar(Casilla ficha)
{
    bool val = true;
    vector<Casilla>::iterator it;
    for (it = fichas.begin(); it != fichas.end(); ++it){
        if(ficha.getX() == it->getX() and ficha.getY() == it->getY()){
            val = false;
            break;
        }
        //qDebug() << it->getEstado() ;
    }
    if(val){
        fichas.push_back(ficha);
    }else{
        qDebug() <<"no se pude agregar";
    }
}

bool Jugador::remover(Casilla ficha)
{

}

void Jugador::imprimir()
{
    vector<Casilla>::iterator it;
    for (it = fichas.begin(); it != fichas.end(); ++it)
        qDebug() << it->getEstado() ;

}
