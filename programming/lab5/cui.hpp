#include "storage.hpp"

class Cui {
    Storage * const storage_;

    // students menus
    void MainMenu();
    void Menu(int entity_id);
    void UpdateMenu(int entity_id);
    void DeleteMenu(int entity_id);
    void CreateMenu();
    void printStringsTable (CsvTable & table);
    void printTable (vector<Language> & v);
    void print (Language & l);

    void MainMenu_p();
    void Menu_p(int entity_id);
    void UpdateMenu_p(int entity_id);
    void DeleteMenu_p(int entity_id);
    void CreateMenu_p();
    void printTable_p (vector<Programmer> & v);
    void print_p (Programmer & l);
    
public:
    Cui(Storage * storage): storage_(storage) {}
    //
    void show();
};