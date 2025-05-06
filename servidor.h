#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
// para obtener las IP
#include <QNetworkInterface>
// para funcionalidad de aleatoriedad
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui {
class Servidor;
}
QT_END_NAMESPACE

class Servidor : public QWidget
{
    Q_OBJECT

public:
    Servidor(QWidget *parent = nullptr);
    ~Servidor();

private:
    Ui::Servidor *ui;
    QTcpServer *serverSocket = nullptr;
    QVector<QString> randomMessages;

    void initServer();

private slots:
    void sendRandomMessage();
};
#endif // SERVIDOR_H
