#pragma once
#include <string>

const std::string NUTRITION_TYPE = "Nutrition";
const std::string EXERCISE_TYPE = "Exercise";

const std::string USERS_FILE_NAME = "users.txt";
const std::string LOGS_FILE_NAME = "logs.txt";

const std::string GENDERS[] = { "male", "female" };
const std::string PROFILE_INFORMATION[] = { "username", "password", "height", "weight", "activity_level", "goal", "rate", "account" };

const std::string ACTIVITY_LEVELS_STRING[] = {
	"Sedentary (little to no exercise)",
	"Light activity (exercise 1-3 days per week)",
	"Moderate activity (exercise 3-5 days per week)",
	"Active (exercise 6-7 days per week)",
	"Very active (intense workouts or physical labor)"
};
const std::string GOALS_STRING[] = {
	"Lose weight",
	"Maintain weight",
	"Gain weight"
};
const std::string RATES_STRING[] = {
	"0.25 kg a week",
	"0.50 kg a week",
	"0.75 kg a week",
	"1 kg a week"
};
const std::string ACCOUNTS_STRING[] = {
	"Standard",
	"Premium"
};

const double ACTIVITY_LEVELS[] = { 1.2, 1.375, 1.55, 1.725, 1.9 };
const int MAX_ACTIVITY_LEVEL = 5;

constexpr int TRANSFORMATION_RATES[] = { 275, 550, 825, 1110 };
const int MAX_RATE = 4;
