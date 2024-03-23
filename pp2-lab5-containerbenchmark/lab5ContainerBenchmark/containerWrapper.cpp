#include <iostream>
#include <algorithm> // std::sort, std::find, std::copy
#include <iterator> // std::distance, std::advance, std::back_inserter
#include <limits>   // std::numeric_limits<size_t>::max()
#include <numeric>  // std::accumulate()

using namespace std;

#include "containerWrapper.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
    #warning "Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
    #pragma message ("Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif
using value_type = std::int64_t;
IContainerWrapper::~IContainerWrapper() = default;

void DequeWrapper::insert(const value_type &element, std::size_t position) {
    auto it = impl_.begin();
    it += position;
    impl_.insert(it, element);
}

value_type DequeWrapper::count() const {
    value_type sum = 0;
    for(value_type element: impl_){
        sum += element;
    }
    return sum;
}

std::size_t DequeWrapper::find(const value_type& needle) const {
    for(size_t i = 0; i<impl_.size();i++){
        if(needle == impl_.at(i)){
            return i;
        }
    }
    return std::numeric_limits<size_t>::max();
}

value_type DequeWrapper::pop_front() {
    value_type first_element = impl_.front();
    impl_.pop_front();
    return first_element;
}

value_type DequeWrapper::pop_back() {
    value_type last_element = impl_.back();
    impl_.pop_back();
    return last_element;
}
