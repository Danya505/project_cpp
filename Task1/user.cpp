#include "user.h"
#include "group.h"

User::User() : user_name(""), id(""), meta_information("") {}

User::User(std::string user_name, std::string id, std::string meta_information)
    : user_name(user_name), id(id), meta_information(meta_information) {}

std::string User::get_id() const { return id; }
std::string User::get_user_name() const { return user_name; }
std::string User::get_meta() const { return meta_information; }

std::string User::get_user_info() const
{
    std::string group_info = "none";
    if (auto g = group.lock())
        group_info = g->get_id();
    return "ID: " + id + ", Name: " + user_name + ", Meta: " + meta_information + ", Group: " + group_info;
}

void User::set_group(std::shared_ptr<Group> g) { group = g; }

std::shared_ptr<Group> User::get_group() const { return group.lock(); }

void User::remove_group() { group.reset(); }