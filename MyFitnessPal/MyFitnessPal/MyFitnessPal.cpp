/**
*
* Solution to course project # 9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* <main file>
*
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "DataHandler.cpp"
#include "DataLoader.h"
#include "OutputMessages.h"
#include "ApplicationConstants.h"

std::string current_user = "";
std::string current_password = "";
std::string current_birthday = "";

int current_gender = 0;
int current_age = 0;
int current_height = 0;
double current_weight = 0;
int current_activity_level = 0;
int current_goal = 0;
int current_rate = 0;
int current_account = 0;

int bmr = 0;
std::vector<std::string> logs;

bool save_user(const std::string& username, const std::string& password, const std::string& birthdate,
	int gender, int height, double weight,
	int activity_level, int goal, int rate, int account)
{
	std::ofstream file(USERS_FILE_NAME, std::ios::app);

	if (!file.is_open())
	{
		std::cerr << FILE_NOT_FOUND << std::endl;
		return false;
	}
	file << username << UNIFIED_DELIMETER << password << UNIFIED_DELIMETER << birthdate << UNIFIED_DELIMETER
		<< gender << UNIFIED_DELIMETER << height << UNIFIED_DELIMETER << weight << UNIFIED_DELIMETER
		<< activity_level << UNIFIED_DELIMETER << goal << UNIFIED_DELIMETER << rate << UNIFIED_DELIMETER << account << "\n";
	file.close();

	return true;
}
bool save_log(const std::string& username, const std::string& date, const std::string& name, int calories)
{
	std::ofstream file(LOGS_FILE_NAME, std::ios::app);

	if (!file.is_open())
	{
		std::cerr << FILE_NOT_FOUND << std::endl;
		return false;
	}
	file << username << UNIFIED_DELIMETER << date << UNIFIED_DELIMETER << name << UNIFIED_DELIMETER << calories << "\n";
	file.close();

	return true;
}
bool delete_log(const std::string& log)
{
	std::vector<std::string> active_logs;

	std::ifstream input_file(LOGS_FILE_NAME);
	if (!input_file)
	{
		std::cerr << FILE_NOT_FOUND << std::endl;
		return false;
	}

	std::string line;
	bool log_found = false;

	while (std::getline(input_file, line))
	{
		if (line == log)
		{
			log_found = true;
		}
		else
		{
			active_logs.push_back(line);
		}
	}
	input_file.close();
	std::ofstream temp_file(LOGS_FILE_NAME, std::ios::trunc);

	for (const std::string& cur_log : active_logs)
	{
		temp_file << cur_log << "\n";
	}
	temp_file.close();
	return true;
}
bool delete_daily_logs(const std::string& date)
{
	std::vector<std::string> active_logs;

	std::ifstream input_file(LOGS_FILE_NAME);
	if (!input_file)
	{
		std::cerr << FILE_NOT_FOUND << std::endl;
		return false;
	}

	std::string line;

	int count = 0;
	while (std::getline(input_file, line))
	{
		std::vector<std::string> splitted_line = DataUtility::split(line);
		std::string username = splitted_line[0];
		std::string log_date = splitted_line[1];

		if (username == current_user && log_date == date)
		{
			auto it = std::find(logs.begin(), logs.end(), line);
			if (it != logs.end())
			{
				logs.erase(it);
				count++;
			}
		}
		else
		{
			active_logs.push_back(line);
		}
	}
	input_file.close();
	if (count == 0)
	{
		std::cout << LOGS_EMPTY << date << "." << std::endl;
		return false;
	}

	std::ofstream temp_file(LOGS_FILE_NAME, std::ios::trunc);
	if (!temp_file)
	{
		std::cerr << FILE_NOT_FOUND << std::endl;
		return false;
	}

	for (const std::string& cur_log : active_logs)
	{
		temp_file << cur_log << "\n";
	}
	temp_file.close();

	std::cout << count << " logs on " << date << DELETED_LOGS << std::endl;
	return true;
}
bool delete_all_logs()
{
	int counter = 0;
	std::vector<std::string> active_logs;

	std::ifstream input_file(LOGS_FILE_NAME);
	if (!input_file)
	{
		std::cerr << FILE_NOT_FOUND << std::endl;
		return false;
	}

	std::string line;

	while (std::getline(input_file, line))
	{
		std::vector<std::string> splitted_line = DataUtility::split(line);
		std::string username = splitted_line[0];

		if (username == current_user)
		{
			counter++;
		}
		else
		{
			active_logs.push_back(line);
		}
	}
	input_file.close();

	if (counter == 0) return true;

	std::ofstream temp_file(LOGS_FILE_NAME, std::ios::trunc);
	if (!temp_file)
	{
		std::cerr << FILE_NOT_FOUND << std::endl;
		return false;
	}

	for (const std::string& cur_log : active_logs)
	{
		temp_file << cur_log << "\n";
	}
	temp_file.close();

	std::cout << counter << LOGS_DELETED << std::endl;
	return true;
}
bool log_in(const std::string& username, const std::string& password)
{
	std::ifstream file(USERS_FILE_NAME);

	if (!file.is_open())
	{
		std::cerr << FILE_NOT_FOUND << std::endl;
		return false;
	}

	std::string line;
	bool found = false;

	while (std::getline(file, line))
	{
		std::vector<std::string> line_info = DataUtility::split(line);
		std::string file_name = line_info[0];
		std::string file_password = line_info[1];

		if (file_name == username && file_password == password)
		{
			found = true;

			current_user = username;
			current_password = password;

			current_birthday = line_info[2];
			current_age = DataUtility::calculate_age(line_info[2]);

			current_gender = std::stoi(line_info[3]);
			current_height = std::stoi(line_info[4]);
			current_weight = std::stoi(line_info[5]);
			current_activity_level = std::stoi(line_info[6]);
			current_goal = std::stoi(line_info[7]);
			current_rate = std::stoi(line_info[8]);
			current_account = std::stoi(line_info[9]);

			bmr = DataUtility::calculate_bmr(current_gender, current_weight, current_height, current_age, current_activity_level);
			break;
		}
	}

	file.close();
	logs = load_logged_user_logs(current_user);

	if (found)
	{
		return true;
	}
	else
	{
		std::cerr << INVALID_USERNAME_OR_PASSWORD << std::endl;
		return false;
	}
}
void log_out()
{
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

	logs.clear();
}

void create_account()
{
	std::cout << "---------------------- REGISTRATION -----------------------" << std::endl;

	std::string username, password, birthdate;
	int height, gender, activity_level, goal = 0, rate = 0, account;
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

	if (save_user(username, password, birthdate, gender, height, weight, activity_level, goal, rate, account))
	{
		std::cout << ACCOUNT_CREATED_SUCCESSFULLY << username << "!" << std::endl;
		log_in(username, password);
	}
	else
	{
		std::cerr << SOMETHING_WENT_WRONG << std::endl;
	}
}
bool delete_account()
{
	std::vector<std::string> active_users;

	std::ifstream input_file(USERS_FILE_NAME);
	if (!input_file)
	{
		std::cerr << FILE_NOT_FOUND << std::endl;
		return false;
	}

	std::string line;
	bool user_found = false;

	while (std::getline(input_file, line))
	{
		size_t first_delim = line.find('%');
		size_t second_delim = line.find('%', first_delim + 1);

		std::string temp_username = line.substr(0, first_delim);
		std::string temp_password = line.substr(first_delim + 1, second_delim - first_delim - 1);

		if (temp_username == current_user && temp_password == current_password)
		{
			user_found = true;
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
	return true;
}
void view_profile()
{
	std::cout << "--------------------- ACCOUNT DETAILS ---------------------" << std::endl;
	std::cout << "Username: " << current_user << std::endl;
	std::cout << "Password: " << current_password << std::endl;
	std::cout << "-----------------------------------------------------------" << std::endl;
	std::cout << "Birthdate: " << current_birthday << std::endl;
	std::cout << "Gender: " << GENDERS[current_gender - 1] << std::endl;
	std::cout << "Height: " << current_height << "cm" <<std::endl;
	std::cout << "Weight: " << current_weight << "kg" << std::endl;
	std::cout << "-----------------------------------------------------------" << std::endl;
	std::cout << "Activity level: " << ACTIVITY_LEVELS_STRING[current_activity_level - 1] << std::endl;
	std::cout << "Goal: " << GOALS_STRING[current_goal - 1] << std::endl;
	if (current_goal != 2)
	{
		int index = 0;
		for (int i = 0; i < MAX_RATE; ++i)
		{
			if (current_rate == TRANSFORMATION_RATES[i])
			{
				index = i;
				break;
			}
		}
		std::cout << "Rate: " << RATES_STRING[index] << std::endl;
	}
	std::cout << "Account: " << ACCOUNTS_STRING[current_account - 1] << std::endl;
	std::cout << "-----------------------------------------------------------" << std::endl;
	DataUtility::calculate_recommendation(bmr, current_goal, current_rate, current_account);

}
void edit_profile()
{
	int option = InputIntegratedValidation::get_profile_info();

	std::string parameter = PROFILE_INFORMATION[option - 1];

	std::string target_user = current_user;
	std::string target_password = current_password;

	bool bmr_changed = false;
	bool changes_made = true;

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
		if (current_goal != 2)
		{
			current_rate = InputIntegratedValidation::get_rate(current_goal);
			bmr_changed = true;
		}
		else
		{
			std::cerr << RATE_CHANGE_UNAVAILABLE << std::endl;
			changes_made = false;
		}

	}
	else if (parameter == "account")
	{
		current_account = InputIntegratedValidation::get_account_type();
	}

	if (changes_made)
	{
		delete_account();
		save_user(target_user, target_password, current_birthday, current_gender, current_height, current_weight, current_activity_level, current_goal, current_rate, current_account);

		if (bmr_changed)
		{
			bmr = DataUtility::calculate_bmr(current_gender, current_weight, current_height, current_age, current_activity_level);
		}
		std::cout << PROFILE_SAVE_CHANGES << std::endl;
	}
	else
	{
		std::cerr << NO_CHANGES << std::endl;
	}
}

void get_logs_for_date(const std::string& date,
	std::vector<std::string>& user_friendly_logs,
	std::vector<std::string>& raw_logs)
{

	std::vector<std::string> user_friendly_exercises;
	std::vector<std::string> raw_exercises;


	for (const std::string& log : logs)
	{
		std::vector<std::string> log_line = DataUtility::split(log);
		std::string file_date = log_line[1];

		if (file_date == date)
		{
			std::string name = log_line[2];
			int calories = std::stoi(log_line[3]);

			std::string current_log;
			if (calories < 0)
			{
				calories *= -1;
				current_log = "You burnt " + std::to_string(calories) + " calories doing " + name + " on " + file_date + ".";
				user_friendly_exercises.push_back(current_log);
				raw_exercises.push_back(log);
			}
			else
			{
				current_log = "You consumed " + std::to_string(calories) + " calories from " + name + " on " + file_date + ".";
				user_friendly_logs.push_back(current_log);
				raw_logs.push_back(log);
			}
		}
	}
	user_friendly_logs.insert(user_friendly_logs.end(), user_friendly_exercises.begin(), user_friendly_exercises.end());
	raw_logs.insert(raw_logs.end(), raw_exercises.begin(), raw_exercises.end());
}
void add_log(const std::string& type)
{
	std::string input;
	int calories;

	if (type == NUTRITION_TYPE)
	{
		std::cout << "---------------------- Add Nutrition ----------------------" << std::endl;
	}
	else if (type == EXERCISE_TYPE)
	{
		std::cout << "---------------------- Add Exercise -----------------------" << std::endl;
	}

	input = InputIntegratedValidation::get_log_name(type);
	calories = InputIntegratedValidation::get_calories();
	if (type == EXERCISE_TYPE)
	{
		calories *= -1;
	}

	std::string date_now = InputIntegratedValidation::get_local_time();

	if (save_log(current_user, date_now, input, calories))
	{
		logs.push_back(current_user + UNIFIED_DELIMETER + date_now + UNIFIED_DELIMETER + input + UNIFIED_DELIMETER + std::to_string(calories));
		std::cout << LOG_SAVED << std::endl;
	}
	else
	{
		std::cout << SOMETHING_WENT_WRONG << std::endl;
	}
}
void view_log(const std::string& date)
{
	std::vector<std::string> user_friendly_logs;
	std::vector<std::string> raw_logs;

	get_logs_for_date(date, user_friendly_logs, raw_logs);

	if (!user_friendly_logs.empty())
	{
		std::cout << "------------------- Logs on " << date << " -------------------" << std::endl;
		int consumed = 0;
		int burnt = 0;

		for (size_t i = 0; i < user_friendly_logs.size(); i++)
		{
			int current_cals = std::stoi(DataUtility::split(raw_logs[i])[3]);
			if (current_cals < 0)
			{
				burnt += -current_cals;
			}
			else
			{
				consumed += current_cals;
			}

			std::cout << user_friendly_logs[i] << std::endl;
		}
		std::cout << "-----------------------------------------------------------" << std::endl;
		DataUtility::calculate_recommendation(bmr, current_goal, current_rate, current_account);
		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << "Consumed calories: " << consumed << " kcal" << std::endl;
		std::cout << "Burnt calories: " << burnt << " kcal" << std::endl;
		std::cout << "Current intake: " << consumed - burnt << " kcal" << std::endl;
		int recommended = bmr + current_rate;
		std::cout << "-----------------------------------------------------------" << std::endl;
		DataUtility::display_evaluation(current_goal, recommended, consumed, burnt);
		std::cout << "-----------------------------------------------------------" << std::endl;
	}
	else
	{
		std::cout << LOGS_EMPTY << date << "." << std::endl;
	}
}
void edit_log()
{
	std::vector<std::string> user_friendly_logs;
	std::vector<std::string> raw_logs;

	std::string date_now = InputIntegratedValidation::get_local_time();

	get_logs_for_date(date_now, user_friendly_logs, raw_logs);

	if (user_friendly_logs.empty())
	{
		std::cout << LOGS_EMPTY << date_now << "." << std::endl;
	}
	else
	{
		std::cout << "------------------------ Choose log -----------------------" << std::endl;
		for (size_t i = 0; i < user_friendly_logs.size(); i++)
		{
			std::cout << i + 1 << " - " << user_friendly_logs[i] << std::endl;
		}

		int choice = InputIntegratedValidation::get_validated_input("Option: ", 1, static_cast<int>(user_friendly_logs.size()));
		std::string& selected_log = raw_logs[choice - 1];

		std::vector<std::string> splitted_log = DataUtility::split(selected_log);
		std::string name = splitted_log[2];
		int calories = std::stoi(splitted_log[3]);
		std::string type = calories < 0 ? EXERCISE_TYPE : NUTRITION_TYPE;

		int option = InputIntegratedValidation::get_log_info();
		std::string parameter = LOG_INFORMATION[option - 1];

		if (parameter == "name")
		{
			name = InputIntegratedValidation::get_log_name(type);
		}
		else
		{
			calories = InputIntegratedValidation::get_calories();
			if (type == EXERCISE_TYPE)
			{
				calories *= -1;
			}
		}

		if (save_log(current_user, date_now, name, calories))
		{
			if (delete_log(selected_log))
			{
				logs.erase(std::find(logs.begin(), logs.end(), raw_logs[choice - 1]));
				logs.push_back(current_user + UNIFIED_DELIMETER + date_now + UNIFIED_DELIMETER + name + UNIFIED_DELIMETER + std::to_string(calories));
				std::cout << LOG_EDITED << std::endl;
			}
		}
		else
		{
			std::cout << SOMETHING_WENT_WRONG << std::endl;
		}
	}
}

void print_logo()
{
	std::cout << "-----------------------------------------------------------" << std::endl;
	std::cout << " __  __       _____ _ _                       ____       _ " << std::endl;
	std::cout << "|  \\/  |_   _|  ___(_) |_ _ __   ___  ___ ___|  _ \\ __ _| |" << std::endl;
	std::cout << "| |\\/| | | | | |_  | | __| '_ \\ / _ \\/ __/ __| |_) / _` | |" << std::endl;
	std::cout << "| |  | | |_| |  _| | | |_| | | |  __/\\__ \\__ \\  __/ (_| | |" << std::endl;
	std::cout << "|_|  |_|\\__, |_|   |_|\\__|_| |_|\\___||___/___/_|   \\__,_|_|" << std::endl;
	std::cout << "        |___/                                              " << std::endl;
	std::cout << "-----------------------------------------------------------" << std::endl;

}
void delay(int milliseconds)
{
	clock_t start_time = clock();
	while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}
void simulate_loading_bar()
{
	const int bar_width = 42;
	std::cout << "Loading: [";
	for (int i = 0; i < bar_width; ++i)
	{
		std::cout << "#";
		std::cout.flush();
		delay(25);
	}
	delay(200);
	std::cout << "] Done!" << std::endl;
}
void help_guide()
{

	std::cout << "-----------------------------------------------------------" << std::endl;
	std::cout << "------------------------ HELP MENU ------------------------" << std::endl;
	std::cout << "-----------------------------------------------------------" << std::endl;
	std::cout << "\nAvailable Commands:" << std::endl;
	std::cout << "-----------------------------------------------------------" << std::endl;
	std::cout << " + exit     |  Exit the application." << std::endl;
	std::cout << " + help     |  Display this help guide." << std::endl;
	if (current_user.empty())
	{
		std::cout << " + signup   |  Create a new account to start tracking" << std::endl;
		std::cout << "            |  your fitness journey." << std::endl;
		std::cout << " + login    |  Log in to your existing account to access" << std::endl;
		std::cout << "            |  personalized features." << std::endl;
		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << "Note: You need to log in or sign up to use more features." << std::endl;
		std::cout << "For questions, contact support at support@myfitnespal.com." << std::endl;
	}
	else
	{
		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << " + log_out           |  Log out of your profile." << std::endl;
		std::cout << " + edit_profile      |  Edit profile information." << std::endl;
		std::cout << " + view_profile      |  View profile information." << std::endl;
		std::cout << " + delete_account    |  Permanently delete your account and" << std::endl;
		std::cout << "                     |  all stored information." << std::endl;
		std::cout << " + add_nutrition     |  Add nutrition to your daily log." << std::endl;
		std::cout << " + add_exercise      |  Add exercise to your daily log." << std::endl;
		std::cout << " + daily_logs        |  View your daily logs." << std::endl;
		std::cout << " + view_logs         |  View your logs for a specific date." << std::endl;
		std::cout << " + edit_log          |  Edit one of your daily logs." << std::endl;
		std::cout << " + delete_logs       |  Erase all logs from a chosen date." << std::endl;
		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << "For questions, contact support at support@myfitnespal.com." << std::endl;
	}
	std::cout << "-----------------------------------------------------------" << std::endl;;
}
void start_guide()
{
	print_logo();

	simulate_loading_bar();
	std::cout << "\n----------------- Welcome to MyFitnessPal -----------------" << std::endl;
	std::cout << "-----------------------------------------------------------\n" << std::endl;

	help_guide();
}

void command_line()
{
	std::cout << "\nCommand: ";
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

				bool output = log_in(username_input, password_input);
				if (output)
				{
					std::cout << LOGIN_SUCCESSFUL << current_user << "!" << std::endl;
				}
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
				std::cout << LOGOUT_SUCCESSFUL << std::endl;
			}
			else if (input == "delete_account")
			{
				std::cout << ARE_YOU_SURE << std::endl;
				std::string answer;
				std::cin >> answer;
				if (answer == "yes")
				{
					if (delete_account())
					{
						std::cout << ACCOUNT_DELETED_SUCCESSFULLY << std::endl;
						delete_all_logs();
						log_out();
					}
					else {
						std::cerr << SOMETHING_WENT_WRONG << std::endl;
					}
				}
			}
			else if (input == "edit_profile")
			{
				edit_profile();
			}
			else if (input == "view_profile")
			{
				view_profile();
			}
			else if (input == "add_nutrition")
			{
				add_log(NUTRITION_TYPE);
			}
			else if (input == "add_exercise")
			{
				add_log(EXERCISE_TYPE);
			}
			else if (input == "daily_logs")
			{
				std::string date_now = InputIntegratedValidation::get_local_time();
				view_log(date_now);
			}
			else if (input == "view_logs")
			{
				std::string date_input = InputIntegratedValidation::get_log_date();
				view_log(date_input);
			}
			else if (input == "edit_log")
			{
				edit_log();
			}
			else if (input == "delete_logs")
			{
				std::string date_input = InputIntegratedValidation::get_log_date();
				delete_daily_logs(date_input);				
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

		std::cout << "\nCommand: ";
		std::cin >> input;
	}
}
void run()
{
	start_guide();
	load_usernames();
	command_line();
}

int main()
{
	run();
}
