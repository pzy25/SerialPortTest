#include "mywidget.h"
#include "./ui_mywidget.h"

myWidget::myWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::myWidget)
{
    ui->setupUi(this);
    connect(ui->btn_refreshSerial,&QPushButton::clicked,this,&myWidget::btnRefresh_slot);
    connect(ui->btn_openSerial, &QPushButton::clicked, this, &myWidget::open1closeSerialPort_slot);
    connect(ui->btnSend, &QPushButton::clicked, this, &myWidget::on_btnSend_slot);
    initSerialPort();

}

myWidget::~myWidget()
{
    delete ui;
}

void myWidget::setSerialValue()
{
    QStringList baudRates = {"9600", "19200", "38400", "57600", "115200"};
    ui->baudRate->addItems(baudRates);

    QStringList dataBits = {"8", "7", "6", "5"};
    ui->dataBits->addItems(dataBits);

    QStringList stopBits = {"1", "2"};
    ui->stopBits->addItems(stopBits);

    QStringList parity = {"NoParity", "None", "EvenParity","OddParity"};
    ui->parity->addItems(parity);

}

void myWidget::initSerialPort()
{
    setSerialValue();
    ui->btnSend->setEnabled(false);

}

void myWidget::open1closeSerialPort_slot()
{
    if (myserial.isOpen()) {
        // 如果串口已打开，关闭它
        myserial.close();
        // 更新按钮文本显示为“打开串口”
        ui->btn_openSerial->setText(tr("打开串口"));
        QMessageBox::information(this, tr("Serial Port Closed"), tr("Serial port has been closed."));
        ui->btnSend->setEnabled(false);
    } else {
        myserial.setPortName(ui->portName->currentText().split(" - ").first());
        myserial.setBaudRate(static_cast<QSerialPort::BaudRate>(ui->baudRate->currentText().toInt()));
        myserial.setDataBits(static_cast<QSerialPort::DataBits>(ui->dataBits->currentText().toInt()));
        myserial.setParity(static_cast<QSerialPort::Parity>(ui->parity->currentIndex()));
        myserial.setStopBits(static_cast<QSerialPort::StopBits>(ui->stopBits->currentIndex() + 1));
        myserial.setFlowControl(QSerialPort::NoFlowControl);
        qDebug() << "Attempting to open serial port:" << ui->portName->currentText().split(" - ").first();
        qDebug() << "Baud Rate:" << ui->baudRate->currentText();
        qDebug() << "Data Bits:" << ui->dataBits->currentText();
        qDebug() << "Parity:" << ui->parity->currentIndex();
        qDebug() << "Stop Bits:" << ui->stopBits->currentIndex() + 1;
        if (myserial.open(QIODevice::ReadWrite)) {
            QMessageBox::information(this, tr("Connection Successful"),
                                     tr("Serial port opened successfully."));
            ui->btn_openSerial->setText(tr("关闭串口"));
            ui->btnSend->setEnabled(true);
        } else {
            QMessageBox::critical(this, tr("Error"), myserial.errorString());
            ui->btnSend->setEnabled(false);
        }
    }
}

void myWidget::on_btnSend_slot()
{
    QString dataToSend = ui->lineEdit->text();  // 假设lineEdit是用户输入数据的地方

    QByteArray hexData = QByteArray::fromHex(dataToSend.toLocal8Bit());
    myserial.write(hexData);
    qDebug() << "Sending in HEX mode:" << hexData;

    if (myserial.waitForBytesWritten(1000)) {
        QMessageBox::information(this, tr("发送成功"), tr("数据已成功发送。"));
    } else {
        QMessageBox::critical(this, tr("错误"), tr("发送数据失败。"));
    }
}

void myWidget::btnRefresh_slot()
{
    ui->portName->clear(); // 清除下拉框中现有的所有项

    // 获取系统中所有可用的串行端口
    const QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : availablePorts) {
        // 向下拉框中添加串行端口的名称
        ui->portName->addItem(info.portName() + " - " + info.description(), info.portName());
    }
}
