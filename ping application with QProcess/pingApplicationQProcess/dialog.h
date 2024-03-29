#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "ping.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    void output(QString data);
private slots:
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Dialog *ui;
    Ping m_ping;

};
#endif // DIALOG_H
