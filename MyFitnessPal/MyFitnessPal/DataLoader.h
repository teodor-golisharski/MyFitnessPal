/**
*
* Solution to course project # 9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Teodor Golisharski
* @idnumber 6MI0600367 @compiler VC
*
* <loading data file>
*
*/

#pragma once
#include <vector>
#include <string>

extern std::vector<std::string> usernames;

void load_usernames();

std::vector<std::string> load_logged_user_logs(const std::string& current_username);