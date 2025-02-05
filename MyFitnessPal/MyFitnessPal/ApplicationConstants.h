/**
*
* Solution to course project # 9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* <application constants file>
*
*/

#pragma once
#include <string>

static const char UNIFIED_DELIMETER = '%';

static const std::string NUTRITION_TYPE = "Nutrition";
static const std::string EXERCISE_TYPE = "Exercise";
 
static const std::string USERS_FILE_NAME = "users.txt";
static const std::string LOGS_FILE_NAME = "logs.txt";
 
static const std::string GENDERS[] = { "male", "female" };
static const std::string PROFILE_INFORMATION[] = { "username", "password", "height", "weight", "activity_level", "goal", "rate", "account" };
static const std::string LOG_INFORMATION[] = { "name", "calories" };
 
static const std::string ACTIVITY_LEVELS_STRING[] = {
	"Sedentary (little to no exercise)",
	"Light activity (exercise 1-3 days per week)",
	"Moderate activity (exercise 3-5 days per week)",
	"Active (exercise 6-7 days per week)",
	"Very active (intense workouts or physical labor)"
};
static const std::string GOALS_STRING[] = {
	"Lose weight",
	"Maintain weight",
	"Gain weight"
};
static const std::string RATES_STRING[] = {
	"0.25 kg a week",
	"0.50 kg a week",
	"0.75 kg a week",
	"1 kg a week"
};
static const std::string ACCOUNTS_STRING[] = {
	"Standard",
	"Premium"
};
 
 //											 Proteins  Fat   Carbs
static const double LOSE_WEIGHT_RATIO[] =	   { 0.35, 0.30, 0.35 };
static const double MAINTAIN_WEIGHT_RATIO[] = { 0.25, 0.30, 0.45 };
static const double GAIN_WEIGHT_RATIO[] =     { 0.40, 0.25, 0.35 };
 
static double ACTIVITY_LEVELS[] = { 1.2, 1.375, 1.55, 1.725, 1.9 };
static const int MAX_ACTIVITY_LEVEL = 5;
 
static constexpr int TRANSFORMATION_RATES[] = { 275, 550, 825, 1110 };
static const int MAX_RATE = 4;