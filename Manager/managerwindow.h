#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QDialog>
#include <QMap>

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
    void restoreFromDB();
    void saveToDB();

public slots:
    void selectUserItem();
    void selectGroupItem();
    void selectMemberItem();
signals:
        void clearLists();
private slots:
    void on_modifyUser_clicked();
};

#endif // MANAGERWINDOW_H
