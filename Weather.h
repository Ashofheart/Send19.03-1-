#pragma once
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace MY {
	class WeatherForecast {
	public:
		class Weather {
			float temp;
			std::string date;
			std::string description;
		public:
			Weather(float temp, std::string date, std::string description);
			std::string Date();
			std::string Descr();
			float Temp();
			friend std::ostream& operator<< (std::ostream& stream, const MY::WeatherForecast::Weather& w);
		};
		WeatherForecast(std::string city, std::string API);
		Weather operator[](int ind);
		float Get_Min_Temp(int index);
		float Get_Max_Temp(int index);
		float Get_Middle_Temp(int index);
	private:
		std::vector<Weather> Forecast;
		std::vector<float> MinTemp;
		std::vector<float> MaxTemp;
		std::vector<float> MiddleTemp;
	};
}