#pragma once

#include <string>
#include <vector>
#include <memory>

class User;

class Group
{
private:
    std::string id;
    std::string name;
    std::vector<std::weak_ptr<User>> users;

public:
    Group();
    Group(std::string id, std::string name);
    std::string get_id() const;
    std::string get_name() const;
    void add_user(std::shared_ptr<User> user);
    void remove_user(const std::string &user_id);
    std::string get_group_info() const;
    std::vector<std::string> get_user_ids() const;
};