#include "Weather.h"
#include <chrono>

std::vector<std::string> split(std::string s1, std::string s2) {
	int cnt = 0;
	std::vector<std::string> ans;
	std::string now = "";
	for (auto i : s1) {
		if (cnt == s2.size()) {
			ans.push_back(now);
			cnt = 0;
			now = "";
		}
		if (i == s2[cnt]) {
			cnt++;
		}
		else {
			now += i;
		}
	}
	if (now != "") {
		ans.push_back(now);
	}
	return ans;
}

int str_to_int(std::string s) {
	int ans = 0;
	for (int i = 0; i < s.size(); i++) {
		ans *= 10;
		ans += int(s[i] - '0');
	}
	return ans;
}

int Date_to_index(std::string date) {
	std::vector<std::string> dt = split(date, ":");
	auto now = std::chrono::system_clock::now();
	std::tm specific_date = {};
	specific_date.tm_year = str_to_int(dt[0]) - 1900;
	specific_date.tm_mon = str_to_int(dt[1]) - 1;
	specific_date.tm_mday = str_to_int(dt[2]) + 1;
	std::chrono::system_clock::time_point date_chrono = std::chrono::system_clock::from_time_t(std::mktime(&specific_date));
	std::chrono::duration<double> ans = date_chrono - now;
	int ans_int = int(ans.count()) / (60 * 60 * 24);
	if (ans_int >= 6) {
		return -1;
	}
	return ans_int;
}

const std::string API = "45cff52cc241e93dd06a9c9980c74a7c";

int main()
{
	std::cout << "Enter your city\'s name:\n";
	std::string city; std::cin >> city;
	MY::WeatherForecast wf(city, API);
	bool work = true;
	int choose;
	std::string date;
	int month, day;
	MY::WeatherForecast::Weather* w;
	while (work) {
		std::cout << "1)Today\'s forecast\n2)5 days forecast\n3)One of next 5 days forecast\n";
		std::cout << "4)Biggest temperature of one of next 5 days\n5)Smallest temperature of one of next 5 days\n";
		std::cout << "6)Middle temperature of one of next 5 days\n";
		std::cout << "7)exit\n";
		std::cin >> choose;
		getchar();
		switch (choose) {
		case 1:
			std::cout << wf[0] << '\n';
			std::cout << "press Enter to continue...";
			getchar();
			system("cls");
			break;
		case 2:
			for (int i = 0; i < 5; i++) {
				std::cout << wf[i] << '\n';
			}
			std::cout << "press Enter to continue...";
			getchar();
			system("cls");
			break;
		case 3:
			std::cout << "enter date - which of five next days do you want to see\n";
			std::cin >> date;
			getchar();
			std::cout << wf[Date_to_index(date)] << '\n';
			std::cout << "press Enter to continue...";
			getchar();
			system("cls");
			break;
		case 4:
			std::cout << "enter date - which of five next days do you want to see\n";
			std::cin >> date;
			getchar();
			std::cout << "The biggest temperature is: " << wf.Get_Max_Temp(Date_to_index(date)) << '\n';
			std::cout << "press Enter to continue...";
			getchar();
			system("cls");
			break;
		case 5:
			std::cout << "choose - which of five next days do you want to see\n";
			std::cin >> date;
			getchar();
			std::cout << "The smallest temperature is: " << wf.Get_Min_Temp(Date_to_index(date)) << '\n';
			std::cout << "press Enter to continue...";
			getchar();
			system("cls");
			break;
		case 6:
			std::cout << "choose - which of five next days do you want to see\n";
			std::cin >> date;
			getchar();
			std::cout << "The middle temperature is: " << wf.Get_Middle_Temp(Date_to_index(date)) << '\n';
			std::cout << "press Enter to continue...";
			getchar();
			system("cls");
			break;
		case 7:
			work = false;
			break;
		default:
			std::cout << "it is incorrect choose!\n";
			break;
		}
	}
}