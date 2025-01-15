#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "OutputMessages.h"
#include "DataValidation.cpp"

std::string current_user = "";
std::string current_password = "";
std::string current_birthday = "";

int current_gender = 0;
int current_age = 0;
int current_height = 0;
int current_weight = 0;
int current_activity_level = 0;
int current_goal = 0;
int current_rate = 0;
int current_account = 0;

int bmr = 0;

void save_user(const std::string& username, const std::string& password, const std::string& birthdate,
	int gender, int height, double weight,
	int activity_level, int goal, int rate, int account) {
	std::ofstream file(USERS_FILE_NAME, std::ios::app);

	if (!file.is_open())
	{
		std::cerr << FILE_NOT_FOUND << std::endl;
		return;
	}
	file << username << "%" << password << "%" << birthdate << "%"
		<< gender << "%" << height << "%" << weight << "%"
		<< activity_level << "%" << goal << "%" << rate << "%" << account << "\n";
	file.close();
}

void create_account() {
	std::cout << "---------------------- REGISTRATION -----------------------" << std::endl;

	std::string username, password, birthdate;
	int age, height, gender, activity_level, goal = 0, rate = 0, account;
	double weight;

	username = InputIntegratedValidation::get_username();
	password = InputIntegratedValidation::get_password();

	std::cout << "-------------------- PERSONAL DETAILS ---------------------" << std::endl;
	birthdate = InputIntegratedValidation::get_birthday();
	gender = InputIntegratedValidation::get_gender();
	height = InputIntegratedValidation::get_height();
	weight = InputIntegratedValidation::get_weight();
	activity_level = InputIntegratedValidation::get_activity_level();
	goal = InputIntegratedValidation::get_goal();
	rate = InputIntegratedValidation::get_rate(goal);
	account = InputIntegratedValidation::get_account_type();

	save_user(username, password, birthdate, gender, height, weight, activity_level, goal, rate, account);
	std::cout << ACCOUNT_CREATED_SUCCESSFULLY << username << "!" << std::endl;
}

void delete_account() {
	std::vector<std::string> active_users;

	std::ifstream input_file(USERS_FILE_NAME);
	if (!input_file)
	{
		std::cerr << "Error: Could not open file.\n";
		return;
	}

	std::string line;
	bool userFound = false;

	while (std::getline(input_file, line))
	{
		size_t first_delim = line.find('%');
		size_t second_delim = line.find('%', first_delim + 1);

		std::string temp_username = line.substr(0, first_delim);
		std::string temp_password = line.substr(first_delim + 1, second_delim - first_delim - 1);

		if (temp_username == current_user && temp_password == current_password)
		{
			userFound = true;
		}
		else
		{
			active_users.push_back(line);
		}
	}

	input_file.close();
	std::ofstream temp_file(USERS_FILE_NAME, std::ios::trunc);

	for (const std::string& cur_user : active_users)
	{
		temp_file << cur_user << "\n";
	}

	temp_file.close();
}

void edit_profile() {
	int option = InputIntegratedValidation::get_profile_info();

	std::string parameter = PROFILE_INFORMATION[option - 1];

	std::string target_user = current_user;
	std::string target_password = current_password;

	bool bmr_changed = false;

	if (parameter == "username")
	{
		target_user = InputIntegratedValidation::get_username();
	}
	else if (parameter == "password")
	{
		target_password = InputIntegratedValidation::get_password();
	}
	else if (parameter == "height")
	{
		current_height = InputIntegratedValidation::get_height();
		bmr_changed = true;
	}
	else if (parameter == "weight")
	{
		current_weight = InputIntegratedValidation::get_weight();
		bmr_changed = true;
	}
	else if (parameter == "activity_level")
	{
		current_activity_level = InputIntegratedValidation::get_activity_level();
		bmr_changed = true;
	}
	else if (parameter == "goal")
	{
		current_goal = InputIntegratedValidation::get_goal();
		current_rate = InputIntegratedValidation::get_rate(current_goal);
		bmr_changed = true;
	}
	else if (parameter == "rate")
	{
		current_rate = InputIntegratedValidation::get_rate(current_goal);
		bmr_changed = true;
	}
	else if (parameter == "account")
	{
		current_account = InputIntegratedValidation::get_account_type();
	}

	delete_account();
	save_user(target_user, target_password, current_birthday, current_gender, current_height, current_weight, current_activity_level, current_goal, current_rate, current_account);
	
	if (bmr_changed)
	{
		bmr = DataOperations::calculate_bmr(current_gender, current_weight, current_height, current_age, current_activity_level);
	}

	std::cout << PROFILE_SAVE_CHANGES << std::endl;
}

