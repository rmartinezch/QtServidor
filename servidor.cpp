#include "servidor.h"
#include "ui_servidor.h"

Servidor::Servidor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Servidor)
{
    ui->setupUi(this);
    serverSocket = new QTcpServer(this);
    initServer();
    connect(ui->pb_cerrar, &QAbstractButton::clicked,
            this, &QWidget::close);
    connect(serverSocket, &QTcpServer::newConnection,
            this, &Servidor::sendRandomMessage);

    // Mensajes aleatorios
    for (int i = 0; i < 50; ++i) {
        randomMessages << "Mensaje aleatorio " +
                              QString::number(i);
    }
}

Servidor::~Servidor()
{
    delete ui;
}

void Servidor::initServer()
{
    qDebug() << "initServer() !!!";
    if (!serverSocket->listen()) {
        qDebug() << "Error en el servidor: " +
                        serverSocket->errorString();
        return;
    }
    // obtener parámetros
    QString port =
        QString::number(serverSocket->serverPort());
    QString ipAddress;
    QList<QHostAddress> ipAddressList =
        QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressList.size(); ++i) {
        if (ipAddressList.at(i) != QHostAddress::LocalHost
            && ipAddressList.at(i).toIPv4Address()) {
            ipAddress = ipAddressList.at(i).toString();
            qDebug() << ipAddress;
            break;
        }
    }

    QString info = "IP: " + ipAddress + ", puerto: " + port;
    qDebug() << info;
    ui->lbl_servidor_info->setText(info);
}

void Servidor::sendRandomMessage()
{
    qDebug() << "sendRandomMessage() !!!";
    QByteArray qByteArray;
    QDataStream qDataStream(&qByteArray,
                            QIODevice::WriteOnly);
    QString randomMsg = randomMessages[
        QRandomGenerator::global()->bounded(
        randomMessages.size())];

    qDataStream << randomMsg;
    QTcpSocket *clientConnection =
        serverSocket->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);
    clientConnection->write(qByteArray);
    clientConnection->disconnectFromHost();
    ui->lbl_random_msg->setText(randomMsg);
}
