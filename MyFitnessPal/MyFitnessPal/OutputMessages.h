#pragma once
#include <string>

// Data errors
static const std::string INVALID_USERNAME = "Username has been taken! Try another one.";
static const std::string INVALID_PASSWORD = "Invalid password. Please ensure it meets the requirements.";
static const std::string INVALID_USERNAME_OR_PASSWORD = "Invalid username or password!";
static const std::string INVALID_AGE = "You must be at least 14 years old to create an account.";
static const std::string INVALID_BIRTHDATE = "Invalid date. Please enter a valid birthday (YYYY-MM-DD).";
static const std::string INVALID_ACTIVITY_LEVEL = "Invalid activity level. Please enter a number in the range.";
static const std::string INVALID_GENDER = "Invalid gender. Please enter a correct one.";
static const std::string INVALID_WEIGHT = "Invalid weight. Please enter a valid positive number: ";
static const std::string INVALID_HEIGHT = "Invalid height. Please enter a valid positive number: ";
static const std::string RATE_CHANGE_UNAVAILABLE = "Rate change is unavailable. Please update your goal first.";
 
static const std::string INVALID_FOOD_NAME = "Food name cannot contain special symbols. Try again.";
static const std::string INVALID_EXERCISE_NAME = "Exercise name cannot contain special symbols. Try again.";
static const std::string INVALID_CALORIES = "Invalid calories. Please enter a positive number: ";
static const std::string INVALID_LOG_DATE = "Invalid log date format.";
 
 // General errors
static const std::string FILE_NOT_FOUND = "Error! File was not found.";
static const std::string INVALID_COMMAND = "Command not recognized! Type help for additional guidance.";
static const std::string LOCALTIME_ERROR = "Error retrieving local time.";
static const std::string SOMETHING_WENT_WRONG = "Something went wrong. Try again or contact support.";
static const std::string NO_CHANGES = "No changes were made due to an error.";
 
 // Success messages
static const std::string ACCOUNT_CREATED_SUCCESSFULLY = "Account created successfully! Welcome to MyFitnessPal, ";
static const std::string LOGIN_SUCCESSFUL = "Login successful! Welcome, ";
static const std::string LOGOUT_SUCCESSFUL = "You have successfully logged out.";
static const std::string ACCOUNT_DELETED_SUCCESSFULLY = "Account deleted successfully! Goodbye! :(";
static const std::string PROFILE_SAVE_CHANGES = "Changes have been saved.";
static const std::string LOG_SAVED = "Your log has been successfully saved!";
static const std::string LOG_EDITED = "Your log has been successfully edited!";
static const std::string DELETED_LOGS = " were deleted.";
 
 // Output messages
static const std::string LOGS_EMPTY = "No logs found on ";
static const std::string LOGS_DELETED = " logs associated with your account were deleted.";
static const std::string ARE_YOU_SURE = "Are you sure? (yes/no)";