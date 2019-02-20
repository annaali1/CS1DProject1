#pragma once
#include "accountType.hpp"
#include<QMainWindow>

/*****************************************************
 * Class MainWindow will be within the Ui namespace
 * and will handle outputting the user interface as
 * well as managing the file variable
 * ***************************************************/
namespace Ui{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        QString currentFile; // Directory of the file containing restaurants currently loaded into the program

        // Setup the menus and widgets in the window
        void setupMenusAndWidgets();

};
