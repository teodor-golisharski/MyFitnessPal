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

bool validate_age(int age) {
	if (age >= 14 && age <= 100) {
		return true;
	}
	return false;
}

