#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <QDialog>

namespace Ui {
class MenuScreen;
}

class MenuScreen : public QDialog
{
    Q_OBJECT

public:
    explicit MenuScreen(QString& name, QWidget *parent = nullptr);
    ~MenuScreen();

private:
    Ui::MenuScreen *ui;
};

#endif // MENUSCREEN_H
