#include <functional>
#include <algorithm>
#include <string>
#include <cstring>
#include <stdexcept>
#include <utility> // std::exchange
#include "PtrCStringVector.h"
using namespace std;


PtrCStringVector::PtrCStringVector()
{
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

PtrCStringVector::PtrCStringVector(const PtrCStringVector &srcPtrCStringVector): PtrCStringVector()
{
    capacity_ = srcPtrCStringVector.capacity_;
    size_ = srcPtrCStringVector.size_;
    //check
    if (srcPtrCStringVector.data_) {
        data_ = new char * [capacity_];
        for (size_t i = 0; i < size_; i++) {
            const char* str = srcPtrCStringVector.data_[i];
            size_t length = strlen(str);
            data_[i] = new char[length + 1];
            strcpy(data_[i], str);
        }
    }
}

PtrCStringVector::~PtrCStringVector()
{
    free();
    delete [] data_;
}

PtrCStringVector &PtrCStringVector::operator=(const PtrCStringVector &source)
{

    if(this != &source){
        free();
        delete[] data_;
        capacity_ = source.capacity_;
        size_ = source.size_;
        data_ = new char*[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            const char* str = source.data_[i];
            size_t length = strlen(str);
            data_[i] = new char[length + 1];
            strcpy(data_[i], str);
        }
    }
    return *this;
}

PtrCStringVector& PtrCStringVector::operator=(PtrCStringVector&& source)
{

    if (this != &source) {
        free();
        delete[] data_;

        data_ = source.data_;
        size_ = source.size_;
        capacity_ = source.capacity_;

        source.data_ = nullptr;
        source.size_ = 0;
        source.capacity_ = 0;
    }
    return *this;
}

void PtrCStringVector::push_back(const char *text2Add)
{

    if(size_==capacity_){
        reserve(capacity_+1);
    }
    *(data_+size_) = new char[strlen(text2Add)+1];
    strcpy(*(data_+size_), text2Add);

    size_++;

}

PtrCStringVector PtrCStringVector::operator+(const PtrCStringVector &anotherVector) const
{
    PtrCStringVector added_vector(*this);

    for (std::size_t i = 0; i < anotherVector.size_; ++i) {
        added_vector.push_back(anotherVector.data_[i]);
    }

    return added_vector;
}

char *PtrCStringVector::operator[](size_t index)
{


    if (index < size_) {
        return data_[index];
    } else{
        throw std::out_of_range("Out of range");
    }
}
const char *PtrCStringVector::operator[](size_t index) const
{

    if (index < size_) {
        return data_[index];
    } else{
        throw std::out_of_range("Out of range");
    }
}

PtrCStringVector PtrCStringVector::operator&(const PtrCStringVector &rhs) const
{

    PtrCStringVector bit_added_vector;
    bit_added_vector.reserve(std::max(size_, rhs.size_));
    bit_added_vector.size_ = std::max(size_,rhs.size_);

    for (std::size_t i = 0; i < bit_added_vector.size_; i++) {
        std::size_t this_length = (i < size_) ? std::strlen(data_[i]) : 0;
        std::size_t rhs_length = (i < rhs.size_) ? std::strlen(rhs.data_[i]) : 0;

        bit_added_vector.data_[i] = new char[this_length + rhs_length + 1];

        if (i < size_) {
            std::strcpy(bit_added_vector.data_[i], data_[i]);
        }
        if (i < rhs.size_) {
            std::strcat(bit_added_vector.data_[i], rhs.data_[i]);
        }
    }

    return bit_added_vector;
}

void PtrCStringVector::free()
{

    for (size_t i = 0; i < size_; ++i) {
        delete[] data_[i];
    }
    size_ = 0;
}

void PtrCStringVector::reserve(size_t new_capacity)
{

    if (new_capacity > capacity_) {
        capacity_ = new_capacity;
        data_ = (char **)(realloc(data_, new_capacity * sizeof(char *)));
    }
}
