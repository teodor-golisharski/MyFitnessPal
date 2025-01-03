#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "ErrorMessages.hpp"
#include "Validation.cpp"

static double bmr = 0;
static int maintainCalories = 0;
static int additional = 0;

static std::string current_user = "";

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

void delete_user(const std::string& target) {

}

void create_account() {
	std::cout << "---------------------- REGISTRATION -----------------------" << std::endl;

	std::string username, password, gender, birthdate;
	int age, height, activity_level, goal = 0, rate = 0, account;
	double weight;

	while (true) {
		std::cout << "Username: ";
		std::cin >> username;
		if (DataValidation::validate_username(username)) break;
		std::cerr << INVALID_USERNAME << std::endl;
	}

	while (true) {
		std::cout << "Password: ";
		std::cin >> password;
		if (DataValidation::validate_password(password)) break;
		std::cerr << INVALID_PASSWORD << std::endl;
	}

	std::cout << "-------------------- PERSONAL DETAILS ---------------------" << std::endl;
	birthdate = InputIntegratedValidation::get_birthday();

	while (true) {
		std::cout << "Gender (male/female): ";
		std::cin >> gender;
		if (gender == "male" || gender == "female") break;
		std::cerr << INVALID_GENDER << std::endl;
	}

	std::cout << "Height (in cm): ";
	while (!(std::cin >> height) || height <= 0) {
		std::cerr << INVALID_HEIGHT;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::cout << "Weight (in kg): ";
	while (!(std::cin >> weight) || weight <= 0) {
		std::cerr << INVALID_WEIGHT;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	activity_level = InputIntegratedValidation::get_activity_level();
	goal = InputIntegratedValidation::get_goal();
	rate = InputIntegratedValidation::get_rate(goal);
	account = InputIntegratedValidation::get_account_type();

	save_user(username, password, birthdate, gender, height, weight, activity_level, goal, rate, account);
}

void delete_account(std::string username, std::string password) {
	// Deleting account
}

void log_in(std::string username, std::string password) {
	bool username_exists_status = !DataValidation::username_exists(username);
}

void log_out() {
	// logs out currently logged in user
}


void print_logo() {
	std::cout << "-----------------------------------------------------------" << std::endl;
	std::cout << " __  __       _____ _ _                       ____       _ " << std::endl;
	std::cout << "|  \\/  |_   _|  ___(_) |_ _ __   ___  ___ ___|  _ \\ __ _| |" << std::endl;
	std::cout << "| |\\/| | | | | |_  | | __| '_ \\ / _ \\/ __/ __| |_) / _` | |" << std::endl;
	std::cout << "| |  | | |_| |  _| | | |_| | | |  __/\\__ \\__ \\  __/ (_| | |" << std::endl;
	std::cout << "|_|  |_|\\__, |_|   |_|\\__|_| |_|\\___||___/___/_|   \\__,_|_|" << std::endl;
	std::cout << "        |___/                                              " << std::endl;
	std::cout << "-----------------------------------------------------------" << std::endl;

}

void delay(int milliseconds) {
	clock_t start_time = clock();
	while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}
void simulate_loading_bar() {
	const int bar_width = 42;
	std::cout << "Loading: [";
	for (int i = 0; i < bar_width; ++i) {
		std::cout << "#";
		std::cout.flush();
		delay(25);
	}
	delay(250);
	std::cout << "] Done!" << std::endl;
}
void start_guide() {
	print_logo();

	simulate_loading_bar();
	std::cout << "\n----------------- Welcome to MyFitnessPal -----------------" << std::endl;
	std::cout << "-----------------------------------------------------------" << std::endl;

}

void command_line() {

	std::string input;
	std::cin >> input;
	while (true)
	{
		if (input == "exit") {

		}
		if (current_user.empty()) {
			if (input == "register") {
				create_account();
			}
			else if (input == "login") {

			}
			else {
				std::cerr << INVALID_COMMAND << std::endl;
			}
		}
	}

}

void run() {
	start_guide();

}


int main()
{

	run();
	//create_account();
}
