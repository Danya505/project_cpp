#pragma once

#include <string>
#include <memory>

class Group;

class User
{
private:
    std::string user_name;
    std::string id;
    std::string meta_information;
    std::weak_ptr<Group> group;

public:
    User();
    User(std::string user_name, std::string id, std::string meta_information);
    std::string get_id() const;
    std::string get_user_name() const;
    std::string get_meta() const;
    std::string get_user_info() const;
    void set_group(std::shared_ptr<Group> g);
    std::shared_ptr<Group> get_group() const;
    void remove_group();
};