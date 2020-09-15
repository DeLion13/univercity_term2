#include "csv_storage.h"
#include "csv.hpp"
#include <fstream>
#include <iostream>

using namespace std;

bool CsvStorage::load() {
    string lang_filename = this -> dir_name_ + "lang.csv";
    string composers_csv  = readAllFromFile(lang_filename);
    CsvTable lang_table = Csv::createTableFromString(composers_csv);
    for (CsvRow & row : lang_table) {
        Language l;
        l.id = std::stoi(row[0]);
        l.name = row[1];
        l.type = row[2];
        l.author = row[3];
        this -> lang_.push_back(l);
    }

    string lang_filename2 = this -> dir_name_ + "prog.csv";
    string composers_csv2  = readAllFromFile(lang_filename2);
    CsvTable lang_table2 = Csv::createTableFromString(composers_csv2);
    for (CsvRow & row : lang_table2) {
        Programmer l;
        l.id = std::stoi(row[0]);
        l.name = row[1];
        l.stage = row[2];
        l.date_of_start = row[3];
        this -> lang2_.push_back(l);
    }
    return true;
}

bool CsvStorage::save() {
    string lang_filename = this -> dir_name_ + "lang.csv";
    CsvTable t;
    for (Language & l: this -> lang_) {
        CsvRow r;
        r.push_back(std::to_string(l.id));
        r.push_back(l.name);
        r.push_back(l.type);
        r.push_back(l.author);
        t.push_back(r);
    }
    string csv_text = Csv::createStringFromTable(t);
    writeAllToFile(lang_filename, csv_text);

    string lang_filename2 = this -> dir_name_ + "prog.csv";
    CsvTable t2;
    for (Programmer & l: this -> lang2_) {
        CsvRow r;
        r.push_back(std::to_string(l.id));
        r.push_back(l.name);
        r.push_back(l.stage);
        r.push_back(l.date_of_start);
        t2.push_back(r);
    }
    string csv_text2 = Csv::createStringFromTable(t2);
    writeAllToFile(lang_filename2, csv_text2);
    return true;
}

vector<Language> CsvStorage::getAllLanguages(void) {
    return this -> lang_;
}

bool CsvStorage::updateLanguage(const Language & language) {

    for (Language & l : this -> lang_) {
        if (l.id == language.id) {
            l = language;
        }
    }

    return true;
}

bool CsvStorage::removeLanguage(int language_id) {
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
    return false;
}

int CsvStorage::getNewId() {
    int max_id = 0;
    for (Language & l : this -> lang_) {
        if (l.id >= max_id) {
            max_id = l.id;
        }
    }
    int new_id = max_id + 1;
    return new_id;
}

int CsvStorage::insertLanguage(const Language & language) {
    int new_id = this -> getNewId();
    Language copy = language;
    copy.id = new_id;
    this -> lang_.push_back(copy);
    return new_id;
}

optional<Language> CsvStorage::getLanguageById(int language_id) {
    for (Language & l : this -> lang_) {
        if (l.id == language_id) {
            return l;
        }
    }

    return nullopt;
}

string CsvStorage::readAllFromFile (string const & filename) {
    ifstream file;
    file.open(filename, ios_base::in);
    if (!file.good()) {
        cerr << "Can`t open file: " << filename << endl;
        abort();
    }

    string text_str;
    string row_str;

    while (std::getline(file, row_str)) {
        text_str += row_str + '\n';
    }

    return text_str;
}

void CsvStorage::writeAllToFile (string const & filename, string const & text) {
    ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        cerr << "Wasn`t open file: " << filename << endl;
        abort();
    }
    file << text;
    file.close();
}

vector<Programmer> CsvStorage::getAllProgrammer(void) {
    return this -> lang2_;
}

bool CsvStorage::updateProgrammer(const Programmer & programmer) {

    for (Programmer & l : this -> lang2_) {
        if (l.id == programmer.id) {
            l = programmer;
        }
    }

    return true;
}

bool CsvStorage::removeProgrammer(int programmer_id) {
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
    return false;
}

int CsvStorage::getNewProgId() {
    int max_id = 0;
    for (Programmer & l : this -> lang2_) {
        if (l.id >= max_id) {
            max_id = l.id;
        }
    }
    int new_id = max_id + 1;
    return new_id;
}

int CsvStorage::insertProgrammer(const Programmer & programmer) {
    int new_id = this -> getNewProgId();
    Programmer copy = programmer;
    copy.id = new_id;
    this -> lang2_.push_back(copy);
    return new_id;
}

optional<Programmer> CsvStorage::getProgrammerById(int programmer_id) {
    for (Programmer & l : this -> lang2_) {
        if (l.id == programmer_id) {
            return l;
        }
    }
    return nullopt;
}
