#include "mainwindow.hpp"
#include "loginwindow.hpp"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    //This sets the screen scale to whatever resolution the moniter is. If your screen size is too large for the login or main
    //window, I reccoment commenting this out. Its because my screen is 4K
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //Declare the application with the arguments
    QApplication a(argc, argv);

    //Declare a main window
    MainWindow w;


    //Pass the main window to the login screen class
    Login log(&w);

    //Show the login screen
    log.show();

    //Return after execution
    return a.exec();
}
