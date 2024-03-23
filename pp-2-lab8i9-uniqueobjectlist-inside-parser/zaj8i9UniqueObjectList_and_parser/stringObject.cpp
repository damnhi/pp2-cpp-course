#include <iostream>
#include <random>
#include <typeinfo>
#include <type_traits>
#include <cstring>
#include <cctype>
#include "stringObject.h"
using namespace std;

// TODO:


bool StringObject::operator==(const Object &obj) const {
    if (const auto* other = dynamic_cast<const StringObject*>(&obj)) {
        return text == other->text;
    } else return false;
}

