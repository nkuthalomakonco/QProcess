#include "dialog.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setStyle("fusion");
    //open qss file
    QFile file("C:/Users/nkuthalo.makonco/Desktop/ping application with QProcess/styles/VisualScript/VisualScript.qss");
    file.open(QFile::ReadOnly);

    QString styleSheet { QLatin1String(file.readAll()) };

    //setup stylesheet
    a.setStyleSheet(styleSheet);
    Dialog w;
    w.show();
    return a.exec();
}
//https://qss-stock.devsecstudio.com/documentation.php
