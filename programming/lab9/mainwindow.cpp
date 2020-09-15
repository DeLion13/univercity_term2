#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xml_storage.h"
#include "sqlite_storage.h"
#include "dialog.h"
#include "dialog_e.h"
#include "login.h"

#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlQuery>

Q_DECLARE_METATYPE(Language);
Q_DECLARE_METATYPE(Language *);
Q_DECLARE_METATYPE(Programmer);
Q_DECLARE_METATYPE(Programmer *);
Q_DECLARE_METATYPE(User);
Q_DECLARE_METATYPE(User *);

User getUserById(int id) {
    vector<User> users;

    QSqlQuery query("SELECT * FROM users");
    while (query.next()) {
       int id_v = query.value("id").toInt();
       string username = query.value("username").toString().toStdString();
       string password_hash = query.value("password_hash").toString().toStdString();
       User u;
       u.id = id_v;
       u.username = username;
       u.password_hash = password_hash;

       users.push_back(u);
    }

    for (int i = 0; i < users.size(); i++) {
        if (id == users[i].id) {
            qDebug() << users[i].id;
            qDebug() << users[i].username.c_str();
            qDebug() << users[i].password_hash.c_str();
            User us;
            us.id = users[i].id;
            us.username = users[i].username.c_str();
            us.password_hash = users[i].password_hash.c_str();
            return  us;
        }
    }
}

Language copy(Language * l) {
    Language l_copy;
    l_copy.id = l -> id;
    l_copy.name = l -> name;
    l_copy.type = l -> type;
    l_copy.author = l -> author;
    l_copy.user_id = l -> user_id;

    return l_copy;
}

Programmer copy_p(Programmer * l) {
    Programmer l_copy;
    l_copy.id = l -> id;
    l_copy.name = l -> name;
    l_copy.stage = l -> stage;
    l_copy.date_of_start = l -> date_of_start;

    return l_copy;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui -> setupUi(this);

    this -> storage_ = nullptr;

    connect(ui -> actionOpen_storage, &QAction::triggered, this, &MainWindow::onOld);
    connect(ui -> actionExit, &QAction::triggered, this, &MainWindow::exit_);
    qDebug() << "ctor()";
}

MainWindow::~MainWindow() {
    qDebug() << "~ctor()";
    if (this -> storage_ != nullptr) {
        qDebug() << "Deleting of storage";
        this -> storage_ -> close();
        delete storage_;
    }
    delete ui;
}

void MainWindow::onOld() {
    QString fileName = QFileDialog::getOpenFileName(
         this,              // parent
         "Dialog Caption",  // caption
         "",                // directory to start with
         "SQL (*.sqlite);;All Files (*)");  // file name filter

    qDebug() << fileName;
    if (this -> storage_ != nullptr) {
        ui -> listWidget -> clear();
        delete storage_;
    }

    //XmlStorage * xml_ptr = new XmlStorage(fileName.toStdString());
    SqliteStorage * sql_ptr = new SqliteStorage(fileName.toStdString());
    this -> storage_ = sql_ptr;
    bool opened = this -> storage_ -> open();
    bool cool = false;

    if (opened) {
        cool = this -> storage_ -> login_pass();
    }

    if (cool) {
        vector<Language> langs = this -> storage_ -> getYourLangs();

        for (int i = 0; i < langs.size(); i++) {
            QVariant qVariant;
            qVariant.setValue(langs[i]);
            QListWidgetItem * qStudentListItem = new QListWidgetItem();
            qStudentListItem -> setText(langs[i].name.c_str());
            qStudentListItem -> setData(Qt::UserRole, qVariant);
            ui -> listWidget -> addItem(qStudentListItem);
        }

        User u = getUserById(this -> storage_ -> returnId());

        ui -> label_7 -> setText(u.username.c_str());
    } else {
        this -> storage_ = nullptr;
        delete sql_ptr;
    }
}

void MainWindow::on_editButton_clicked() {
    QList<QListWidgetItem *> item = ui -> listWidget -> selectedItems();
    if (item.count() == 1) {
        QListWidgetItem * selectedItem = item.at(0);
        QVariant var = selectedItem -> data(Qt::UserRole);
        Language * lang = static_cast<Language *>(var.data());

        Dialog_e * dialog =  new Dialog_e(this -> storage_, lang);
        dialog -> setWindowTitle("Edit");
        dialog -> exec();
        delete  dialog;

        var.clear();
        var.setValue(copy(lang));
        selectedItem -> setText(lang -> name.c_str());
        selectedItem -> setData(Qt::UserRole, var);

        this -> storage_ -> updateLanguage(copy(lang));
    }
}

void MainWindow::on_addButton_clicked() {
    if (this -> storage_ != nullptr) {
        Language lang;
        Dialog dialog(&lang, this -> storage_ -> returnId());
        dialog.setWindowTitle("Add");
        dialog.exec();

        int id = this -> storage_ -> insertLanguage(lang);
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

                   this -> storage_ -> removeLanguage(lang -> id);
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

    QString users;
    vector <Programmer> progs = this -> storage_ -> getProgrammersForLang(*lang);

    users += progs[0].name.c_str();
    users += " (+";
    users += QString::number(progs.size() - 1);
    users += ")";

    ui -> label_9 -> setText(users);
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
