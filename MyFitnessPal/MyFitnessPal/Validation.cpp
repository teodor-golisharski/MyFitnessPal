#pragma once
#include <string>
#include "ApplicationConstants.h"

static std::vector<std::string> usernames;
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

namespace DataValidation {
	bool validate_username(std::string& username) {

		load_usernames();
		if (usernames.size() == 0) {
			return true;
		}
		if (username.find('%') != std::string::npos) {
			return false;
		}
		for (size_t i = 0; i < usernames.size(); i++)
		{
			if (usernames[i] == username) {
				return false;
			}
		}
		return true;
	}

	bool validate_password(std::string& password) {
		if (password.find('%') != std::string::npos) {
			return false;
		}
		return true;
	}

	bool is_valid_date(int year, int month, int day) {
		if (year < 1900 || year > 2024 || month < 1 || month > 12 || day < 1 || day > 31) {
			return false;
		}
		if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
			return false;
		}
		if (month == 2) {
			bool is_leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
			return day <= (is_leap ? 29 : 28);
		}
		return true;
	}
}

namespace InputIntegratedValidation {
	std::string get_birthday() {
		int year, month, day;
		while (true) {
			std::cout << "Enter birthday (YYYY-MM-DD): ";
			char delimiter;
			if (std::cin >> year >> delimiter >> month >> delimiter >> day && delimiter == '-' && DataValidation::is_valid_date(year, month, day)) {
				return std::to_string(year) + "-" + (month < 10 ? "0" : "") + std::to_string(month) + "-" +
					(day < 10 ? "0" : "") + std::to_string(day);
			}
			std::cout << INVALID_BIRTHDATE << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	int get_validated_input(const std::string& prompt, int min, int max) {
		int choice;
		while (true) {
			std::cout << prompt;
			std::cin >> choice;
			if (std::cin.fail() || choice < min || choice > max) {
				std::cerr << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else {
				return choice;
			}
		}
	}

	int get_activity_level() {
		std::cout << "-------------------------------------------------------\n";
		std::cout << "1 - Sedentary (little to no exercise)\n";
		std::cout << "2 - Light activity (exercise 1-3 days per week)\n";
		std::cout << "3 - Moderate activity (exercise 3-5 days per week)\n";
		std::cout << "4 - Active (exercise 6-7 days per week)\n";
		std::cout << "5 - Very active (intense workouts or physical labor)\n";
		std::cout << "#Guide: Type the number based on your activity.\n";
		std::cout << "-------------------------------------------------------\n";

		int activity_level = get_validated_input("Activity level: ", 1, MAX_ACTIVITY_LEVEL);
		return activity_level - 1;
	}

	int get_goal() {
		std::cout << "-------------------------------------------------------\n";
		std::cout << "1 - Lose weight\n";
		std::cout << "2 - Maintain weight\n";
		std::cout << "3 - Gain weight\n";
		std::cout << "#Guide: Type the number based on your goal.\n";
		std::cout << "-------------------------------------------------------\n";

		return get_validated_input("Goal: ", 1, 3);
	}

	int get_rate(int goal) {
		if (goal != 2) {
			std::cout << "-------------------------------------------------------\n";
			std::cout << "1 - 0.25 kg a week\n";
			std::cout << "2 - 0.50 kg a week\n";
			std::cout << "3 - 0.75 kg a week\n";
			std::cout << "4 - 1 kg a week\n";
			std::cout << "#Guide: Type the number based on your desired transformation rate.\n";
			std::cout << "-------------------------------------------------------\n";

			int rate_choice = get_validated_input("Rate: ", 1, MAX_RATE);
			int rate = TRANSFORMATION_RATES[rate_choice - 1];
			return (goal == 1) ? -rate : rate; 
		}
		return 0;
	}

	int get_account_type() {
		std::cout << "-------------------------------------------------------\n";
		std::cout << "----------------- CHOOSE ACCOUNT TYPE -----------------\n";
		std::cout << "1 - Standard\n";
		std::cout << "2 - Premium\n";
		std::cout << "-------------------------------------------------------\n";

		return get_validated_input("AccountType: ", 1, 2);
	}
}

