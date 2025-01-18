#pragma once
#include <vector>
#include <string>

extern std::vector<std::string> usernames;

void load_usernames();

std::vector<std::string> load_logged_user_logs(const std::string& current_username);