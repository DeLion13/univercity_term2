#include "sqlite_storage.h"
#include "storage.hpp"
#include "language.hpp"

#include <QDebug>
#include <QtSql>

Q_DECLARE_METATYPE(Language);
Q_DECLARE_METATYPE(Programmer);

Language getLanguageFromQuery(const QSqlQuery & query) {
    int id = query.value("id").toInt();
    string name = query.value("name").toString().toStdString();
    string type = query.value("type").toString().toStdString();
    string author = query.value("author").toString().toStdString();

    Language l;
    l.id = id;
    l.name = name;
    l.type = type;
    l.author = author;

    return l;
}

Programmer getProgrammerFromQuery(const QSqlQuery & query) {
    int id = query.value("id").toInt();
    string name = query.value("name").toString().toStdString();
    string stage = query.value("stage").toString().toStdString();
    string date_of_start = query.value("date_of_start").toString().toStdString();

    Programmer l;
    l.id = id;
    l.name = name;
    l.stage = stage;
    l.date_of_start = date_of_start;

    return l;
}

SqliteStorage::SqliteStorage(const string & dir_name) : dir_name_(dir_name) {
    db_ = QSqlDatabase::addDatabase("QSQLITE");

}

bool SqliteStorage::load() {
    QString path = QString::fromStdString(this -> dir_name_) + "data.sqlite";
    db_.setDatabaseName(path);

    bool connected = db_.open();  // open db connection
    if (!connected) {
        return false;
    }

    return  true;
}
bool SqliteStorage::save() {
    db_.close();
    return  false;
}
// Languages
vector<Language> SqliteStorage::getAllLanguages(void) {
    vector<Language> langs;
    QSqlQuery query("SELECT * FROM lang");
    while (query.next())
    {
       int id = query.value("id").toInt();
       string name = query.value("name").toString().toStdString();
       string type = query.value("type").toString().toStdString();
       string author = query.value("author").toString().toStdString();

       Language l;
       l.id = id;
       l.name = name;
       l.type = type;
       l.author = author;

       this -> lang_.push_back(l);
    }

    return  this -> lang_;
}

optional<Language> SqliteStorage::getLanguageById(int language_id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM lang WHERE id = :id");
    query.bindValue(":id", language_id);
    if (!query.exec()) {  // do exec if query is prepared SELECT query
       qDebug() << "get person error:" << query.lastError();
       return  nullopt;
    }
    if (query.next()) {
       Language l = getLanguageFromQuery(query);
       return  l;
    } else {
       qDebug() << " not found ";
       return nullopt;
    }
    return nullopt;
}
bool SqliteStorage::updateLanguage(const Language & language) {
    QSqlQuery query;
    query.prepare("UPDATE lang SET name = :name, type = :type, author = :author WHERE id = :id");
    query.bindValue(":name", QString::fromStdString(language.name));
    query.bindValue(":type", QString::fromStdString(language.type));
    query.bindValue(":author",  QString::fromStdString(language.author));
    query.bindValue(":id", language.id);
    if (!query.exec()){
        qDebug() << "updatePerson error:" << query.lastError();
    }
    for (Language & l : this -> lang_) {
        if (l.id == language.id) {
            l = language;
        }
    }
}
bool SqliteStorage::removeLanguage(int language_id) {

    QSqlQuery query;
    query.prepare("DELETE FROM lang WHERE id = :id");
    query.bindValue(":id", language_id);
    if (!query.exec()) {
        qDebug() << "deletePerson error:" << query.lastError();
    }

    if (query.numRowsAffected() == 0) {
        return  false;
    }

    int index = -1;
    for (int i = 0; i < this -> lang_.size(); i++) {
        if (this -> lang_[i].id == language_id) {
            index = i;
        }
    }
    if (index >= 0) {
        this -> lang_.erase(this -> lang_.begin() + index);
        return true;
    }

}

