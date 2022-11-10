#include "casilla.h"

Casilla::Casilla(int _estado,float _alto,float _ancho, float _x, float _y, QPixmap pixmap)
{
    estado = _estado;
    altura = _alto;
    ancho = _ancho;
    //setPos(_x,_y);
    x = _x;
    y = _y;
    agregar = false;
    m_playerPixmap = pixmap;
    seleccionada = false;

    if(estado==3 or estado==6){
        costo_paso = 1;
    }else if(estado==4 or estado==7){
        costo_paso = 2;
    }else if(estado==5 or estado==8){
        costo_paso = 3;
    }else{
        costo_paso = 0;
    }
}

Casilla::Casilla(const Casilla &otro)
{
    estado = otro.estado;
    altura = otro.altura;
    ancho = otro.ancho;
    //setPos(_x,_y);
    x = otro.x;
    y = otro.y;
    agregar = false;
    m_playerPixmap = otro.m_playerPixmap;
    seleccionada = false;

    if(estado==3 or estado==6){
        costo_paso = 1;
    }else if(estado==4 or estado==7){
        costo_paso = 2;
    }else if(estado==5 or estado==8){
        costo_paso = 3;
    }else{
        costo_paso = 0;
    }
}


QRectF Casilla::boundingRect() const{

   // return QRectF(-x/2, -y/2, ancho, altura);
    return QRectF(x,y,altura,ancho);
}


void Casilla::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
       QWidget *widget){
    QPen pen(Qt::blue,4);
if(estado==1){ //cuadrados negros
    painter->setBrush(Qt::black);

    painter->drawRect(boundingRect());
}else if(estado==2){//border azules o color

    painter->setPen(QPen(Qt::TransparentMode));
    //painter->setPen(pen);
//    painter->drawRect(boundingRect());

    painter->setBrush(QColor(qRgb(0,255,255)));
    painter->drawRect(boundingRect());

}else if(estado==3){//cuadrados amarillo

     // painter->setBrush(Qt::white);
     // painter->drawEllipse(boundingRect().x()+10,boundingRect().y()+10,boundingRect().width()-20,boundingRect().height()-20);

    painter->setBrush(QColor(245, 239, 70, 127 ));
    painter->drawRect(boundingRect());
        painter->drawPixmap(x, y, QPixmap(":/fantasma.png"), 1,1, ancho, altura);
}else if(estado==4){//cuadrados amarillo

     // painter->setBrush(Qt::white);
     // painter->drawEllipse(boundingRect().x()+10,boundingRect().y()+10,boundingRect().width()-20,boundingRect().height()-20);

    painter->setBrush(QColor(245, 239, 70, 127 ));
    painter->drawRect(boundingRect());
        painter->drawPixmap(x, y, QPixmap(":/humano.png"), 1,1, ancho, altura);
}else if(estado==5){//border azules

//    painter->drawRect(boundingRect());
//    painter->setBrush(Qt::white);
//    painter->drawEllipse(boundingRect().x()+15,boundingRect().y()+15,boundingRect().width()-30,boundingRect().height()-30);

//    painter->setBrush(QColor(199, 65, 214, 127 ));
    painter->setBrush(QColor(245, 239, 70, 127 ));
    painter->drawRect(boundingRect());
        painter->drawPixmap(x, y, QPixmap(":/asura.png"), 1,1, ancho, altura);

}else if(estado==6){//border azules
    painter->setBrush(QColor(199, 65, 214, 127 ));
    painter->drawRect(boundingRect());
    painter->drawPixmap(x, y, QPixmap(":/fantasma.png"), 1,1, ancho, altura);

}else if(estado==7){//border azules

    painter->setBrush(QColor(199, 65, 214, 127 ));
    painter->drawRect(boundingRect());
    painter->drawPixmap(x, y, QPixmap(":/humano.png"), 1,1, ancho, altura);

}else if(estado==8){//border azules

    painter->setBrush(QColor(199, 65, 214, 127 ));
    painter->drawRect(boundingRect());
    painter->drawPixmap(x, y, QPixmap(":/asura.png"), 1,1, ancho, altura);


}else{
    //painter->setBrush(Qt::white);
    painter->setBrush(Qt::transparent);
    painter->drawRect(boundingRect());
}
}

int Casilla::getEstado() const
{
    return estado;
}

void Casilla::setEstado(int newEstado)
{
    estado = newEstado;
}

void Casilla::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<" casilla " << estado<<" posx " << x<<" posy " << y;

    if(seleccionada==false){
        seleccionada = true;
    }else if(seleccionada){
        seleccionada = false;
    }

    qDebug()<<seleccionada;
}

float Casilla::getX() const
{
    return x;
}

void Casilla::setX(float newX)
{
    x = newX;
}

float Casilla::getY() const
{
    return y;
}

void Casilla::setY(float newY)
{
    y = newY;
}

bool Casilla::getSeleccionada() const
{
    return seleccionada;
}

void Casilla::setSeleccionada(bool newSeleccionada)
{
    seleccionada = newSeleccionada;
}

int Casilla::getCosto_paso() const
{
    return costo_paso;
}

void Casilla::setCosto_paso(int newCosto_paso)
{
    costo_paso = newCosto_paso;
}

