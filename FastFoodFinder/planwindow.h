#ifndef PLANWINDOW_H
#define PLANWINDOW_H

#include <QWidget>

namespace Ui {
class PlanWindow;
}

class PlanWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlanWindow(QWidget *parent = nullptr);
    ~PlanWindow();

private:
    Ui::PlanWindow *ui;
};

#endif // PLANWINDOW_H