int SqliteStorage::getNewId() {
    int max_id = 0;
    for (Language & l : this -> lang_) {
        if (l.id >= max_id) {
            max_id = l.id;
        }
    }
    int new_id = max_id + 1;
    return new_id;
}


int SqliteStorage::insertLanguage(const Language & language) {

    QSqlQuery query;
    query.prepare("INSERT INTO lang (name, type, author) VALUES (:name, :type, :author)");
    query.bindValue(":name", QString::fromStdString(language.name));
    query.bindValue(":type", QString::fromStdString(language.type));
    query.bindValue(":author",  QString::fromStdString(language.author));
    if (!query.exec()){
        return 0;
    }
    QVariant var = query.lastInsertId();
    int new_id = this -> getNewId();
    Language copy = language;
    copy.id = new_id;
    this -> lang_.push_back(copy);
    return var.toInt();
}
// Programmer
vector<Programmer> SqliteStorage::getAllProgrammer(void) {
    vector<Programmer> langs;
    QSqlQuery query("SELECT * FROM prog");
    while (query.next())
    {
        int id = query.value("id").toInt();
        string name = query.value("name").toString().toStdString();
        string stage = query.value("stage").toString().toStdString();
        string date_of_start = query.value("date_of_start").toString().toStdString();

        Programmer l;
        l.id = id;
        l.name = name;
        l.stage = stage;
        l.date_of_start = date_of_start;

        this -> lang2_.push_back(l);
    }

    return  this -> lang2_;
}
optional<Programmer> SqliteStorage::getProgrammerById(int lprogrammer_id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM prog WHERE id = :id");
    query.bindValue(":id", lprogrammer_id);
    if (!query.exec()) {  // do exec if query is prepared SELECT query
       qDebug() << "get person error:" << query.lastError();
       return  nullopt;
    }
    if (query.next()) {
       Programmer l = getProgrammerFromQuery(query);
       return  l;
    } else {
       qDebug() << " not found ";
       return nullopt;
    }
    return nullopt;
}
bool SqliteStorage::updateProgrammer(const Programmer & programmer) {
    QSqlQuery query;
    query.prepare("UPDATE prog SET name = :name, stage = :stage, date_of_start = :date_of_start WHERE id = :id");
    query.bindValue(":name", QString::fromStdString(programmer.name));
    query.bindValue(":type", QString::fromStdString(programmer.stage));
    query.bindValue(":author",  QString::fromStdString(programmer.date_of_start));
    query.bindValue(":id", programmer.id);
    if (!query.exec()){
        qDebug() << "updatePerson error:" << query.lastError();
    }
    for (Programmer & l : this -> lang2_) {
        if (l.id == programmer.id) {
            l = programmer;
        }
    }
}
bool SqliteStorage::removeProgrammer(int programmer_id) {
    QSqlQuery query;
    query.prepare("DELETE FROM prog WHERE id = :id");
    query.bindValue(":id", programmer_id);
    if (!query.exec()) {
        qDebug() << "deletePerson error:" << query.lastError();
    }

    if (query.numRowsAffected() == 0) {
        return  false;
    }

    int index = -1;
    for (int i = 0; i < this -> lang2_.size(); i++) {
        if (this -> lang2_[i].id == programmer_id) {
            index = i;
        }
    }
    if (index >= 0) {
        this -> lang2_.erase(this -> lang2_.begin() + index);
        return true;
    }
}
int SqliteStorage::insertProgrammer(const Programmer & programmer) {
    QSqlQuery query;
    query.prepare("INSERT INTO prog (name, stage, date_of_start) VALUES (:name, :stage, :date_of_start)");
    query.bindValue(":name", QString::fromStdString(programmer.name));
    query.bindValue(":type", QString::fromStdString(programmer.stage));
    query.bindValue(":author",  QString::fromStdString(programmer.date_of_start));
    if (!query.exec()){
        return 0;
    }
    QVariant var = query.lastInsertId();
    int new_id = this -> getNewId();
    Programmer copy = programmer;
    copy.id = new_id;
    this -> lang2_.push_back(copy);
    return var.toInt();
}
