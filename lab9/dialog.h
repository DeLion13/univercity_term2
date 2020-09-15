#ifndef DIALOG_H
#define DIALOG_H
#include "mainwindow.h"

#include <QDialog>
#include <QListWidget>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(Language * t, int user_id, QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    Language * change;
    int user;
};

#endif // DIALOG_H
