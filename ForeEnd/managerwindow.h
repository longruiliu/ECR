#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QDialog>

namespace Ui {
    class managerWindow;
}

class managerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit managerWindow(QWidget *parent = 0);
    ~managerWindow();

private:
    Ui::managerWindow *ui;
};

#endif // MANAGERWINDOW_H
