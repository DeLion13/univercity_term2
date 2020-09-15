#include "list.hpp"

#include <cstdio>
#include <cmath>

List::List() {
    this -> capacity_ = 4;
    this -> size_ = 0;
    const int tmp = this -> capacity_;
    this -> items_ = static_cast<float *>(malloc(sizeof(float) * this -> capacity_));
    if (this -> items_ == nullptr) {
        fprintf(stderr, "Allocating memory error\n");
        abort();
    }
}

List::~List   () {
    free(this -> items_);
}

size_t List::size () {
    return this -> size_;
}

void List::insert (int index, float value) {
    if (index < 0 || index >= this -> size_) {
        List::error();
        return;
    }
    if (this -> size_ == this -> capacity_) {
        List::reall(this -> capacity_ * 2);
    }
    for (int i = this -> size_ - 1; i >= index; i--) {
        this -> items_[i + 1] = this -> items_[i];
    }
    this -> items_[index] = value;
    this -> size_ += 1;
}

void List::reall(int newCap) {
    float * newArray = static_cast<float *>(realloc(this -> items_, sizeof(float) * newCap));
    if (newArray == nullptr) {
        fprintf(stderr, "Reallocating memory error\n");
        abort();
    }
    this -> items_ = newArray;
    this -> capacity_ = newCap;
}

void List::removeAt (size_t index) {
    if (index < 0 || index >= this -> size_) {
        List::error();
        return;
    }
    for (int i = index; i < this -> size_ - 1; i++) {
        this -> items_[i] = this -> items_[i + 1];
    }
    this -> size_ -= 1;
}

void List::add (float value) {
    if (this -> size_ == this -> capacity_) {
        List::reall(this -> capacity_ * 2);
    }
    this -> items_[this -> size_] = value;
    this -> size_ += 1;
}

void List::remove (float value) {
    List::removeAt(List::indexOf(value));
}

int List::indexOf (float value) {
    for (int i = 0; i < this -> size_; i++) {
        if (this -> items_[i] == value) {
            return i;
        }
    }
    printf("Not found your element!");
    return -1;
}

bool List::contains (float value) {
    bool c = false;
    for (int i = 0; i < this -> size_; i++) {
        if (this -> items_[i] == value) {
            c = true;
        }
    }
    return c;
}

bool List::isEmpty () {
    bool emp = false;
    if (this -> items_ == nullptr) {
        emp = true;
    }
    return emp;
}

void List::clear () {
    this -> size_ = 0;
}

void List::print () {
    for(int i = 0; i < this -> size_; i++) {
        if (i < this -> size_ - 1) {
            printf("%.3f -> ", this -> items_[i]);
        } else {
            printf("%.3f", this -> items_[i]);
        }
        
    }
    printf("\n");
}

void List::ten () {
    int r = 0;
    for (int i = 0; i < this -> size_; i++) {
        if (fabs(this -> items_[i]) > 10) {
            List::insert(r, this -> items_[i]);
            List::removeAt(i + 1);
            r++;
        }
    }
}

void List::error() {
    fprintf(stderr, "Segmentation fault!");
}

float & List::operator [](int index) {
    if (index < 0) {
        abort();
    }
    return this->items_[index];
}
