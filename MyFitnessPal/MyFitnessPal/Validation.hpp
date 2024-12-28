#pragma once

bool validate_username(std::string username) {
	for (size_t i = 0; i < usernames.size(); i++)
	{
		if (usernames[i] == username) {
			return true;
		}
	}
	return false;
}

bool validate_password(std::string password) {
	if (password.find('%')) {
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