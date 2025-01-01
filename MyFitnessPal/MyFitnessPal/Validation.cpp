#pragma once
#include <string>

static std::vector<std::string> usernames;
static std::vector<std::string> logs;

const double ACTIVITY_LEVELS[] = { 1.2, 1.375, 1.55, 1.725, 1.9 };
const int MAX_ACTIVITY_LEVEL = 5;

const int TRANSFORMATION_RATES[] = { 275, 550, 825, 1110 };
const int MAX_RATE = 4;


namespace DataValidation {
	bool validate_username(std::string& username) {
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

	double getActivityLevel() {
		std::cout << "-------------------------------------------------------\n";
		std::cout << "1 - Sedentary (little to no exercise)\n";
		std::cout << "2 - Light activity (exercise 1-3 days per week)\n";
		std::cout << "3 - Moderate activity (exercise 3-5 days per week)\n";
		std::cout << "4 - Active (exercise 6-7 days per week)\n";
		std::cout << "5 - Very active (intense workouts or physical labor)\n";
		std::cout << "#Guide: Type the number based on your activity.\n";
		std::cout << "-------------------------------------------------------\n";

		int activity_level = get_validated_input("Activity level: ", 1, MAX_ACTIVITY_LEVEL);
		return ACTIVITY_LEVELS[activity_level - 1];
	}
}


