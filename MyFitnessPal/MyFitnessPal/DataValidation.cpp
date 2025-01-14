#include <string>
#include "ApplicationConstants.h"
#include "DataLoader.h"

namespace DataValidation {

	bool username_exists(const std::string& username) {
		for (const auto& stored_username : usernames)
		{
			if (stored_username == username) {
				return true;
			}
		}
		return false;
	}

	bool validate_username(std::string& username) {

		load_usernames();
		if (usernames.empty()) {
			return true;
		}
		if (username.find('%') != std::string::npos) {
			return false;
		}
		if (username_exists(username)) {
			return false;
		}
		return true;
	}

	bool validate_password(const std::string& password) {
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
	std::string get_username() {

		std::string username;
		while (true) {
			std::cout << "Username: ";
			std::cin >> username;
			if (DataValidation::validate_username(username)) break;
			std::cerr << INVALID_USERNAME << std::endl;
		}
		return username;
	}
	std::string get_password() {

		std::string password;
		while (true) {
			std::cout << "Password: ";
			std::cin >> password;
			if (DataValidation::validate_password(password)) break;
			std::cerr << INVALID_PASSWORD << std::endl;
		}
		return password;
	}
	int get_height() {
		int height;
		std::cout << "Height (in cm): ";
		while (!(std::cin >> height) || height <= 0) {
			std::cerr << INVALID_HEIGHT;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		return height;
	}
	double get_weight() {
		double weight;

		std::cout << "Weight (in kg): ";
		while (!(std::cin >> weight) || weight <= 0) {
			std::cerr << INVALID_WEIGHT;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		return weight;
	}

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
	int get_gender() {
		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << "1 - Male" << std::endl;
		std::cout << "2 - Female" << std::endl;
		std::cout << "#Guide: Type the corresponding number." << std::endl;
		std::cout << "-----------------------------------------------------------" << std::endl;

		return get_validated_input("Gender: ", 1, 2);
	}

	int get_activity_level() {
		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << "1 - Sedentary (little to no exercise)" << std::endl;
		std::cout << "2 - Light activity (exercise 1-3 days per week)" << std::endl;
		std::cout << "3 - Moderate activity (exercise 3-5 days per week)" << std::endl;
		std::cout << "4 - Active (exercise 6-7 days per week)" << std::endl;
		std::cout << "5 - Very active (intense workouts or physical labor)" << std::endl;
		std::cout << "#Guide: Type the number corresponding to your activity." << std::endl;
		std::cout << "-----------------------------------------------------------" << std::endl;

		return get_validated_input("Activity level: ", 1, MAX_ACTIVITY_LEVEL);
	}
	int get_goal() {
		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << "1 - Lose weight" << std::endl;
		std::cout << "2 - Maintain weight" << std::endl;
		std::cout << "3 - Gain weight" << std::endl;
		std::cout << "#Guide: Type the number corresponding to your goal." << std::endl;
		std::cout << "-----------------------------------------------------------" << std::endl;

		return get_validated_input("Goal: ", 1, 3);
	}
	int get_rate(int goal) {
		if (goal != 2) {
			std::cout << "-----------------------------------------------------------" << std::endl;
			std::cout << "1 - 0.25 kg a week" << std::endl;
			std::cout << "2 - 0.50 kg a week" << std::endl;
			std::cout << "3 - 0.75 kg a week" << std::endl;
			std::cout << "4 - 1 kg a week" << std::endl;
			std::cout << "#Guide: Type the number corresponding to your desired \ntransformation rate." << std::endl;
			std::cout << "-----------------------------------------------------------" << std::endl;

			int rate_choice = get_validated_input("Rate: ", 1, MAX_RATE);
			int rate = TRANSFORMATION_RATES[rate_choice - 1];
			return (goal == 1) ? -rate : rate;
		}
		return 0;
	}
	int get_account_type() {
		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << "------------------- CHOOSE ACCOUNT TYPE -------------------" << std::endl;
		std::cout << "1 - Standard" << std::endl;
		std::cout << "2 - Premium" << std::endl;
		std::cout << "-----------------------------------------------------------" << std::endl;

		return get_validated_input("AccountType: ", 1, 2);
	}

	int get_profile_info() {
		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << "1 - Username" << std::endl;
		std::cout << "2 - Password" << std::endl;
		std::cout << "3 - Height" << std::endl;
		std::cout << "4 - Weight" << std::endl;
		std::cout << "5 - Activity level" << std::endl;
		std::cout << "6 - Goal" << std::endl;
		std::cout << "7 - Transformation rate" << std::endl;
		std::cout << "8 - Account type" << std::endl;
		std::cout << "#Guide: Enter the number of the parameter you want to edit." << std::endl;
		std::cout << "-----------------------------------------------------------" << std::endl;

		return get_validated_input("Option: ", 1, 8);
	}
}

namespace DataOperations {

	int calculate_age(const std::string& birthdate) {
		int year, month, day;
		sscanf_s(birthdate.c_str(), "%d-%d-%d", &year, &month, &day);

		time_t t = time(0);
		tm now;
		localtime_s(&now, &t);
		int age = now.tm_year + 1900 - year;
		if (now.tm_mon + 1 < month || (now.tm_mon + 1 == month && now.tm_mday < day)) {
			--age;
		}

		return age;
	}

	int calculate_bmr(int gender, double weight, int height, int age, int activity_level) {

		double weight_index = gender == 1 ? 13.397 : 9.247;
		double height_index = gender == 1 ? 4.799 : 3.098;
		double age_index = gender == 1 ? 5.677 : 4.330;

		double bmr = gender == 1 ? 88.362 : 447.593;
		bmr += weight_index * weight + height_index * height - age_index * age;
		bmr *= ACTIVITY_LEVELS[activity_level];

		return (int)bmr;
	}
}


