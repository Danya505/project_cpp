#include "users.h"

void Users::add_user(std::shared_ptr<User> user)
{
    users[user->get_id()] = user;
}

void Users::delete_user(const std::string &user_id)
{
    users.erase(user_id);
}

std::shared_ptr<User> Users::get_user(const std::string &user_id)
{
    auto it = users.find(user_id);
    return it != users.end() ? it->second : nullptr;
}

std::string Users::all_users_info() const
{
    std::string result;
    for (const auto &pair : users)
        result += pair.second->get_user_info() + "\n";
    return result;
}