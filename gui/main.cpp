#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QStyle>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Load style sheet from Qt resources
    QFile styleFile(":/style.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream styleStream(&styleFile);
        app.setStyleSheet(styleStream.readAll());
        styleFile.close();
    }

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
