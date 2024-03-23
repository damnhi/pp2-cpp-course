#include <iostream>
using namespace std;

#include "user.h"
#include "linux.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
    #warning "Funkcje sa do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
    #pragma message ("Funkcje sa do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif
std::size_t Linux::open_source_sympathizers_ = 0;
Linux::Linux()
{
    cout<<"+" << distribution_ << '\n';
    open_source_sympathizers_++;
}


Linux::Linux(std::string newDistribution_)
{
    distribution_ = newDistribution_;
    cout<<"+" << distribution_ << '\n';
    open_source_sympathizers_++;
}


Linux::~Linux()
{
    cout<<"~" << distribution_ << '\n';
    open_source_sympathizers_--;
}


std::string Linux::distribution()
{
    return distribution_;
}


std::size_t Linux::open_source_sympathizers()
{
    return open_source_sympathizers_;
}


//*users_.push_back(User(username));
int Linux::add_user(std::string username, std::string password)
{
    User temp_user;
    temp_user.user_name_ = username;
    temp_user.password_ = password;
    users_.push_back(temp_user);
    return users_.size() - 1;
}

User Linux::user(std::size_t user_id)
{
    return users_.at(user_id);
}

std::string Linux::user_home_directory(const int user_id)
{
    User tempUser = users_[user_id];
    std::string username = tempUser.user_name_;
   return "/home/" + username + "/";

}
std::optional<std::string> Linux::graphic_environment() const
{
     return graphic_environment_;

}

void Linux::set_graphic_environment(std::string graphicEnvName){
    graphic_environment_ = graphicEnvName;
}