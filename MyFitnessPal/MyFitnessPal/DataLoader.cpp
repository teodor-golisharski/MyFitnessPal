#include <iostream>
#include <vector>
#include <fstream>
#include "ApplicationConstants.h"

static std::vector<std::string> usernames;
static std::vector<std::string> users;
static std::vector<std::string> logs;

void load_usernames() {
	std::ifstream in_users(USERS_FILE_NAME);
	if (!in_users) {
		std::ofstream users(USERS_FILE_NAME);
		users.close();
	}
	else {
		std::string line;
		while (std::getline(in_users, line)) {
			size_t pos = line.find('%');
			if (pos != std::string::npos) {

				std::string username = line.substr(0, pos);
				usernames.push_back(username);
			}
		}
		in_users.close();
	}
}
void load_users() {
	std::ifstream in_users(USERS_FILE_NAME);
	if (!in_users) {
		std::ofstream users(USERS_FILE_NAME);
		users.close();
	}
	else {
		std::string line;
		while (std::getline(in_users, line)) {
			users.push_back(line);
		}
		in_users.close();
	}
}
