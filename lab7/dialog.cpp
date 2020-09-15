#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>


Dialog::Dialog(Language * t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    change = t;
}

Dialog::~Dialog()
{

    delete ui;
}

void Dialog::on_buttonBox_accepted() {
    change -> name = ui -> lineEdit -> text().toStdString();
    qDebug() << change -> name.c_str();
    change -> type = ui -> lineEdit_2 -> text().toStdString();
    qDebug() << change -> type.c_str();
    change -> author = ui -> lineEdit_3 -> text().toStdString();
    qDebug() << change -> author.c_str();
}
