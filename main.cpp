﻿#include "nehewidget.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    bool fs =false;
    QApplication a(argc, argv);
    switch(QMessageBox::information(0,
                                    "Start FullScreen?",
                                    "Would You Like To Run In Fullscreen Mode?",
                                    QMessageBox::Yes,
                                    QMessageBox::No | QMessageBox::Default ) )
    {
    case QMessageBox::Yes:
        fs = true;
        break;
    case QMessageBox::No:
        fs = false;
        break;
    }

    NeHeWidget w(0, 0, fs);
    w.show();

    return a.exec();
}
