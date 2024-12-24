/*
*
* Solution to course project # 9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Teodor Golisharski
* @idnumber 6MI0600367
* @compiler VC
*
* MyFitnessPal CLI Application
*
*/


#include <iostream>
#include <string>
#include <vector>
#include <fstream>

static std::vector<std::string> usernames;
static std::vector<std::string> logs;
static double bmr = 0;
static int maintainCalories = 0;
static int additional = 0;

static std::string current_user = "";

const std::string USERS_FILE_NAME = "users.txt";
const std::string LOGS_FILE_NAME = "logs.txt";

void create_account() {
	std::cout << "----------- Registration -----------" << std::endl;
	std::string username, password, gender, birthdate, goal = "", account;

	std::cout << "Username: ";
	std::cin >> username;

	std::cout << "\nPassword: ";
	std::cin >> password;

	int age, height, activity_level;
	double weight;

	std::cout << "----------- Personal Details -----------" << std::endl;
	std::cout << "Age: ";
	std::cin >> age;

	std::cout << "\nGender: ";
	std::cin >> gender;

	std::cout << "\nHeight: ";
	std::cin >> height;

	std::cout << "\nWeight: ";
	std::cin >> weight;

	std::cout << "\n-------------------------------------------------------" << std::endl;
	std::cout << "1 - Sedentary (little to no exercise)";
	std::cout << "2 - Light activity (exercise 1-3 days per week)";
	std::cout << "3 - Moderate activity (exercise 3-5 days per week)";
	std::cout << "4 - Active (exercise 6-7 days per week)";
	std::cout << "5 - Very active (intense workouts or physical labor)";
	std::cout << "#Guide: Type the number based on your activity.";
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "Activity level: ";
	std::cin >> activity_level;

	switch (activity_level) {
	case 1: bmr = 1.2; break;
	case 2: bmr = 1.375; break;
	case 3: bmr = 1.55; break;
	case 4: bmr = 1.725; break;
	case 5: bmr = 1.9; break;
	}

	std::cout << "\n-------------------------------------------------------" << std::endl;
	std::cout << "1 - Lose weight" << std::endl;
	std::cout << "2 - Maintain weight" << std::endl;
	std::cout << "3 - Gain weight" << std::endl;
	std::cout << "#Guide: Type the number based on your goal." << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	int tempOption1 = 0, tempOption2 = 0;
	std::cout << "Goal: ";
	std::cin >> tempOption1;
	if (tempOption1 != 2) {
		std::cout << "\n-------------------------------------------------------" << std::endl;
		std::cout << "1 - 0.25 kg a week" << std::endl;
		std::cout << "2 - 0.50 kg a week" << std::endl;
		std::cout << "3 - 0.75 kg a week" << std::endl;
		std::cout << "4 - 1 kg a week" << std::endl;
		std::cout << "#Guide: Type the number based on your desired transformation rate.";
		std::cout << "-------------------------------------------------------" << std::endl;
		std::cout << "Rate: ";
		std::cin >> tempOption2;

		tempOption2 = tempOption2 == 1 ? 275 : tempOption2 == 2 ? 550 : tempOption2 == 3 ? 825 : 1110;
		if (tempOption1 == 1) {
			tempOption2 = 0 - tempOption2;
		}
	}
	additional += tempOption2;

	std::cout << "\n-------------------------------------------------------" << std::endl;
	std::cout << "------------------CHOOSE ACCOUNT TYPE------------------" << std::endl;
	std::cout << "1 - Standard" << std::endl;
	std::cout << "2 - Premium" << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "AccountType: ";
	std::cin >> account;
}

void delete_account(std::string username, std::string password) {
	// Deleting account
}

void log_in(std::string username, std::string password) {
	// logs in existring user
}

void log_out() {
	// logs out currently logged in user
}

void start_guide() {
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Welcome to MyFitnessPal" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
}

void load_information() {
	std::ifstream in_users(USERS_FILE_NAME);
	if (!in_users) {
		std::ofstream users(USERS_FILE_NAME);
		users.close();
	}
	else {
		std::string line;
		while (std::getline(in_users, line)) {
			size_t pos = line.find('%');
			if (pos != std::string::npos) {

				std::string username = line.substr(0, pos);
				usernames.push_back(username);
			}
		}
		in_users.close();
	}

	std::ifstream in_logs(LOGS_FILE_NAME);
	if (!in_logs) {
		std::ofstream logs(LOGS_FILE_NAME);
		logs.close();
	}
	else {
		std::string log_entry;
		while (std::getline(in_logs, log_entry)) {
			logs.push_back(log_entry);
		}
		in_logs.close();
	}
}

void run() {
	start_guide();
	load_information();

	for (size_t i = 0; i < usernames.size(); i++)
	{
		std::cout << usernames[i] << std::endl;
	}
}


int main()
{
	std::cout << "\n-------------------------------------------------------" << std::endl;
	//run();
}
