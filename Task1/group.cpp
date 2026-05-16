#include "group.h"
#include "user.h"
#include <algorithm>

Group::Group() : id(""), name("") {}

Group::Group(std::string id, std::string name) : id(id), name(name) {}

std::string Group::get_id() const { return id; }
std::string Group::get_name() const { return name; }

void Group::add_user(std::shared_ptr<User> user)
{
    users.push_back(user);
}

void Group::remove_user(const std::string &user_id)
{
    users.erase(std::remove_if(users.begin(), users.end(),
                               [&user_id](const std::weak_ptr<User> &wp)
                               {
                                   auto u = wp.lock();
                                   return !u || u->get_id() == user_id;
                               }),
                users.end());
}

std::string Group::get_group_info() const
{
    std::string result = "Group ID: " + id + ", Name: " + name + ", Users: ";
    for (const auto &wp : users)
    {
        if (auto u = wp.lock())
            result += u->get_id() + " ";
    }
    return result;
}

std::vector<std::string> Group::get_user_ids() const
{
    std::vector<std::string> ids;
    for (const auto &wp : users)
    {
        if (auto u = wp.lock())
            ids.push_back(u->get_id());
    }
    return ids;
}