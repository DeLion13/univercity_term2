#include "stack.hpp"

#include <cstdio>
#include <cstdlib>
#include <cmath>

Stack::Stack() {
    this -> cap_ = 4;
    const int tmp = this -> cap_;
    this -> length_ = 0;
    this -> arr_ = static_cast<float *>(malloc(sizeof(float) * this -> cap_));
    if (this -> arr_ == nullptr) {
        fprintf(stderr, "Allocating memory error\n");
        abort();
    }
}

Stack::~Stack() {
    free(this -> arr_);
}

void Stack::push(float value) {
    this -> arr_[this -> length_] = value;
    this -> length_ += 1;
    if (this -> length_ == this -> cap_) {
        int newcap = this -> cap_ * 2;
        float * newarr = static_cast<float *>(realloc(this -> arr_, sizeof(float) * newcap));
        if (newarr == nullptr) {
            fprintf(stderr, "Reallocating memory error\n");
            abort();
        }
        this -> arr_ = newarr;
        this -> cap_ = newcap;
    }
}

float Stack::pop() {
    float oldValue = this -> arr_[this -> length_ - 1];
    this -> length_ -= 1;
    return oldValue;
}

float Stack::peek() {
    return this -> arr_[this -> length_ - 1];
}

size_t Stack::size() {
    return this -> length_;
}

void Stack::print() {
    for (int i = 0; i < Stack::size(); i++) {
        if (i == 0) {
            printf("%.3f", this -> arr_[i]);
        } else {
            printf(" <- %.3f", this -> arr_[i]);
        }
    }
    printf("\n");
}

bool Stack::isEmpty () {
    bool emp = false;
    if (this -> arr_ == nullptr) {
        emp = true;
    }
    return emp;
}