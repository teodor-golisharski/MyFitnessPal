/*
*
* Solution to course project # 9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Teodor Golisharski
* @idnumber 6MI0600367
* @compiler VC
*
* MyFitnessPal CLI Application
*
*/


#include <iostream>
#include <string>
#include <vector>
#include <fstream>

static std::vector<std::string> usernames;
static std::vector<std::string> logs;

static std::string current_user = "";

const std::string USERS_FILE_NAME = "users.txt";
const std::string LOGS_FILE_NAME = "logs.txt";

void create_account() {
	std::cout << "----------- Registration -----------" << std::endl;
	std::string username, password, gender, birthdate, activity_level, goal, account;

	std::cout << "Username: ";
	std::cin >> username;
	std::cout << "\nPassword: ";
	std::cin >> password;

	int age, height;

	std::cout << "----------- Personal Details -----------" << std::endl;
	std::cout << "Age: ";
	std::cin >> age;
	std::cout << "\nGender: ";
	std::cin >> gender;
	std::cout << "\nHeight: ";
	std::cin >> height;

}

void delete_account(std::string username, std::string password) {
	// Deleting account
}

void log_in(std::string username, std::string password) {
	// logs in existring user
}

void log_out() {
	// logs out currently logged in user
}

void start_guide() {
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Welcome to MyFitnessPal" << std::endl;
	std::cout << "-----------------------------------" << std::endl;

}

void load_information() {
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

	std::ifstream in_logs(LOGS_FILE_NAME);
	if (!in_logs) {
		std::ofstream logs(LOGS_FILE_NAME);
		logs.close();
	}
	else {
		std::string log_entry;
		while (std::getline(in_logs, log_entry)) {
			logs.push_back(log_entry);
		}
		in_logs.close();
	}
}

void run() {
	start_guide();
	load_information();

	for (size_t i = 0; i < usernames.size(); i++)
	{
		std::cout << usernames[i] << std::endl;
	}
}




int main()
{
	run();
}
