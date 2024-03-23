#include <iostream>
using namespace std;

#include "user.h"
#include "windows.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
    #warning "Funkcje sa do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
    #pragma message ("Funkcje sa do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif
std::size_t Windows::activated_systems_ = 0;
std::string Windows::version()
{
    return version_;
}
Windows::Windows()
{
    cout << "Windows " << version_ << '\n';
    activated_systems_++;
}
Windows::Windows(std::string difVersion)
{
    version_ = difVersion;
    cout << "Windows " << version_ << '\n';
    activated_systems_++;
}

std::size_t Windows::activated_systems()
{
    return activated_systems_;
}

int Windows::add_user(std::string username, std::string password)
{
    User temp_user;
    temp_user.user_name_ = username;
    temp_user.password_ = password;
    users_.push_back(temp_user);
    return users_.size() - 1;
}
User Windows::user(std::size_t user_id)
{
    return users_.at(user_id);
}
std::string Windows::user_home_directory(const int user_id)
{
    User tempUser = users_[user_id];
    std::string username = tempUser.user_name_;
    return "C:\\Users\\" + username;

}