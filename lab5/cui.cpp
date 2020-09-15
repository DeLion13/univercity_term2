#include "cui.hpp"
#include "csv.hpp"
#include "storage.hpp"
#include <iostream>
// #include <progbase.h>
// #include <progbase/console.h>

using std::string;

void Cui::MainMenu() {
    vector<Language> v = this -> storage_ -> getAllLanguages();
    Cui::printTable(v);
}

void Cui::Menu(int entity_id) {
    Language l = this -> storage_ -> getLanguageById(entity_id).value();
    Cui::print(l);
}

void Cui::UpdateMenu(int entity_id) {
    Language copy;
    std::cout << "Updating, input new information: " << std::endl;
    string name;
    std::cout << "Name: ";
    std::cin >> name;
    string type;
    std::cout << "Type: ";
    std::cin >> type;
    string author;
    std::cout << "Author: ";
    std::cin >> author;

    copy.id = entity_id;
    copy.name = name;
    copy.type = type;
    copy.author = author;

    this -> storage_ -> updateLanguage(copy);
}

void Cui::DeleteMenu(int entity_id) {
    this -> storage_ -> removeLanguage(entity_id);
}

void Cui::CreateMenu() {
    std::cout << "Hello, input new Language: " << std::endl;
    string name;
    std::cout << "Name: ";
    std::cin >> name;
    string type;
    std::cout << "Type: ";
    std::cin >> type;
    string author;
    std::cout << "Author: ";
    std::cin >> author;

    Language new_l;
    new_l.name = name;
    new_l.type = type;
    new_l.author = author;

    this -> storage_ -> insertLanguage(new_l);
}

void Cui::MainMenu_p() {
    vector<Programmer> v = this -> storage_ -> getAllProgrammer();
    Cui::printTable_p(v);
}

void Cui::Menu_p(int entity_id) {
    Programmer l = this -> storage_ -> getProgrammerById(entity_id).value();
    Cui::print_p(l);
}

void Cui::UpdateMenu_p(int entity_id) {
    Programmer copy;
    std::cout << "Updating, input new information: " << std::endl;
    string name;
    std::cout << "Name: ";
    std::cin >> name;
    string stage;
    std::cout << "Stage: ";
    std::cin >> stage;
    string date_of_start;
    std::cout << "Date of start (XX.XX.XXXX): ";
    std::cin >> date_of_start;

    copy.id = entity_id;
    copy.name = name;
    copy.stage = stage;
    copy.date_of_start = date_of_start;

    this -> storage_ -> updateProgrammer(copy);
}

void Cui::DeleteMenu_p(int entity_id) {
    this -> storage_ -> removeProgrammer(entity_id);
}

void Cui::CreateMenu_p() {
    std::cout << "Hello, input new Programmer: " << std::endl;
    string name;
    std::cout << "Name: ";
    std::cin >> name;
    string stage;
    std::cout << "Stage: ";
    std::cin >> stage;
    string date_of_start;
    std::cout << "Date of start (XX.XX.XXXX): ";
    std::cin >> date_of_start;

    Programmer new_l;
    new_l.name = name;
    new_l.stage = stage;
    new_l.date_of_start = date_of_start;

    this -> storage_ -> insertProgrammer(new_l);
}