void log_in(std::string username, std::string password) {
	std::ifstream file(USERS_FILE_NAME);

	if (!file.is_open())
	{
		std::cerr << FILE_NOT_FOUND << std::endl;
		return;
	}

	std::string line;
	bool found = false;

	while (std::getline(file, line))
	{
		size_t pos_username = line.find('%');
		if (pos_username == std::string::npos)
		{
			continue;
		}

		std::string file_username = line.substr(0, pos_username);

		size_t pos_password = line.find('%', pos_username + 1);
		if (pos_password == std::string::npos)
		{
			continue;
		}
		std::string file_password = line.substr(pos_username + 1, pos_password - pos_username - 1);

		if (file_username == username && file_password == password)
		{
			found = true;

			current_user = username;
			current_password = password;

			size_t start = pos_password + 1;
			size_t end = line.find('%', start);
			current_birthday = line.substr(start, end - start);
			current_age = DataOperations::calculate_age(current_birthday);

			start = end + 1;
			end = line.find('%', start);
			current_gender = std::stoi(line.substr(start, end - start));

			start = end + 1;
			end = line.find('%', start);
			current_height = std::stoi(line.substr(start, end - start));

			start = end + 1;
			end = line.find('%', start);
			current_weight = std::stoi(line.substr(start, end - start));

			start = end + 1;
			end = line.find('%', start);
			current_activity_level = std::stoi(line.substr(start, end - start));

			start = end + 1;
			end = line.find('%', start);
			current_goal = std::stoi(line.substr(start, end - start));

			start = end + 1;
			end = line.find('%', start);
			current_rate = std::stoi(line.substr(start, end - start));

			start = end + 1;
			current_account = std::stoi(line.substr(start));

			bmr = DataOperations::calculate_bmr(current_gender, current_weight, current_height, current_age, current_activity_level);
			break;
		}
	}

	file.close();

	if (found)
	{
		std::cout << LOGIN_SUCCESSFUL << username << "!" << std::endl;
	}
	else
	{
		std::cerr << INVALID_USERNAME_OR_PASSWORD << std::endl;
	}
}

void log_out() {
	current_user = "";
	current_password = "";
	current_birthday = "";

	current_gender = 0;
	current_age = 0;
	current_height = 0;
	current_weight = 0;
	current_activity_level = 0;
	current_goal = 0;
	current_rate = 0;
	current_account = 0;
	bmr = 0;

	std::cout << LOGOUT_SUCCESSFUL << std::endl;
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
	for (int i = 0; i < bar_width; ++i)
	{
		std::cout << "#";
		std::cout.flush();
		delay(25);
	}
	delay(250);
	std::cout << "] Done!" << std::endl;
}
void help_guide() {

	std::cout << "-----------------------------------------------------------" << std::endl;
	std::cout << "------------------------ HELP MENU ------------------------" << std::endl;
	std::cout << "-----------------------------------------------------------" << std::endl;
	std::cout << "\nAvailable Commands:" << std::endl;
	std::cout << " + exit     |  Exit the application." << std::endl;
	std::cout << " + help     |  Display this help guide." << std::endl;
	if (current_user.empty())
	{
		std::cout << " + signup   |  Create a new account to start tracking" << std::endl;
		std::cout << "            |  your fitness journey." << std::endl;
		std::cout << " + login    |  Log in to your existing account to access" << std::endl;
		std::cout << "            |  personalized features." << std::endl;
		std::cout << "\n-----------------------------------------------------------" << std::endl;
		std::cout << "Note: You need to log in or sign up to use more features." << std::endl;
		std::cout << "For questions, contact support at support@myfitnespal.com." << std::endl;
	}
	else
	{
		std::cout << " + log_out           |  Log out of your profile." << std::endl;
		std::cout << " + edit_profile      |  Edit profile information." << std::endl;
		std::cout << " + delete_account    |  Permanently delete your account and" << std::endl;
		std::cout << "                     |  all stored information." << std::endl;
		std::cout << " + add_nutrition     |  Add nutrition to your daily log." << std::endl;
		// more functionality here 
		std::cout << "\n-----------------------------------------------------------" << std::endl;
		std::cout << "For questions, contact support at support@myfitnespal.com." << std::endl;
	}
	std::cout << "-----------------------------------------------------------" << std::endl;;
	std::cout << "" << std::endl;
}
void start_guide() {
	print_logo();

	simulate_loading_bar();
	std::cout << "\n----------------- Welcome to MyFitnessPal -----------------" << std::endl;
	std::cout << "-----------------------------------------------------------\n" << std::endl;

	help_guide();
}

void command_line() {
	std::cout << "Command: ";
	std::string input;
	std::cin >> input;
	while (true)
	{
		if (input == "exit")
		{
			std::cout << "Exiting";
			for (int i = 0; i < 3; ++i)
			{
				std::cout << ".";
				std::cout.flush();
				delay(25);
			}
			return;
		}
		else if (input == "help")
		{
			help_guide();
		}
		else if (current_user.empty())
		{
			if (input == "signup")
			{
				create_account();
			}
			else if (input == "login")
			{
				std::string username_input, password_input;
				std::cout << "Username: ";
				std::cin >> username_input;
				std::cout << "Password: ";
				std::cin >> password_input;

				log_in(username_input, password_input);
			}
			else
			{
				std::cerr << INVALID_COMMAND << std::endl;
			}
		}
		else if (!current_user.empty())
		{
			if (input == "log_out")
			{
				log_out();
			}
			else if (input == "delete_account")
			{
				delete_account();
				std::cout << ACCOUNT_DELETED_SUCCESSFULLY << std::endl;
			}
			else if (input == "edit_profile")
			{
				edit_profile();
			}
			else if (input == "add_nutrition")
			{

			}
			else if (input == "add_exercise")
			{

			}
			else
			{
				std::cerr << INVALID_COMMAND << std::endl;
			}

		}
		else
		{
			std::cerr << INVALID_COMMAND << std::endl;
		}

		std::cout << "Command: ";
		std::cin >> input;
	}

}

void run() {
	//start_guide();
	help_guide(); // temp
	command_line();
}


int main()
{
	run();
}
