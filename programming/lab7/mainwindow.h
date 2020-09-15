#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "xml_storage.h"
#include "storage.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = 0);
    ~MainWindow();

private slots:
    void onNew();
    void onOld();

    void on_editButton_clicked();

    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void exit_();

private:
    Ui::MainWindow *ui;

    Storage * storage_; // <-- STORAGE
};

#endif // MAINWINDOW_H
