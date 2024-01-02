#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setText("OS : " + m_ping.operatingSystem());

    connect(ui->pbStart,&QPushButton::clicked,&m_ping,&Ping::start);
    connect(ui->pbStop,&QPushButton::clicked,&m_ping,&Ping::stop);
    connect(&m_ping,&Ping::output,this,&Dialog::output);

    m_ping.setAddress(ui->lineEdit->text());
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::output(QString data)
{
    ui->plainTextEdit->appendPlainText(data);
}


void Dialog::on_lineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    m_ping.setAddress(ui->lineEdit->text());
}

