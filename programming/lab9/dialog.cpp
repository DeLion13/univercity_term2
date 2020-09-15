#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>


Dialog::Dialog(Language * t, int user_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this -> user = user_id;

    change = t;
}

Dialog::~Dialog()
{

    delete ui;
}

void Dialog::on_buttonBox_accepted() {
    change -> name = ui -> lineEdit -> text().toStdString();
    change -> type = ui -> lineEdit_2 -> text().toStdString();
    change -> author = ui -> lineEdit_3 -> text().toStdString();
    change -> user_id = this -> user;
}
