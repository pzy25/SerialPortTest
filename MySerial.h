// MySerial.h

#ifndef MYSERIAL_H
#define MYSERIAL_H

#include <QSerialPort>
#include <QObject>

class MySerial : public QSerialPort
{
    Q_OBJECT

public:
    explicit MySerial(QObject *parent = nullptr);
    ~MySerial();


signals:


private slots:


private:

};

#endif // MYSERIAL_H
