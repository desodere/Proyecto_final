#ifndef CUERPO_H
#define CUERPO_H

#define GRAV 1 //gravedad
#define DT 1 //diferencial de tiempo
#define MOD 30

#include <QGraphicsItem>
#include <QPainter>
#include <cmath>
#include <math.h>
#include <qdebug.h>

class Cuerpo: public QGraphicsItem
{
public:
    Cuerpo(double x, double y, double masa, double radio, double vx, double vy);
    Cuerpo( const Cuerpo &obj);
    ~Cuerpo();
    float x, y, vx, vy, ax, ay, radio, masa;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // Funciones mvto
    void aceleracion(double t1, double t2);
    void aceleracion(Cuerpo *cuerpo);
    void velocidades();
    void posiciones();

};

#endif // CUERPO_H
