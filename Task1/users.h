#pragma once

#include "user.h"
#include <unordered_map>
#include <string>
#include <memory>

class Users
{
private:
    std::unordered_map<std::string, std::shared_ptr<User>> users;

public:
    void add_user(std::shared_ptr<User> user);
    void delete_user(const std::string &user_id);
    std::shared_ptr<User> get_user(const std::string &user_id);
    std::string all_users_info() const;
};