#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "ErrorMessages.hpp"

static std::vector<std::string> usernames;
static std::vector<std::string> logs;

#include "Validation.hpp"

static double bmr = 0;
static int maintainCalories = 0;
static int additional = 0;

static std::string current_user = "";

const std::string USERS_FILE_NAME = "users.txt";
const std::string LOGS_FILE_NAME = "logs.txt";

void save_user(const std::string& username, const std::string& password, const std::string& birthdate,
	const std::string& gender, int height, double weight,
	int activity_level, int goal, int rate, int account) {
	std::ofstream file(USERS_FILE_NAME, std::ios::app);

	if (!file.is_open()) {
		std::cerr << FILE_NOT_FOUND << std::endl;
		return;
	}
	file << "\n" << username << "%" << password << "%" << birthdate << "%"
		<< gender << "%" << height << "%" << weight << "%"
		<< activity_level << "%" << goal << "%" << rate << "%" << account << "\n";
	file.close();
	std::cout << ACCOUNT_CREATED_SUCCESSFULLY << username << "!" << std::endl;
}

bool create_account() {
	std::cout << "----------- Registration -----------" << std::endl;

	std::string username, password, gender, birthdate;
	int age, height, activity_level, goal = 0, rate = 0, account;
	double weight;

	while (true) {
		std::cout << "Username: ";
		std::cin >> username;
		if (validate_username(username)) break;
		std::cerr << INVALID_USERNAME << std::endl;
	}

	while (true) {
		std::cout << "Password: ";
		std::cin >> password;
		if (validate_password(password)) break;
		std::cerr << INVALID_PASSWORD << std::endl;
	}

	std::cout << "----------- Personal Details -----------" << std::endl;
	birthdate = get_birthday();

	while (true) {
		std::cout << "Gender (male/female): ";
		std::cin >> gender;
		if (gender == "male" || gender == "female") break;
		std::cerr << INVALID_GENDER << std::endl;
	}
	
	std::cout << "Height (in cm): ";
	std::cin >> height;

	std::cout << "Weight (in kg): ";
	std::cin >> weight;

	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "1 - Sedentary (little to no exercise)" << std::endl;
	std::cout << "2 - Light activity (exercise 1-3 days per week)" << std::endl;
	std::cout << "3 - Moderate activity (exercise 3-5 days per week)" << std::endl;
	std::cout << "4 - Active (exercise 6-7 days per week)" << std::endl;
	std::cout << "5 - Very active (intense workouts or physical labor)" << std::endl;
	std::cout << "#Guide: Type the number based on your activity." << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "Activity level: ";
	std::cin >> activity_level;

	switch (activity_level) {
	case 1: bmr = 1.2; break;
	case 2: bmr = 1.375; break;
	case 3: bmr = 1.55; break;
	case 4: bmr = 1.725; break;
	case 5: bmr = 1.9; break;
	default: { 
		std::cerr << INVALID_ACTIVITY_LEVEL << std::endl; 
		return false; 
		}
	}

	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "1 - Lose weight" << std::endl;
	std::cout << "2 - Maintain weight" << std::endl;
	std::cout << "3 - Gain weight" << std::endl;
	std::cout << "#Guide: Type the number based on your goal." << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "Goal: ";
	std::cin >> goal;
	if (goal != 2) {
		std::cout << "-------------------------------------------------------" << std::endl;
		std::cout << "1 - 0.25 kg a week" << std::endl;
		std::cout << "2 - 0.50 kg a week" << std::endl;
		std::cout << "3 - 0.75 kg a week" << std::endl;
		std::cout << "4 - 1 kg a week" << std::endl;
		std::cout << "#Guide: Type the number based on your desired transformation rate." << std::endl;
		std::cout << "-------------------------------------------------------" << std::endl;
		std::cout << "Rate: ";
		std::cin >> rate;

		rate = rate == 1 ? 275 : rate == 2 ? 550 : rate == 3 ? 825 : 1110;
		if (goal == 1) {
			rate = 0 - rate;
		}
	}
	additional += rate;

	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "----------------- CHOOSE ACCOUNT TYPE -----------------" << std::endl;
	std::cout << "1 - Standard" << std::endl;
	std::cout << "2 - Premium" << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "AccountType: ";
	std::cin >> account;


	save_user(username, password, birthdate, gender, height, weight, activity_level, goal, rate, account);
}

void delete_account(std::string username, std::string password) {
	// Deleting account
}

void log_in(std::string username, std::string password) {
	// logs in existing user
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
void read_information() {

}
void command_line() {

	std::string input;
	std::cin >> input;


}

void run() {
	start_guide();
	load_information();

}


int main()
{
	std::cout << "\n-------------------------------------------------------" << std::endl;
	//run();
	load_information();
	create_account();
}
