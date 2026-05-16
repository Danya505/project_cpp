#include "groups.h"

void Groups::add_group(std::shared_ptr<Group> group)
{
    groups[group->get_id()] = group;
}

void Groups::delete_group(const std::string &id)
{
    groups.erase(id);
}

std::shared_ptr<Group> Groups::get_group(const std::string &id)
{
    auto it = groups.find(id);
    return it != groups.end() ? it->second : nullptr;
}

std::string Groups::all_groups_info() const
{
    std::string result;
    for (const auto &pair : groups)
        result += pair.second->get_group_info() + "\n";
    return result;
}