void Cui::show() {
    system("clear");
    bool is_running = true;
    while (is_running) {
        int input;
        std::cout << "Menu:\n1 - Language storage\n2 - Programmers storage\n0 - Exit\nInput command: ";
        std::cin >> input;
        if (input == 1) {
            system("clear");
            bool is_running = true;
            while (is_running) {
                int command;
                std::cout << "Menu:\n1 - Print all elements\n2 - Work with one of elements\n3 - New element\n0 - Exit\nInput command: ";
                std::cin >> command;
                if (command == 0) {
                    is_running = false;
                } else if (command == 1) {
                    // Console_clear();
                    system("clear");
                    Cui::MainMenu();
                } else if (command == 2) {
                    {
                        int input;
                        std::cout << "Input id: ";
                        // Console_clear();
                        system("clear");
                        std::cin >> input;
                        bool start2 = true;
                        while (start2) {
                        
                            int command1;
                            std::cout << "Menu:\n1 - Information\n2 - Update\n3 - Delete\n0 - Exit\nInput command: ";
                            std::cin >> command1;
                            if (command1 == 1) {
                                system("clear");
                                Cui::Menu(input);
                            } else if (command1 == 2) {
                                system("clear");
                                Cui::UpdateMenu(input);
                            } else if (command1 == 3) {
                                Cui::DeleteMenu(input);
                                start2 = false;
                            } else if (command1 == 0) {
                                start2 = false;
                            }
                        }
                        system("clear");
                    }
                } else if (command == 3) {
                    // Console_clear();
                    system("clear");
                    Cui::CreateMenu();
                }
            }
            this -> storage_ -> save();
        } else if (input == 2) {
            system("clear");
            bool is_running = true;
            while (is_running) {
                int command;
                std::cout << "Menu:\n1 - Print all elements\n2 - Work with one of elements\n3 - New element\n0 - Exit\nInput command: ";
                std::cin >> command;
                if (command == 0) {
                    is_running = false;
                } else if (command == 1) {
                    // Console_clear();
                    system("clear");
                    Cui::MainMenu_p();
                } else if (command == 2) {
                    {
                        int input;
                        std::cout << "Input id: ";
                        // Console_clear();
                        system("clear");
                        std::cin >> input;
                        bool start2 = true;
                        while (start2 == true) {
                            int command1;
                            std::cout << "Menu:\n1 - Information\n2 - Update\n3 - Delete\n0 - Exit\nInput command: ";
                            std::cin >> command1;
                            if (command1 == 1) {
                                system("clear");
                                Cui::Menu_p(input);
                            } else if (command1 == 2) {
                                system("clear");
                                Cui::UpdateMenu_p(input);
                            } else if (command1 == 3) {
                                Cui::DeleteMenu_p(input);
                                start2 = false;
                            } else if (command1 == 0) {
                                start2 = false;
                            }
                        }
                        system("clear");
                    }
                } else if (command == 3) {
                    // Console_clear();
                    system("clear");
                    Cui::CreateMenu_p();
                }
            }
            this -> storage_ -> save();
        } else if (input == 0) {
            is_running = false;
        }
        // Console_clear();
        system("clear");
    }
}

void Cui::printTable (vector<Language> & v) {
    for (Language & l : v) {
        printf("%d,", l.id);
        printf("%s,", l.name.c_str());
        printf("%s,", l.type.c_str());
        printf("%s\n", l.author.c_str());
    }
}

void Cui::print (Language & l) {
    printf("%d,", l.id);
    printf("%s,", l.name.c_str());
    printf("%s,", l.type.c_str());
    printf("%s\n", l.author.c_str());
}

void Cui::printTable_p (vector<Programmer> & v) {
    for (Programmer & l : v) {
        printf("%d,", l.id);
        printf("%s,", l.name.c_str());
        printf("%s,", l.stage.c_str());
        printf("%s\n", l.date_of_start.c_str());
    }
}

void Cui::print_p(Programmer & l) {
    printf("%d,", l.id);
    printf("%s,", l.name.c_str());
    printf("%s,", l.stage.c_str());
    printf("%s\n", l.date_of_start.c_str());
}


void Cui::printStringsTable(CsvTable & table) {
    for (int i = 0; i < table.size(); i++) {
        CsvRow row = table[i];
        for (int j = 0; j < row.size(); j++) {
            if (j == 0) {
                printf("%s", row[j].c_str());
            } else {
                printf(",");
                printf("%s", row[j].c_str());
            }
        }
        if (i != table.size() - 1) {
            printf("\n");
        }
    }
}