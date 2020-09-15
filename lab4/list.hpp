#pragma once

#include <cstdlib>

class List {
        float * items_;
        size_t capacity_;
        size_t size_;
    private:
        void   reall(int newCap);
    public:
        List();
        ~List();

        void   add(float value);
        void   insert(int index, float value);
        void   removeAt(size_t index);
        void   remove   (float value);
        float & operator [](int index);
        void   clear();
        size_t size();
        void   print();
        void   ten();
        int    indexOf(float value);
        bool   contains(float value);
        bool   isEmpty();
        void   error();
};