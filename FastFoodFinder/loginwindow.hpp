#pragma once
#include "accountType.hpp"
#include <QDialog>
#include <QWidget>

/*******************************************
 * class Login will be within namespace Ui.
 * It will handle all of the login information
 * as well as determine if the person logging
 * in is a user or an admin
 * ******************************************/

namespace Ui{
    class Login;
}

class Login : public QDialog
{
    Q_OBJECT

    public:
        //Constructor
        explicit Login(QWidget*);

        //Destructor
        ~Login();

        //Public function to return type of user
        static fastFoodFinder::AccountType getType();

    private slots:
        //Checks if the push button has been clicked or not
        void on_pushButton_registered_clicked();
        //Checks if the check box for showing the password has been clicked
        void on_checkBox_showPW_stateChanged(int arg1);

private:
        //Method authenticate is used when the program checks if an admin username or password as been entered
        bool authenticate(QString username, QString password) const;

        //Method authSuccessful will output that the login was accepted and transition to the main window
        void authSuccessful(fastFoodFinder::AccountType) const;

        //Outputs that the authentication has failed and waits for new input
        void authFailed() const;

        static fastFoodFinder::AccountType type;    //The type of user(admin or foodie)
        Ui::Login* ui;                              //Pointer to namespace Ui for Login info
        QWidget* windowAfterLogin;               //Pointer so that MainWindow appears after successful login
};
