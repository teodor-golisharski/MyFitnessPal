#pragma once
#include <vector>
#include <string>

extern std::vector<std::string> usernames;
extern std::vector<std::string> users;

void load_usernames();
void load_users();
std::vector<std::string> load_logged_user_logs(const std::string& current_username);