#pragma once

#include <cstdlib>

class Stack {
        int cap_;
        int length_; 
        float * arr_;
    public:
        Stack();
        ~Stack();

        size_t  size ();
        void    push (float value);
        float   peek ();
        float   pop ();
        void    print();
        bool    isEmpty ();
};