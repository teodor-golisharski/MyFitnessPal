#pragma once
#include<string>
#include<vector>

namespace DataValidation
{
	bool username_exists(const std::string& username);
	bool validate_string(const std::string& input);
	bool validate_username(const std::string& username);
	bool is_valid_date(int year, int month, int day);
}

namespace DataUtility
{
	int calculate_age(const std::string& birthdate);
	int calculate_bmr(int gender, double weight, int height, int age, int activity_level);
	void calculate_recommendation(int bmr, int current_goal, int current_rate, int current_account);
	void display_evaluation(int current_goal, int recommended, int consumed, int burnt);
	std::vector<std::string> split(const std::string& str);
}

namespace InputIntegratedValidation
{
	std::string get_username();
	std::string get_password();
	int get_height();
	double get_weight();
	std::string get_local_time();
	std::string get_birthday();
	std::string get_log_date();
	int get_validated_input(const std::string& prompt, int min, int max);
	int get_gender();
	int get_activity_level();
	int get_goal();
	int get_rate(int goal);
	int get_account_type();
	int get_profile_info();
	int get_log_info();
	std::string get_log_name(const std::string& type);
	int get_calories();
}