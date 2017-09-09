#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>  //Librería para el uso de cadenas de texto
#include <cmath>    //Librería para el uso de funciones matemáticas

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Conexiones
    connect(ui->Proceder,SIGNAL(clicked()),this,SLOT(metodo()));
    connect(ui->Borrar,SIGNAL(clicked()),this,SLOT(borrar()));
    connect(ui->Salir,SIGNAL(clicked()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::funcion(double c){
    return (667.38/c)*(1-exp(-0.146843*c))-40; //devuelve la función de arrastre
}

void MainWindow::metodo(){
    QString temp,temp2,temp3;          //Cadenas de texto de uso temporal
    double dato1=ui->Dato1->value();   //Recupera el valor de X1 del spinbox
    double dato2=ui->Dato2->value();   //Recupera el valor de X2 del spinbox
    double err=ui->Err->value(); //Recupera el valor del error del spinbox
    double xr=0.0;
    double ea=100.0;
    while(ea>err){
        xr=(dato1+dato2)/2; //Se calcula la bisección
        ea=100*std::abs(xr-dato2)/xr; //Se calcula el error
        if(funcion(dato1)*funcion(xr)<0)  //Se evaluan la función en X1 y Xr
            dato2=xr;
        if(funcion(dato1)*funcion(xr)>0)  //Se evaluan la función en X1 y Xr
            dato1=xr;
    }
    temp.append("Raiz=").append(temp2.setNum(xr)).append("\nError=").append(temp3.setNum(ea));  //Se prepara el texto para ser presentado
    ui->Texto->setText(temp);  //Se presenta el texto
}

void MainWindow::borrar(){
    ui->Dato1->setValue(0.0);  //Se borran los spinbox
    ui->Dato2->setValue(0.0);
    ui->Err->setValue(0.0);
    ui->Texto->clear();     //Se borra el texto
}
