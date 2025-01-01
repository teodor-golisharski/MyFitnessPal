#pragma once

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

std::string get_birthday() {
	int year, month, day;
	while (true) {
		std::cout << "Enter birthday (YYYY-MM-DD): ";
		char delimiter;
		if (std::cin >> year >> delimiter >> month >> delimiter >> day && delimiter == '-' && is_valid_date(year, month, day)) {
			return std::to_string(year) + "-" + (month < 10 ? "0" : "") + std::to_string(month) + "-" +
				(day < 10 ? "0" : "") + std::to_string(day);
		}
		std::cout << INVALID_BIRTHDATE << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}
