#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include "user.h"
#include "group.h"
#include "users.h"
#include "groups.h"

int main()
{
    Users users;
    Groups groups;
    std::string command;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, command);
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "createUser")
        {
            std::string id, name, meta;
            iss >> id >> name >> meta;

            auto user = std::make_shared<User>(name, id, meta);
            users.add_user(user);
            std::cout << "User created.\n";
        }
        else if (cmd == "deleteUser")
        {
            std::string id;
            iss >> id;
            auto u = users.get_user(id);
            if (u)
            {
                auto g = u->get_group();
                if (g)
                    g->remove_user(id);
            }
            users.delete_user(id);
            std::cout << "User deleted.\n";
        }
        else if (cmd == "allUsers")
        {
            std::cout << users.all_users_info();
        }
        else if (cmd == "getUser")
        {
            std::string id;
            iss >> id;
            auto u = users.get_user(id);
            if (u)
                std::cout << u->get_user_info() << "\n";
            else
                std::cout << "User not found\n";
        }
        else if (cmd == "createGroup")
        {
            std::string id, name;
            iss >> id >> name;
            auto group = std::make_shared<Group>(id, name);
            groups.add_group(group);
            std::cout << "Group created.\n";
        }
        else if (cmd == "deleteGroup")
        {
            std::string id;
            iss >> id;
            auto g = groups.get_group(id);
            if (g)
            {
                for (const auto &uid : g->get_user_ids())
                {
                    auto u = users.get_user(uid);
                    if (u)
                        u->remove_group();
                }
            }
            groups.delete_group(id);
            std::cout << "Group deleted.\n";
        }
        else if (cmd == "setUserGroup")
        {
            std::string user_id, group_id;
            iss >> user_id >> group_id;

            auto u = users.get_user(user_id);
            if (!u)
            {
                std::cout << "User not found\n";
                continue;
            }

            if (group_id == "none")
            {
                auto old_g = u->get_group();
                if (old_g)
                    old_g->remove_user(user_id);
                u->remove_group();
                std::cout << "User removed from group.\n";
                continue;
            }

            auto new_g = groups.get_group(group_id);
            if (!new_g)
            {
                std::cout << "Group not found\n";
                continue;
            }

            auto old_g = u->get_group();
            if (old_g)
                old_g->remove_user(user_id);

            new_g->add_user(u);
            u->set_group(new_g);
            std::cout << "User " << user_id << " added to group " << group_id << "\n";
        }
        else if (cmd == "allGroups")
        {
            std::cout << groups.all_groups_info();
        }
        else if (cmd == "getGroup")
        {
            std::string id;
            iss >> id;
            auto g = groups.get_group(id);
            if (g)
                std::cout << g->get_group_info() << "\n";
            else
                std::cout << "Group not found\n";
        }
        else if (cmd == "exit")
            break;
        else
            std::cout << "Unknown command\n";
    }
    return 0;
}