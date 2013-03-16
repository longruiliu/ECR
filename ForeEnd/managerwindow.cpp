#include "managerwindow.h"
#include "ui_managerwindow.h"

managerWindow::managerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managerWindow)
{
    ui->setupUi(this);
}

managerWindow::~managerWindow()
{
    delete ui;
}

void managerWindow::refreshData()
{

}
