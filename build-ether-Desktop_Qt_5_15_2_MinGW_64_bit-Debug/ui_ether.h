/********************************************************************************
** Form generated from reading UI file 'ether.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ETHER_H
#define UI_ETHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_J1;
    QGraphicsView *graphicsView_J2;
    QLabel *pa_jugador1;
    QLabel *Reloj;
    QLabel *jugador1;
    QLabel *jugador2;
    QPushButton *btn_inicio;
    QLabel *pa_jugador2;
    QPushButton *finalizar_btn;
    QPushButton *lanzamiento2_btn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1800, 859);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(390, 1, 1011, 751));
        graphicsView_J1 = new QGraphicsView(centralwidget);
        graphicsView_J1->setObjectName(QString::fromUtf8("graphicsView_J1"));
        graphicsView_J1->setGeometry(QRect(0, 1, 400, 751));
        graphicsView_J2 = new QGraphicsView(centralwidget);
        graphicsView_J2->setObjectName(QString::fromUtf8("graphicsView_J2"));
        graphicsView_J2->setGeometry(QRect(1400, 0, 400, 751));
        pa_jugador1 = new QLabel(centralwidget);
        pa_jugador1->setObjectName(QString::fromUtf8("pa_jugador1"));
        pa_jugador1->setGeometry(QRect(100, 600, 131, 111));
        QFont font;
        font.setPointSize(19);
        pa_jugador1->setFont(font);
        Reloj = new QLabel(centralwidget);
        Reloj->setObjectName(QString::fromUtf8("Reloj"));
        Reloj->setGeometry(QRect(650, 740, 71, 71));
        QFont font1;
        font1.setPointSize(28);
        Reloj->setFont(font1);
        Reloj->setAutoFillBackground(false);
        Reloj->setScaledContents(false);
        jugador1 = new QLabel(centralwidget);
        jugador1->setObjectName(QString::fromUtf8("jugador1"));
        jugador1->setGeometry(QRect(10, 10, 381, 731));
        jugador1->setAlignment(Qt::AlignCenter);
        jugador2 = new QLabel(centralwidget);
        jugador2->setObjectName(QString::fromUtf8("jugador2"));
        jugador2->setGeometry(QRect(1410, 0, 381, 741));
        jugador2->setAlignment(Qt::AlignCenter);
        btn_inicio = new QPushButton(centralwidget);
        btn_inicio->setObjectName(QString::fromUtf8("btn_inicio"));
        btn_inicio->setGeometry(QRect(450, 690, 100, 100));
        QFont font2;
        font2.setPointSize(20);
        btn_inicio->setFont(font2);
        btn_inicio->setText(QString::fromUtf8("Inicio"));
        btn_inicio->setIconSize(QSize(100, 100));
        pa_jugador2 = new QLabel(centralwidget);
        pa_jugador2->setObjectName(QString::fromUtf8("pa_jugador2"));
        pa_jugador2->setGeometry(QRect(1540, 600, 131, 111));
        pa_jugador2->setFont(font);
        finalizar_btn = new QPushButton(centralwidget);
        finalizar_btn->setObjectName(QString::fromUtf8("finalizar_btn"));
        finalizar_btn->setGeometry(QRect(40, 760, 83, 29));
        lanzamiento2_btn = new QPushButton(centralwidget);
        lanzamiento2_btn->setObjectName(QString::fromUtf8("lanzamiento2_btn"));
        lanzamiento2_btn->setGeometry(QRect(150, 760, 83, 29));
        MainWindow->setCentralWidget(centralwidget);
        graphicsView->raise();
        graphicsView_J1->raise();
        graphicsView_J2->raise();
        pa_jugador1->raise();
        jugador2->raise();
        Reloj->raise();
        btn_inicio->raise();
        pa_jugador2->raise();
        finalizar_btn->raise();
        lanzamiento2_btn->raise();
        jugador1->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pa_jugador1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        Reloj->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" color:#000000;\">0</span></p></body></html>", nullptr));
        jugador1->setText(QString());
        jugador2->setText(QString());
        pa_jugador2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        finalizar_btn->setText(QCoreApplication::translate("MainWindow", "finalizar_btn", nullptr));
        lanzamiento2_btn->setText(QCoreApplication::translate("MainWindow", "lanzamiento2_btn", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ETHER_H
