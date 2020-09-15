#ifndef USER_H
#define USER_H
#pragma once

#include <string>

using std::string;

struct User {
    int     id;
    string  username;
    string  password_hash;
};

#endif // USER_H
