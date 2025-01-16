#pragma once
#include <string>

// Data errors
const std::string INVALID_USERNAME = "Username has been taken! Try another one.";
const std::string INVALID_PASSWORD = "Invalid password. Please ensure it meets the requirements.";
const std::string INVALID_USERNAME_OR_PASSWORD = "Invalid username or password!";
const std::string INVALID_AGE = "You must be at least 14 years old to create an account.";
const std::string INVALID_BIRTHDATE = "Invalid date. Please enter a valid birthday (YYYY-MM-DD).";
const std::string INVALID_ACTIVITY_LEVEL = "Invalid activity level. Please enter a number in the range.";
const std::string INVALID_GENDER = "Invalid gender. Please enter a correct one.";
const std::string INVALID_WEIGHT = "Invalid weight. Please enter a valid positive number: ";
const std::string INVALID_HEIGHT = "Invalid height. Please enter a valid positive number: ";
const std::string RATE_CHANGE_UNAVAILABLE = "Rate change is unavailable. Please update your goal first.";

const std::string INVALID_FOOD_NAME = "Food name cannot contain '%'. Try again.";
const std::string INVALID_EXERCISE_NAME = "Exercise name cannot contain '%'. Try again.";
const std::string INVALID_CALORIES = "Invalid calories. Please enter a positive number: ";
const std::string INVALID_LOG_DATE = "Invalid log date format.";

// General errors
const std::string FILE_NOT_FOUND = "Error! File was not found.";
const std::string INVALID_COMMAND = "Command not recognized! Type help for additional guidance.";
const std::string LOCALTIME_ERROR = "Error retrieving local time.";
const std::string SOMETHING_WENT_WRONG = "Something went wrong. Try again or contact support.";
const std::string NO_CHANGES = "No changes were made due to an error.";

// Success messages
const std::string ACCOUNT_CREATED_SUCCESSFULLY = "Account created successfully! Welcome to MyFitnessPal, ";
const std::string LOGIN_SUCCESSFUL = "Login successful! Welcome, ";
const std::string LOGOUT_SUCCESSFUL = "You have successfully logged out.";
const std::string ACCOUNT_DELETED_SUCCESSFULLY = "Account deleted successfully! Goodbye! :(";
const std::string PROFILE_SAVE_CHANGES = "Changes have been saved.";
const std::string LOG_SAVED = "Your log has been successfully saved!";

// Output messages
const std::string NUTRITIONS_EMPTY = "No nutrition logs found on ";
const std::string EXERCISES_EMPTY = "No exercise logs found on ";