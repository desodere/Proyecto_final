#include "cuerpo.h"

Cuerpo::Cuerpo(double _x, double _y, double _masa, double _radio, double _vx, double _vy)
{
    x = _x;
    y = _y;
    radio = _radio/10;
    masa = _masa;
    vx = _vx;
    vy = _vy;
    setPos(x/MOD,-y/MOD);
    ax = 0;
    ay = 0;
}

Cuerpo::Cuerpo(const Cuerpo &obj) {
    x = obj.x;
    y = obj.y;
    radio = obj.radio;
    masa = obj.masa;
    vx = obj.vx;
    vy = obj.vy;
}

Cuerpo::~Cuerpo()
{
    delete this;
}

QRectF Cuerpo::boundingRect() const
{
    return QRect(-radio, -radio, radio*2, radio*2);
}

void Cuerpo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkGreen);
    painter->drawEllipse(boundingRect());
}

void Cuerpo::aceleracion(double t1, double t2)
{
    ax = t1;
    ay = t2;
}

void Cuerpo::aceleracion(Cuerpo *cuerpo)
{   /*double q1 = pow(cuerpo->x-x,2);
    double q2 = pow(cuerpo->y-y,2);*/
//    qDebug() << " q1 " << q1<< " q2 " << q2;
    double teta  = 0;
    double r = sqrt( (pow(cuerpo->x-x,2)) + (pow(cuerpo->y-y,2)) );
 //   qDebug() << " r " << r;

//    if ((cuerpo->y-y)/(cuerpo->x-x)!=INFINITY){
//        teta  = atanf((cuerpo->y-y)/(cuerpo->x-x));
//    }else{
//        teta = 0;
//    }
  //  teta = atan2l((cuerpo->y-y),(cuerpo->x-x));
   // teta = atanl((cuerpo->y-y)/(cuerpo->x-x));
   // teta  = atanf((cuerpo->y-y)/(cuerpo->x-x));
    teta  = atan2((cuerpo->y-y),(cuerpo->x-x));
    //teta  = atan((cuerpo->y-y)/(cuerpo->x-x));
//    qDebug() << " teta " << teta;

    ax =  ((cuerpo->masa*GRAV)/ pow(r,2)) * cos(teta);
    ay =  ((cuerpo->masa*GRAV)/ pow(r,2)) * sin(teta);

//    ax =   cos(teta);
//    ay =  sin(teta);


}



void Cuerpo::velocidades()
{
//    vx = vx + (ax*DT); //velocidad = a velocidad inicial + la aceleracion  por diferecial de tiempo
//    vy = vy + (ay*DT);

    vx = vx + (ax * DT);
    vy = vy + (ay * DT);

}

void Cuerpo::posiciones()
{
    x = x + (vx * DT) + (0.5 * ax * pow(DT,2));
    y = y + (vy * DT) + (0.5 * ay * pow(DT,2));

//    x = x + ((vx/1) * 1);
//    y = y + ((vy/1) * 1);

    setPos(x/MOD,-y/MOD);
}
