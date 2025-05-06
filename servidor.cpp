#include "servidor.h"
#include "ui_servidor.h"

Servidor::Servidor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Servidor)
{
    ui->setupUi(this);
}

Servidor::~Servidor()
{
    delete ui;
}
