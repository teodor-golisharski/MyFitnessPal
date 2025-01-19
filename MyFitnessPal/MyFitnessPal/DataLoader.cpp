#include <fstream>
#include <iostream>
#include "DataLoader.h"
#include "ApplicationConstants.h"
#include "OutputMessages.h"

std::vector<std::string> usernames;

void load_usernames()
{
	std::ifstream in_users(USERS_FILE_NAME);
	if (!in_users)
	{
		std::ofstream users(USERS_FILE_NAME);
		users.close();
	}
	else
	{
		std::string line;
		while (std::getline(in_users, line))
		{
			size_t pos = line.find(UNIFIED_DELIMETER);
			if (pos != std::string::npos)
			{

				std::string username = line.substr(0, pos);
				usernames.push_back(username);
			}
		}
		in_users.close();
	}
}

std::vector<std::string> load_logged_user_logs(const std::string& current_username)
{
	std::vector<std::string> logs;

	std::ifstream file(LOGS_FILE_NAME);

	if (!file)
	{
		std::ofstream temp(LOGS_FILE_NAME);
		temp.close();
	}
	else if (!file.is_open())
	{
		std::cerr << FILE_NOT_FOUND << std::endl;
		return logs;
	}
	std::string line;

	while (std::getline(file, line))
	{
		size_t pos_username = line.find(UNIFIED_DELIMETER);
		if (pos_username == std::string::npos)
		{
			continue;
		}

		std::string file_username = line.substr(0, pos_username);

		if (file_username == current_username)
		{
			logs.push_back(line);
		}
	}

	return logs;
}