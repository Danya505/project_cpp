#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "group.h"

class Groups
{
private:
    std::unordered_map<std::string, std::shared_ptr<Group>> groups;

public:
    void add_group(std::shared_ptr<Group> group);
    void delete_group(const std::string &id);
    std::shared_ptr<Group> get_group(const std::string &id);
    std::string all_groups_info() const;
};