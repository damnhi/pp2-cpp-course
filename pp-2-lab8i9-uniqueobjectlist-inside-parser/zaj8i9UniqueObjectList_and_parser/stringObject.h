#pragma once

#include <iosfwd>
#include <string>
#include "object.h"


class StringObject : public Object
{
    std::string text;

public:    
//     TODO:
    bool operator==(const Object& obj) const override;
    StringObject(std::string given_string): text(std::move(given_string)){};
    ~StringObject() override = default;

    Object* clone() const override
    {
       return new StringObject(*this);
    }
};
