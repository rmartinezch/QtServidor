#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QWidget>

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
};
#endif // SERVIDOR_H
