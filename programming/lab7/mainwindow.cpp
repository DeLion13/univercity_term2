#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xml_storage.h"
#include "dialog.h"

#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

Q_DECLARE_METATYPE(Language);
Q_DECLARE_METATYPE(Language *);

Language copy(Language * l) {
    Language l_copy;
    l_copy.id = l -> id;
    l_copy.name = l -> name;
    l_copy.type = l -> type;
    l_copy.author = l -> author;

    return l_copy;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui -> setupUi(this);

    connect(ui -> actionAdd_storage, &QAction::triggered, this, &MainWindow::onNew);
    connect(ui -> actionOpen_storage, &QAction::triggered, this, &MainWindow::onOld);
    connect(ui -> actionExit, &QAction::triggered, this, &MainWindow::exit_);
    qDebug() << "ctor()";
}

MainWindow::~MainWindow() {
    qDebug() << "~ctor()";
    if (this -> storage_ != nullptr) {
        this -> storage_ -> save();
        delete storage_;
    }
    delete ui;
}

void MainWindow::onNew() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString current_dir = QDir::currentPath();
    QString default_name = "new_storage";
    QString folder_path = dialog.getSaveFileName(
       this,
       "Select New Storage Folder",
       current_dir + "/" + default_name,
       "Folders");
    if (this -> storage_ != nullptr) {
        ui -> listWidget -> clear();
        delete storage_;
    }
    XmlStorage * xml_ptr = new XmlStorage(folder_path.toStdString());
    this -> storage_ = xml_ptr;
    this -> storage_ -> save();
    this -> storage_ -> load();

    vector<Language> langs = this -> storage_ -> getAllLanguages();

    for (int i = 0; i < langs.size(); i++) {
        QVariant qVariant;
        qVariant.setValue(langs[i]);
        QListWidgetItem * qStudentListItem = new QListWidgetItem();
        qStudentListItem -> setText(langs[i].name.c_str());
        qStudentListItem->setData(Qt::UserRole, qVariant);
        ui->listWidget->addItem(qStudentListItem);
    }
}

void MainWindow::onOld() {
    QString fileName = QFileDialog::getOpenFileName(
         this,              // parent
         "Dialog Caption",  // caption
         "",                // directory to start with
         "XML (*.xml);;All Files (*)");  // file name filter
    qDebug() << fileName;
    if (this -> storage_ != nullptr) {
        ui -> listWidget -> clear();
        delete storage_;
    }
    XmlStorage * xml_ptr = new XmlStorage(fileName.toStdString());
    this -> storage_ = xml_ptr;
    this -> storage_ -> load();

    vector<Language> langs = this -> storage_ -> getAllLanguages();

    for (int i = 0; i < langs.size(); i++) {
        QVariant qVariant;
        qVariant.setValue(langs[i]);
        QListWidgetItem * qStudentListItem = new QListWidgetItem();
        qStudentListItem -> setText(langs[i].name.c_str());
        qStudentListItem -> setData(Qt::UserRole, qVariant);
        ui -> listWidget -> addItem(qStudentListItem);
    }
}

void MainWindow::on_editButton_clicked() {
    QList<QListWidgetItem *> item = ui -> listWidget -> selectedItems();
    if (item.count() == 1) {
        QListWidgetItem * selectedItem = item.at(0);
        QVariant var = selectedItem -> data(Qt::UserRole);
        Language * lang = static_cast<Language *>(var.data());

        Dialog dialog(lang);
        dialog.setWindowTitle("Edit");
        dialog.exec();

        var.clear();
        var.setValue(copy(lang));
        selectedItem -> setText(lang -> name.c_str());
        selectedItem -> setData(Qt::UserRole, var);

        this -> storage_ -> updateLanguage(copy(lang));
        this -> storage_ -> save();
    }
}

void MainWindow::on_addButton_clicked() {
    if (this -> storage_ != nullptr) {
        Language lang;
        Dialog dialog(&lang);
        dialog.setWindowTitle("Add");
        dialog.exec();

        int id = this -> storage_ -> insertLanguage(lang);
        this -> storage_ -> save();
        lang.id = id;
        QVariant var;
        var.setValue(lang);

        QListWidgetItem * qStudentListItem = new QListWidgetItem();
        qStudentListItem -> setText(lang.name.c_str());
        qStudentListItem -> setData(Qt::UserRole, var);
        ui -> listWidget -> addItem(qStudentListItem);
    }
}

void MainWindow::on_removeButton_clicked() {
    QList<QListWidgetItem *> items = ui -> listWidget -> selectedItems();
    QMessageBox::StandardButton reply;
       reply = QMessageBox::question(
           this,
           "On delete",
           "Are you sure?",
           QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {
           if (items.count() != 0) {
               foreach (QListWidgetItem * selectedItem, items) {
                   QVariant var = selectedItem -> data(Qt::UserRole);
                   Language * lang = static_cast<Language *>(var.data());
                   qDebug() <<lang -> id;

                   this -> storage_ -> removeLanguage(lang -> id);
                   this -> storage_ -> save();
                   int row_index = ui -> listWidget -> row(selectedItem);
                   ui -> listWidget -> takeItem(row_index);

                   delete  selectedItem;
               }
           }
       }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem * item) {
    QVariant var = item -> data(Qt::UserRole);
    Language * lang = static_cast<Language *>(var.data());

    ui -> nameLabel -> setText(lang -> name.c_str());
    ui -> typeLabel -> setText(lang -> type.c_str());
    ui -> authorLabel -> setText(lang -> author.c_str());
}

void MainWindow::exit_() {
    QMessageBox::StandardButton reply;
       reply = QMessageBox::question(
           this,
           "On delete",
           "Are you sure?",
           QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {
           close();
       } else {
           return;
       }

}
