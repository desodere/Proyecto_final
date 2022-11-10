#ifndef CASILLA_H
#define CASILLA_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

using namespace std;

class Casilla:public QGraphicsItem
{

public:
    Casilla(int _estado,float _alto,float _ancho, float _x, float _y,QPixmap pixmap);
    Casilla(const Casilla &otro);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    int getEstado() const;
    void setEstado(int newEstado);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool agregar;
    QPixmap m_playerPixmap ;
    float getX() const;
    void setX(float newX);

    float getY() const;
    void setY(float newY);

    bool getSeleccionada() const;
    void setSeleccionada(bool newSeleccionada);

    int getCosto_paso() const;
    void setCosto_paso(int newCosto_paso);

private:
    int estado;
    float altura;
    float ancho;
    float x;
    float y;
    bool seleccionada;
    int costo_paso;

};

#endif // CASILLA_H
