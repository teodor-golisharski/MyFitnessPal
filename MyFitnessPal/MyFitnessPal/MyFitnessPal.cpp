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

void create_account() {
	std::cout << "----------- Registration -----------" << std::endl;
	std::string username, password, birthdate, activity_level, goal, account;

	std::cout << "Username: ";
	std::cin >> username;
	std::cout << "\nPassword: ";
	std::cin >> password;
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

	std::ifstream users(USERS_FILE_NAME);
	
}

static std::vector<std::string> usernames;
static std::string current_user = "";

const std::string USERS_FILE_NAME = "users.txt";
const std::string LOGS_FILE_NAME = "logs.txt";


int main()
{
	start_guide();

	std::cout << "Hello World!\n";
}
