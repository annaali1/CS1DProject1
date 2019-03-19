#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <iostream>
#include "loginwindow.hpp"
#include "ui_loginwindow.h"

//Initialize type to foodie at start of implementation, otherwise its an unreferenced type
fastFoodFinder::AccountType Login::type = fastFoodFinder::AccountType::ADMIN;

//Constructor will initialize the main window and login screen with appropriate spacing and images
Login::Login(QWidget* window)
    : QDialog(nullptr), ui(new Ui::Login), windowAfterLogin(window)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);

    QPixmap pix(":/Resources/hamburgercopy.jpg");
    ui->label_logo->setPixmap(pix.scaled(150, 150, Qt::KeepAspectRatio));
}

//Destructor
Login::~Login()
{
    delete ui;
}

//If the push button has been clicked, this method checks username and password
//and branches to methods authSuccessful or authFailed respectively
void Login::on_pushButton_registered_clicked()
{
    QString usernameInput = ui->lineEdit_username->text();
    QString passwordInput = ui->lineEdit_password->text();

    if(authenticate(usernameInput, passwordInput))
    {
        authSuccessful(Login::getType());
    }
    else
    {
        authFailed();
    }
}

//Method authenticate will check the username and password and the type
bool Login::authenticate(QString usernameInput, QString passwordInput) const
{
    //Sets the file to be read to our login info
    QFile authFile(":/loginInfo.txt");

    //Initialize a QTextStream with our QFile
    QTextStream qin(&authFile);

    //Open our QFile with read only permissions
    authFile.open(QIODevice::ReadOnly);

    //Initialize QStrings for username, password, and account type
    QString usernameFile;
    QString passwordFile;
    QString accTypeFile;
    bool authValid = false;

    /* Search for correct username and password */
    while(!authValid && !qin.atEnd())
    {
        //Reads in info from the file into QString variables
        usernameFile = qin.readLine();
        passwordFile = qin.readLine();
        accTypeFile  = qin.readLine();
        qin.readLine(); //clears the empty line

        //If any variables are empty, an exception will be thrown, we can add an exception class later
        if(usernameFile.isEmpty() || passwordFile.isEmpty() || accTypeFile.isEmpty())
        {
            throw;
        }
        else if(usernameFile == usernameInput && passwordFile == passwordInput)
        {
            //If username and password input by the user is the same as the file
            //then it is a valid username
            authValid = true;

            //If the accType in the file is an admin, account type will be changed accordingly
            if(accTypeFile == "admin")
            {
                type = fastFoodFinder::AccountType::ADMIN;
            }
            else
            {
                type = fastFoodFinder::AccountType::FOODIE;
            }
        }
    }

    //Closes the file
    authFile.close();

    //Returns the boolean
    return authValid;
}

//Method authSuccessful will load different images and output depending on user or admin status
void Login::authSuccessful(fastFoodFinder::AccountType type) const
{
    QPixmap pix;

    //If the type is an admin, a different image will be loaded in
    if(type == fastFoodFinder::AccountType::ADMIN)
    {
        pix.load(":/admin.png");
    }

    //Set the image logo to the aspect ratio
    ui->label_logo->setPixmap(pix.scaled(pix.width(), pix.height(), Qt::KeepAspectRatio));

    //Set the error message with the appropriate color
    ui->label_errorMsg->setStyleSheet(" QLabel { background-color: green; color: white; } ");

    //Set the error message with appropriate text
    ui->label_errorMsg->setText("Login successful");

    //Show the successful or error screen with correct QTimers
    QTimer::singleShot(500, windowAfterLogin, SLOT(show()));
    QTimer::singleShot(500, this, SLOT(close()));
}

//Method authFailed() will output to the login screen a password incorrect image
void Login::authFailed() const
{
    ui->label_errorMsg->setStyleSheet(" QLabel { background-color: red; color: white; }");
    ui->label_errorMsg->setText("Username/Password was incorrect");
}

//This method handles if the check box for show password has been clicked or not
void Login::on_checkBox_showPW_stateChanged(int)
{
    if(ui->checkBox_showPW->checkState() == Qt::CheckState::Checked)
    {
        ui->lineEdit_password->setEchoMode(QLineEdit::EchoMode::Normal);
    }
    else
    {
        ui->lineEdit_password->setEchoMode(QLineEdit::EchoMode::Password);
    }
}

//Returns the type of the accountType
fastFoodFinder::AccountType Login::getType()
{
    return type;
}

