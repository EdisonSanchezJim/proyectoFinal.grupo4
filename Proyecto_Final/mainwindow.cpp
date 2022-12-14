#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QString>
#include <ostream>
#include <QDebug>
#include <string.h>
#include <sstream>
#include <QCheckBox>
#include <QtSql>
#include <QtDebug>



using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//Edison
QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

void MainWindow::on_DataBase_clicked()
{
    db.setDatabaseName("/home/alse/DOc/Documents/LABULT/Tablas.db");
    if ( !db.open())
    {
        qDebug() << db.lastError();
        qFatal ("Conexión fallida a la Base de Datos");
    }
    QSqlQuery query;
    query.prepare("CREATE TABLE tabla5 (ID INTEGER PRIMARY KEY NOT NULL, Descripcion VARCHAR(30) NOT NULL)");
    query.exec();
    QString query_to_insert = "INSERT INTO tabla5 VALUES ("+ ui->CARNE->toPlainText() + ", 'Motor1')";
    query.prepare(query_to_insert);
    if (!query.exec())
    {
        qDebug () << query.lastError();
    }
    db.close();
}




//BOTONES
void MainWindow::on_ACTUALIZAR_REF_TOL_clicked()
{
    ui->REF_VEL->setText("1800 rpm");
    ui->REF_FREC->setText("60 Hz");
    ui->REF_VOL->setText("220 V");
    ui->REF_TEMP->setText("60 °c");
    ui->TOL_VEL->setText("5%");
    ui->TOL_FREC->setText("5%");
    ui->TOL_VOL->setText("10%");
    ui->TOL_TEMP->setText("5%");
    ui->minV->setText("1710 rpm");
    ui->minF->setText("57 Hz");
    ui->minVo->setText("198 V");
    ui->minT->setText("57 °c");
    ui->maxV->setText("1890 rpm");
    ui->maxF->setText("63 Hz");
    ui->maxVo->setText("242 V");
    ui->maxT->setText("63 °c");



}
//Esteban
void MainWindow::on_ACTUALIZAR_MOTOR_clicked()
{
    QStringList list, lista1, lista2, lista3, lista4, lista5, lista6;
    QString VEL,FREC,VOL,T,t,velocidad, frecuencia, temperatura, voltaje, tiempo;
    int v,f,vo,temp,ti;
    //paletas para cambio  de color de base ca casilla
    QPalette vo_lim= ui->VOLTAJE_2->palette();
    QPalette f_lim= ui->FRECUENCIA_2->palette();
    QPalette v_lim= ui->VELOCIDAD_2->palette();
    QPalette T_lim= ui->TEMPERATURA_2->palette();
    QFile file("/home/alse/DOc/Documents/LABULT/CODE/DATOS.txt");

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening file: " << file.error();
        return;
    }

    QTextStream instream(&file);
    QString str = instream.readLine();

    ui->REGISTRO_VAL_T->setText(str);
    //----------------------------------------------------
    list = str.split(";");

    //
    VEL =list[0];
    FREC =list[1];
    VOL =list[2];
    T =list[3];
    t =list[4];

    //
    lista1=VEL.split(":");
    lista2=FREC.split(":");
    lista3=VOL.split(":");
    lista4=T.split(":");
    lista5=t.split(":");

    lista6 = lista5[1].split("}");

    velocidad = lista1[1];
    frecuencia = lista2[1];
    voltaje= lista3[1];
    temperatura = lista4[1];
    tiempo = lista6[0];

    qDebug()<< velocidad << frecuencia << voltaje << temperatura << tiempo;

    v=velocidad.toUInt();
    f=frecuencia.toUInt();
    vo=voltaje.toUInt();
    temp=temperatura.toUInt();
    ti=tiempo.toUInt();

    ui->VELOCIDAD_2->setText(velocidad);
    ui->FRECUENCIA_2->setText(frecuencia);
    ui->VOLTAJE_2->setText(voltaje);
    ui->TEMPERATURA_2->setText(temperatura);
    ui->T_OPERACION_2->setText(tiempo);


	//----------------------------------------------------
//definicion de colores de cuadro de texto de velocidad
if (v>1710 && v<1890)
{
    v_lim.setColor(QPalette::Base, Qt::green);
    ui->VELOCIDAD_2->setPalette(v_lim);
}
else
{
    v_lim.setColor(QPalette::Base, Qt::red);
    ui->VELOCIDAD_2->setPalette(v_lim);
}
//definicion de colores de cuadro de texto de frecuencia
if (f>57 && f<63)
{
    f_lim.setColor(QPalette::Base, Qt::green);
    ui->FRECUENCIA_2->setPalette(f_lim);
}
else
{
    f_lim.setColor(QPalette::Base, Qt::red);
    ui->FRECUENCIA_2->setPalette(f_lim);
}
//definicion de colores de cuadro de texto de voltaje
if (vo>198 && vo<242)
{
    vo_lim.setColor(QPalette::Base, Qt::green);
    ui->VOLTAJE_2->setPalette(vo_lim);
}
else
{
    vo_lim.setColor(QPalette::Base, Qt::red);
    ui->VOLTAJE_2->setPalette(vo_lim);
}
//definicion de colores de cuadro de texto de temperatura
if (temp>57 && temp<63)
{
    T_lim.setColor(QPalette::Base, Qt::green);
    ui->TEMPERATURA_2->setPalette(T_lim);
}
else
{
    T_lim.setColor(QPalette::Base, Qt::red);
    ui->TEMPERATURA_2->setPalette(T_lim);
}

file.close();

return ;

}
