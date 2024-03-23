#include <iostream>
#include <algorithm>
#include <cstring>
#include <utility> // std::exchange
using namespace std;

#include "simpleString.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
#else
    #pragma message ("Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif

char *SimpleString::c_str() const {
    return data_;
}
SimpleString::SimpleString(const char *text):size_(strlen(text)), capacity_(strlen(text)) {
    data_= new char[size_+1];
    memcpy(data_, text, size_);
    data_[size_] = '\0';
    instances_++;

}
SimpleString::SimpleString(const SimpleString& text){
    size_ = text.size_;
    capacity_ = text.capacity_;
    data_= new char[size_+1];
    memcpy(data_, text.data_, size_);
    data_[size_] = '\0';
    instances_++;
}
SimpleString::~SimpleString(){
    delete[] data_;
    size_=0;
    capacity_=0;
    data_ = nullptr;
    instances_--;
}

std::size_t SimpleString::instances() {
    return instances_;
}

void SimpleString::assign(const char *new_text) {
    std::size_t temp_text_length = strlen(new_text);
    delete[] data_;
    size_ = temp_text_length;
    capacity_= temp_text_length;
    data_ = new char [temp_text_length+1];
    strncpy(data_, new_text, temp_text_length+1 );
}

bool SimpleString::equal_to(const SimpleString& second_string, bool case_sensitive) const{
 if(!case_sensitive) {
     for (int i = 0; i < (int) second_string.size_; ++i) {
         if (tolower(data_[i]) != tolower(second_string.data_[i])) {
             return false;
         }
     }
 }
 else{
     for (int i = 0; i < (int) second_string.size_; ++i) {
         if (data_[i] != second_string.data_[i]) {
             return false;
         }
     }
 }
    return true;
}

void SimpleString::append(const SimpleString &second_string){
    size_t second_size_ = strlen(second_string.data_);
    char* temp_str = new char[this->size_ + second_size_ + 1];
    strcpy(temp_str, this->data_);
    strcat(temp_str, second_string.data_);
    delete[] data_;
    data_ = temp_str;
    size_ = strlen(temp_str);
    capacity_ = strlen(temp_str);
}

SimpleString SimpleString::substr(size_t pos, size_t count) const {
    if(pos > this->size_){
        throw std::out_of_range("Wrong position");
    }
    else if (pos + count > this->size_ || (int) count == -1){
        count = this->size_ - pos;
    }
    char* temp_string = new char[count + 1];
    memcpy( temp_string, this->data_+ pos, count);
    temp_string[count] = '\0';
    SimpleString sub_string(temp_string);
    delete[] temp_string;
    return sub_string;
}

int SimpleString::compare(const SimpleString& text1, bool case_sensitive) const {
    size_t text1_length = strlen(text1.data_);
    size_t text2_length = size_;
    int i = 0;
        if (!case_sensitive) {
            while (i != (int)text1_length || i != (int)text2_length){
                if(tolower(text1.data_[i]) > tolower(data_[i])){
                    return -1;
                } else if(tolower(text1.data_[i]) < tolower(data_[i])){
                    return 1;
                } else i++;
            }

        } else {
            while (i != (int)text1_length || i != (int)text2_length){
                if(text1.data_[i] > data_[i]){
                    return -1;
                } else if(text1.data_[i] < data_[i]){
                    return 1;
                } else i++;
            }
        }
        if(i == (int)text1_length || i == (int)text2_length){
            return (int) (text1_length - text2_length);
    }
    return 0;
}
SimpleString::SimpleString(SimpleString &&other) noexcept {
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = new char[1]{};
    other.size_ = 0;
    //d
    other.capacity_ = 0;
    instances_++;
}