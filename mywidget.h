#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "MySerial.h"
#include <QMessageBox>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui {
class myWidget;
}
QT_END_NAMESPACE

class myWidget : public QWidget
{
    Q_OBJECT

public:
    myWidget(QWidget *parent = nullptr);
    ~myWidget();
    void setSerialValue();
    void initSerialPort();


private slots:
    void btnRefresh_slot();
    void open1closeSerialPort_slot();
    void on_btnSend_slot();

private:
    Ui::myWidget *ui;
    MySerial myserial;

};
#endif // MYWIDGET_H
